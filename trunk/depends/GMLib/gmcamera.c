/**********************************************************************************
**
** Copyright (C) 1994 Narvik University College
** Contact: GMlib Online Portal at http://episteme.hin.no
**
** This file is part of the Geometric Modeling Library, GMlib.
**
** GMlib is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** GMlib is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with GMlib.  If not, see <http://www.gnu.org/licenses/>.
**
**********************************************************************************/



/*! \file gmCamera.c
 *  \brief Inline Camera class implementations
 *
 *  Inline implementations of the Camera class.
 *  This file is included in the header file
 *
 *  \date   2008-08-03
 */





namespace GMlib {



  /*! void Camera::basisChange(const Vector<float,3>& x, const Vector<float,3>& y, const Vector<float,3>& z, const Vector<float,3>& p)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void Camera::basisChange(
    const Vector<float,3>& x,
    const Vector<float,3>& y,
    const Vector<float,3>& z,
    const Vector<float,3>& p
  ) {

    static GLMatrix glmat;
    glmat = _matrix.getTransposed().getPtr();
    glmat.basisChangeCam( x,y,z,p );
    for( int i = 0; i < 4; i++ )
      for( int j = 0; j < 4; j++ )
        _matrix[i][j] = glmat.get(j,i);
  }


  /*! void Camera::decreaseEyeDist(double delta)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void Camera::decreaseEyeDist(double delta) {

    _eye_dist-=delta;
    _ed_fd=_eye_dist/_focal_length;
  }


  /*! void Camera::decreaseFocalDist(double delta)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void Camera::decreaseFocalDist(double delta) {

    increaseFocalDist(-delta);
  }


  /*! void Camera::display()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void Camera::display() {

    setPerspective();
    glViewport(_x,_y,_w,_h);
    glPushMatrix();
      glMultMatrix(_matrix);
      glMultMatrix(_matrix_scene_inv);

      if(_coord_sys_visible)
        drawActiveCam();

      // Cull the scene using the camera's frustum
      _scene->_culling( _frustum, _culling );

      // Sort the scene for blending, if required
      if( _blend_sort )
        _scene->_blending( this );

      // Enable lighting
      _scene->_lighting();

      // Render scene
      _scene->_display( _blend_sort );


      // Display Selection
      glPushAttrib( GL_POLYGON_BIT | GL_LINE_BIT | GL_LIGHTING_BIT ); {

        glLineWidth( _select_linewidth );
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDisable( GL_LIGHTING );

        glColor( _select_color );

        _scene->_displaySelection();
      } glPopAttrib();


      // Display Active
      glPushAttrib( GL_POLYGON_BIT | GL_LINE_BIT | GL_LIGHTING_BIT ); {

        glLineWidth( _select_active_linewidth );
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDisable( GL_LIGHTING );

        glColor( _select_active_color );

        _scene->_displayActive();
      } glPopAttrib();

    glPopMatrix();
  }


  /*! void Camera::drawActiveCam()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void Camera::drawActiveCam() {

    float hh = -1.5f*_near_plane*_angle_tan;
    Point3D<float> cp(_ratio*hh, hh, -_near_plane-1.0f);


    /*! \todo check if this is correct and fix if not */
    cp = _matrix_scene * cp;
    cp = getMatrix() * cp;

  //	GLboolean lg;
  //	glGetBooleanv(GL_LIGHTING,&lg);
  //	if(lg) glDisable(GL_LIGHTING);
    glPushAttrib( GL_LIGHTING );
    glDisable( GL_LIGHTING );
    glBegin(GL_LINES); // draw Coordsys
      glColor( GMcolor::Red );	glPoint(cp); glPoint(cp+Vector3D<float>(0.1f,0,0));
      glColor( GMcolor::Green );	glPoint(cp); glPoint(cp+Vector3D<float>(0,0.1f,0));
      glColor( GMcolor::Blue );	glPoint(cp); glPoint(cp+Vector3D<float>(0,0,0.1f));
    glEnd();
    if(_locked && ! _lock_object)
    {
      glPushMatrix();
      glTranslate(_lock_pos);
      glCallList(_display_list+8);
      glPopMatrix();
    }
    glPopAttrib();
  //	if (lg) glEnable(GL_LIGHTING);
  }


  /*! void Camera::enableCulling( bool enable )
   *	\brief Enable or disable culling
   *
   *	Enable or disable Culling for this camera
   */
  inline
  void Camera::enableCulling( bool enable ) {

    _culling = enable;
  }


  /*! SceneObject* Camera::find(unsigned int name
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  SceneObject* Camera::find(unsigned int name) {

    return _scene->find(name);
  }


  /*! float Camera::getAngleTan() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  float Camera::getAngleTan() const {

    return _angle_tan;
  }


  /*! float Camera::getFarPlane() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  float Camera::getFarPlane() const	{

    return _far_plane;
  }


  /*! float Camera::getFocalLength() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  float Camera::getFocalLength() const {

    return (float)_focal_length;
  }


  /*! std::string Camera::getIdentity() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  std::string Camera::getIdentity() const {

    return "Camera";
  }


  /*! float Camera::getNearPlane() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  float Camera::getNearPlane() const {

    return _near_plane;
  }


  /*! float Camera::getRatio() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  float Camera::getRatio() const {

    return _ratio;
  }


  /*!
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void Camera::getViewport(int& w1, int& w2, int& h1, int& h2) const {

    w1 = _x;
    h1 = _y;
    w2 = _x+_w;
    h2 = _y+_h;
  }


  /*! int Camera::getViewPortW() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  int Camera::getViewportW() const {

    return _w;
  }


  /*! int Camera::getViewPortH() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  int Camera::getViewportH() const {

    return _h;
  }


  /*! void Camera::increaseEyeDist(double delta)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void Camera::increaseEyeDist(double delta) {

    _eye_dist+=delta;
    _ed_fd=_eye_dist/_focal_length;
  }


  /*! void Camera::increaseFocalDist(double delta)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void Camera::increaseFocalDist(double delta) {

    setFocalDist(_focal_length+delta);
  }


  /*! bool Camera::isCoordSysVisible() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  bool Camera::isCoordSysVisible() const {

    return _coord_sys_visible;
  }


  /*! bool Camera::isCulling() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  bool Camera::isCulling() const {

    return _culling;
  }

  /*! bool Camera::isFrustumVisible() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  bool Camera::isFrustumVisible() const {

    return _frustum_visible;
  }


  /*! void Camera::reset()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   *	To be used when changing Camera.
   */
  inline
  void Camera::reset() {

    int	wp[4];
    glGetIntegerv(GL_VIEWPORT,wp);
    reshape(wp[0],wp[1],wp[2],wp[3]);
  }


  /*! void Camera::setCuttingPlanes(float near_plane, float far_plane)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void Camera::setCuttingPlanes(float near_plane, float far_plane) {

    _near_plane = near_plane;
    _far_plane	= far_plane;
    _angle_tan	= 13.0f*_near_plane/(float)_focal_length;
  }


  /*! void Camera::setCoordSysVisible(bool visible)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void Camera::setCoordSysVisible(bool visible) {

    _coord_sys_visible=visible;
  }


  /*! void Camera::setEyeDist(double eye_dist)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void Camera::setEyeDist(double eye_dist) {

    _eye_dist=eye_dist;
    _ed_fd=_eye_dist/_focal_length;
  }


  /*! void Camera::setFocalDist(double focal)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void Camera::setFocalDist(double focal)	{

    _focal_length   = focal;
    _ed_fd			= _eye_dist/_focal_length;
    _angle_tan		= 13.0f*_near_plane/(float)_focal_length;
  }


  /*! void Camera::setFrustumVisible(bool visible=true)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void Camera::setFrustumVisible(bool visible) {

    _frustum_visible=visible;
  }


  /*! void Camera::setScene(Scene& s)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void Camera::setScene(Scene& s) {

    _scene = &s;
  }


  /*! void Camera::setScene(Scene *s)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void Camera::setScene(Scene *s) {

    _scene = s;
  }

}
