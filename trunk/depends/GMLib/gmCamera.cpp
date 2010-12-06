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



/*! \file gmCamera.cpp
 *
 *  Implementation of the Camera class.
 *
 *  \date   2008-07-26
 */


// GMlib includes
#include "gmPoint3D.h"
#include "gmCamera.h"
#include "gmMaterial.h"


namespace GMlib {




  Scene	Camera::_default_scene;
  unsigned int	Camera::_display_list = 0;




  /*! Camera::Camera( Scene& s = _default_scene )
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  Camera::Camera( Scene& s ) : DisplayObject(),_scene(&s) {

    resetC();
  }


  /*! Camera::Camera( Scene* s )
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  Camera::Camera( Scene* s ) : DisplayObject(),_scene(s) {

    resetC();
  }


  /*! Camera::Camera( const Point<float,3>& pos, const Point<float,3>& look_at_pos )
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  Camera::Camera(
    const Point<float,3>&  pos,
    const Point<float,3>&  look_pos
  ) : DisplayObject(look_pos,pos), _scene(&_default_scene) {

    resetC();
  }

  /*! Camera::Camera( const Point<float,3>&  pos,	const Vector<float,3>& dir,	const Vector<float,3>& up, float zoom )
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  Camera::Camera(
    const Point<float,3>&  pos,
    const Vector<float,3>& dir,
    const Vector<float,3>& up,
    float zoom
  ) : DisplayObject(pos,dir,up),_scene(&_default_scene) {

    resetC(zoom);
  }


  /*! Camera::~Camera()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  Camera::~Camera() {}


  /*! double Camera::deltaTranslate(DisplayObject *)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  double Camera::deltaTranslate(DisplayObject * obj) {

    if(obj)
      return 26*(getDir()*(obj->getPos()-getPos()))*getNearPlane()/(getFocalLength()*getViewportH());
    else
      return 0.0;
  }


  void Camera::enableBlendSort( bool enable ) {

    _blend_sort = enable;
  }


  /*! SceneObject*	Camera::findSelectObject(int, int, int type_id)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  SceneObject*	Camera::findSelectObject(int x, int y, int type_id) {

    glPushAttrib(GL_ALL_ATTRIB_BITS ); // Save complete state
      glDisable(GL_COLOR_MATERIAL);glDisable(GL_LIGHTING);glDisable(GL_BLEND);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glShadeModel(GL_FLAT);
    Color c;
    select(type_id);
    glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(GLubyte*)(&c));
    glPopAttrib(); // reset state
    return find(c.get());
  }


  /*! Array<SceneObject* > Camera::findSelectObjects(int xmin, int ymin, int xmax, int ymax, int type_id)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  Array<SceneObject* > Camera::findSelectObjects(int xmin, int ymin, int xmax, int ymax, int type_id) {

    Array<SceneObject* > sel;
    int dx=(xmax-xmin)+1;
    int dy=(ymax-ymin)+1;
    if (dx<2 || dy <2) return sel;     // for debugging, shouldn't really be here?

    glPushAttrib(GL_ALL_ATTRIB_BITS ); // Save complete state
    glDisable(GL_COLOR_MATERIAL);glDisable(GL_LIGHTING);glDisable(GL_BLEND);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glShadeModel(GL_FLAT);
    Color* pixels=new Color[dx*dy];
    _select(type_id);
    glReadPixels(xmin,ymin,dx-1,dy-1,GL_RGBA,GL_UNSIGNED_BYTE,(GLubyte*)pixels);
    glPopAttrib(); // reset state

    int ct=0;
    Color c;
    for(int i=ymin; i<ymax; i++)
      for(int j=xmin;j<xmax; j++)
      {
        c=pixels[ct++];
        SceneObject* tmp=find(c.get());
        if(tmp)
          if(!tmp->getSelected()) { sel.insertAlways(tmp); tmp->setSelected(true); }
      }
    delete [] pixels;
    return sel;
  }


  /*! double Camera::getDistanceToObject(int x, int y)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  double Camera::getDistanceToObject(int x, int y) {

    SceneObject* 	obj = findSelectObject(x, y);
    return getDistanceToObject(obj);
  }


  /*! double Camera::getDistanceToObject(SceneObject*)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  double Camera::getDistanceToObject(SceneObject* obj) {

    if(obj) {

      const HqMatrix<float,3> mat = _matrix*_matrix_scene_inv;
      const Vector<float,3> dv = mat*Point<float,3>(obj->getCenterPos());
      return dv.getLength();
    }
    else
      return 0.0;
  }


  /*! HqMatrix<float,3>& Camera::getMatrix()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  HqMatrix<float,3>& Camera::getMatrix() {

    /*! \todo fix how the matrix is returned */
    static HqMatrix<float,3> retmat;
    retmat = _matrix;
    retmat.invertOrthoNormal();
    return retmat;
  }


  /*! void Camera::go(bool stereo)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   *	Running the Camera.
   */
  void Camera::go(bool stereo) {

    _active = true;
    if (stereo)
    {
      Point3D<float>		tmp_pos  = _pos  - _eye_dist*_side;
      UnitVector3D<float>	tmp_dir  = _dir  + _ed_fd*_side; //tmp_dir  = _pos + _focus_dist*_dir - tmp_pos;
      UnitVector3D<float>	tmp_side = _side - _ed_fd*_dir;  //tmp_side = _up^tmp_dir;
      basisChange(tmp_side, _up, tmp_dir, tmp_pos);			// Change to right eye
      display();
      basisChange(_side, _up, _dir, _pos);						// Back to left eye
    }
    else
    {
      if(_locked)
      {
        updateOrientation(getSceneLockPos());
        basisChange(_side, _up, _dir, _pos);
      }
      display();
    }
    _active = false;
  }


  bool Camera::isBlendSortEnabled() const {

    return _blend_sort;
  }


  /*! void Camera::localDisplay()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void Camera::localDisplay() {

    static Material lins(
      Color( 0.19125f,  0.0735f,  0.0225f,    1.0f ),
      Color( 0.5038f,   0.27048f,  0.0828f,   1.0f ),
      Color( 0.256777f, 0.137622f, 0.086014f, 1.0f ),
      12.8f
    );

    static Material rubb(
      Color( 0.105882f, 0.058824f, 0.103725f, 1.0f ),
      Color( 0.427451f, 0.470588f, 0.501176f, 1.0f ),
      Color( 0.333333f, 0.333333f, 0.501569f, 1.0f ),
      9.84615f
    );

    //PolishedSilver.glSet();
    glCallList(_display_list);
    glCallList(_display_list+2);
    rubb.glSet();
  //  GMmaterial::PolishedBronze.glSet();
    glCallList(_display_list+1);
    glCallList(_display_list+3);
  //	GMmaterial::PolishedRed.glSet();
    lins.glSet();
    glCallList(_display_list+4);
    if(_frustum_visible) {

      Color		col( 1.0f, 1.0f, 1.0f, 1.0f ); // hvit
      Point3D<float> p1(0,0,-_near_plane);
      Point3D<float> p2(0,0,-_far_plane);
      Vector3D<float> v1(0,_angle_tan*_near_plane,0);
      Vector3D<float> v2(-_ratio*_angle_tan*_near_plane,0,0);
      Vector3D<float> v3(0,_angle_tan*_far_plane,0);
      Vector3D<float> v4(-_ratio*_angle_tan*_far_plane,0,0);
      Point3D<float> p1m(p1-v1);
      Point3D<float> p2m(p2-v3);
      p1 += v1;
      p2 += v3;
      GLboolean lg;
      glGetBooleanv(GL_LIGHTING,&lg);
      if(lg) glDisable(GL_LIGHTING);
      glColor(col);
      glBegin(GL_LINE_LOOP);
        glPoint(p1+v2);	glPoint(p1-v2);	glPoint(p1m-v2);	glPoint(p1m+v2);
      glEnd();
      glBegin(GL_LINE_LOOP);
        glPoint(p2+v4);	glPoint(p2-v4);	glPoint(p2m-v4);	glPoint(p2m+v4);
      glEnd();
      glBegin(GL_LINES);
        glPoint(p1 +v2);	glPoint(p2 +v4);	glPoint(p1 -v2);	glPoint(p2 -v4);
        glPoint(p1m-v2);	glPoint(p2m-v4);	glPoint(p1m+v2);	glPoint(p2m+v4);
      glEnd();
      if(lg) glEnable(GL_LIGHTING);
    }
    if(_locked && !_lock_object) {

      GLboolean lg;
      glGetBooleanv(GL_LIGHTING,&lg);
      if(lg) glDisable(GL_LIGHTING);
      glPushMatrix();
      HqMatrix<float,3> invmat = _present; invmat.invertOrthoNormal();
      glTranslate(invmat*_lock_pos);
      glColor(GMcolor::Green);
      glCallList(_display_list+8);
      glPopMatrix();
      if(lg) glEnable(GL_LIGHTING);
    }
  }



  /*! void Camera::localSelect()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void Camera::localSelect() {

    if(!_active) {
      glCallList(_display_list+9);
    }
  }


  /*! SceneObject* Camera::lockTargetAtPixel(int x, int y)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  SceneObject* Camera::lockTargetAtPixel(int x, int y) {

    SceneObject* 	obj = findSelectObject(x, y);
    if(obj)
    {
      lock(obj);
      return obj;
    }
    return 0;
  }


  /*! void Camera::reshape(int w1, inth1, int w2, int h2)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   *	To be used when changing size of window
   */
  void Camera::reshape(int w1, int h1, int w2, int h2) {

    _x = w1;
    _y = h1;
    _w = w2-w1;
    _h = h2-h1;
  //	glViewport(w1,h1,w2,h2);
    _ratio = float(_w)/float(_h);
  //	_setPerspective();
  }


  /*! void Camera::zoom(float z)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void Camera::zoom(float z) {

    setFocalDist(z*_focal_length);
  }


  /*! void Camera::makeGraphics()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void Camera::makeGraphics() {

    int i;
    Point<float,3>		p[18];
    UnitVector<float,3>	v[18];

    p[0] = Point3D<float>(0.07,0.1,0.3);		p[4] = Point3D<float>(-0.07,0.1,0.3);
    p[1] = Point3D<float>(0.07,0.1,-0.3);		p[5] = Point3D<float>(-0.07,0.1,-0.3);
    p[2] = Point3D<float>(0.07,-0.1,-0.3);	p[6] = Point3D<float>(-0.07,-0.1,-0.3);
    p[3] = Point3D<float>(0.07,-0.1,0.3);		p[7] = Point3D<float>(-0.07,-0.1,0.3);

    v[0] = Vector3D<float>(1,0,0);
    v[1] = Vector3D<float>(0,1,0);
    v[2] = Vector3D<float>(-1,0,0);
    v[3] = Vector3D<float>(0,-1,0);
    v[4] = Vector3D<float>(0,0,1);
    v[5] = Vector3D<float>(0,0,-1);

    _display_list = glGenLists(10);

    // Lager displayliste for display
    glNewList(_display_list, GL_COMPILE);
      glBegin(GL_QUADS);
        glNormal(v[2]); glPoint(p[0]); glPoint(p[1]); glPoint(p[2]); glPoint(p[3]);	// right
        glNormal(v[1]); glPoint(p[0]); glPoint(p[4]); glPoint(p[5]); glPoint(p[1]); // top
        glNormal(v[0]); glPoint(p[7]); glPoint(p[6]); glPoint(p[5]); glPoint(p[4]); // left
        glNormal(v[3]); glPoint(p[3]); glPoint(p[2]); glPoint(p[6]); glPoint(p[7]); // botton
        glNormal(v[4]); glPoint(p[0]); glPoint(p[3]); glPoint(p[7]); glPoint(p[4]); // front
        glNormal(v[5]); glPoint(p[2]); glPoint(p[1]); glPoint(p[5]); glPoint(p[6]); // behind
      glEnd();
    glEndList();

    glNewList(_display_list+9, GL_COMPILE);
      glBegin(GL_QUADS);
        glPoint(p[0]); glPoint(p[1]); glPoint(p[2]); glPoint(p[3]);	// right
        glPoint(p[0]); glPoint(p[4]); glPoint(p[5]); glPoint(p[1]); // top
        glPoint(p[7]); glPoint(p[6]); glPoint(p[5]); glPoint(p[4]); // left
        glPoint(p[3]); glPoint(p[2]); glPoint(p[6]); glPoint(p[7]); // botton
        glPoint(p[0]); glPoint(p[3]); glPoint(p[7]); glPoint(p[4]); // front
        glPoint(p[2]); glPoint(p[1]); glPoint(p[5]); glPoint(p[6]); // behind
      glEnd();
    glEndList();

    p[0] = Point3D<float>(0.1,0.1,0.1);	p[4] = Point3D<float>(-0.1,0.1,0.1);
    p[1] = Point3D<float>(0.1,0.1,-0.1);	p[5] = Point3D<float>(-0.1,0.1,-0.1);
    p[2] = Point3D<float>(0.1,-0.1,-0.1);	p[6] = Point3D<float>(-0.1,-0.1,-0.1);
    p[3] = Point3D<float>(0.1,-0.1,0.1);	p[7] = Point3D<float>(-0.1,-0.1,0.1);

    glNewList(_display_list+8, GL_COMPILE);	//	For lock at Point.
      glBegin(GL_QUADS);
        glNormal(v[2]); glPoint(p[0]); glPoint(p[1]); glPoint(p[2]); glPoint(p[3]);	// right
        glNormal(v[1]); glPoint(p[0]); glPoint(p[4]); glPoint(p[5]); glPoint(p[1]); // top
        glNormal(v[0]); glPoint(p[7]); glPoint(p[6]); glPoint(p[5]); glPoint(p[4]); // left
        glNormal(v[3]); glPoint(p[3]); glPoint(p[2]); glPoint(p[6]); glPoint(p[7]); // botton
        glNormal(v[4]); glPoint(p[0]); glPoint(p[3]); glPoint(p[7]); glPoint(p[4]); // front
        glNormal(v[5]); glPoint(p[2]); glPoint(p[1]); glPoint(p[5]); glPoint(p[6]); // behind
      glEnd();
    glEndList();

    p[0] = Point3D<float>(0.02,-0.1,-0.02);	p[4] = Point3D<float>(-0.02,-0.1,-0.02);
    p[1] = Point3D<float>(0.02,-0.1,-0.08);	p[5] = Point3D<float>(-0.02,-0.1,-0.08);
    p[2] = Point3D<float>(0.02,-0.25,-0.06);	p[6] = Point3D<float>(-0.02,-0.25,-0.06);
    p[3] = Point3D<float>(0.02,-0.25,0.0);	p[7] = Point3D<float>(-0.02,-0.25,0.0);

    glNewList(_display_list+1, GL_COMPILE);	//	For handtak.
      glBegin(GL_QUADS);
        glNormal(v[2]); glPoint(p[0]); glPoint(p[1]); glPoint(p[2]); glPoint(p[3]);	// right
        glNormal(v[1]); glPoint(p[0]); glPoint(p[4]); glPoint(p[5]); glPoint(p[1]); // top
        glNormal(v[0]); glPoint(p[7]); glPoint(p[6]); glPoint(p[5]); glPoint(p[4]); // left
        glNormal(v[3]); glPoint(p[3]); glPoint(p[2]); glPoint(p[6]); glPoint(p[7]); // botton
        glNormal(v[4]); glPoint(p[0]); glPoint(p[3]); glPoint(p[7]); glPoint(p[4]); // front
        glNormal(v[5]); glPoint(p[2]); glPoint(p[1]); glPoint(p[5]); glPoint(p[6]); // behind
      glEnd();
    glEndList();

    p[0] = Point3D<float>(-0.016,0.12,0.09);	p[4] = Point3D<float>(-0.054,0.12,0.09);
    p[1] = Point3D<float>(-0.016,0.12,0.05);	p[5] = Point3D<float>(-0.054,0.12,0.05);
    p[2] = Point3D<float>(-0.016,0.1,0.05);	p[6] = Point3D<float>(-0.054,0.1,0.05);
    p[3] = Point3D<float>(-0.016,0.1,0.09);	p[7] = Point3D<float>(-0.054,0.1,0.09);

    glNewList(_display_list+2, GL_COMPILE);
      glBegin(GL_QUADS);						//	For søker del 1
        glNormal(v[2]); glPoint(p[0]); glPoint(p[1]); glPoint(p[2]); glPoint(p[3]);	// right
        glNormal(v[0]); glPoint(p[7]); glPoint(p[6]); glPoint(p[5]); glPoint(p[4]); // left
        glNormal(v[4]); glPoint(p[0]); glPoint(p[3]); glPoint(p[7]); glPoint(p[4]); // front
        glNormal(v[5]); glPoint(p[2]); glPoint(p[1]); glPoint(p[5]); glPoint(p[6]); // behind
      glEnd();

      p[0] = Point3D<float>(-0.015,0.16,0.35);
      p[1] = Point3D<float>(-0.015,0.16,0.0);
      p[2] = Point3D<float>(-0.015,0.12,0.0);
      p[3] = Point3D<float>(-0.015,0.12,0.35);
      p[4] = Point3D<float>(-0.055,0.16,0.35);
      p[5] = Point3D<float>(-0.055,0.16,0.0);
      p[6] = Point3D<float>(-0.055,0.12,0.0);
      p[7] = Point3D<float>(-0.055,0.12,0.35);

      glBegin(GL_QUADS);		//	For søker del 2
        glNormal(v[2]); glPoint(p[0]); glPoint(p[1]); glPoint(p[2]); glPoint(p[3]);	// right
        glNormal(v[1]); glPoint(p[0]); glPoint(p[4]); glPoint(p[5]); glPoint(p[1]); // top
        glNormal(v[0]); glPoint(p[7]); glPoint(p[6]); glPoint(p[5]); glPoint(p[4]); // left
        glNormal(v[3]); glPoint(p[3]); glPoint(p[2]); glPoint(p[6]); glPoint(p[7]); // botton
        glNormal(v[4]); glPoint(p[0]); glPoint(p[3]); glPoint(p[7]); glPoint(p[4]); // front
        glNormal(v[5]); glPoint(p[2]); glPoint(p[1]); glPoint(p[5]); glPoint(p[6]); // behind
      glEnd();
    glEndList();

    GLMatrix mat(Angle(M_PI_4),Point3D<float>(-0.035,0.14,0.0),UnitVector3D<float>(0,0,-1));
    p[1]  = Point3D<float>(-0.055,0.16,0.35);		v[1]  = Vector3D<float>(-1,1,0);
    p[5]  = Point3D<float>(-0.015,0.16,0.35);		v[5]  = Vector3D<float>(1,1,0);
    p[9]  = Point3D<float>(-0.015,0.12,0.35);		v[9]  = Vector3D<float>(1,-1,0);
    p[13] = Point3D<float>(-0.055,0.12,0.35);		v[13] = Vector3D<float>(-1,-1,0);
    p[17] = Point3D<float>(-0.055,0.16,0.35);		v[17] = Vector3D<float>(-1,1,0);

    p[3]  = Point3D<float>(-0.035,0.16,0.35);		v[3]  = Vector3D<float>(0,1,0);
    p[7]  = Point3D<float>(-0.015,0.14,0.35);		v[7]  = Vector3D<float>(1,0,0);
    p[11] = Point3D<float>(-0.035,0.12,0.35);		v[11] = Vector3D<float>(0,-1,0);
    p[15] = Point3D<float>(-0.055,0.14,0.35);		v[15] = Vector3D<float>(-1,0,0);

    p[0] = p[1] + Vector3D<float>(-0.01,0.01,0.05); v[0] = v[1] + Vector3D<float>(0.0,0.0,0.02);

    for(i=2; i<18;i+=2)
    {
      p[i] = mat*p[i-2];
      v[i] = mat*v[i-2];
    }

    glNewList(_display_list+3, GL_COMPILE);
      glBegin(GL_TRIANGLE_STRIP);		//	For søker del 3
        for(i=0; i<18;i++)
        {
          glNormal(v[i]); glPoint(p[i]);
        }
      glEnd();
    glEndList();

    // The lence
    GLMatrix mat2(Angle(M_PI_4),UnitVector3D<float>(0,0,1));
    Point3D<float> cp(0,0,-0.3);
    p[0] = cp + Vector3D<float>(0.0,0.05,0.0);
    p[1] = cp + Vector3D<float>(0.0,0.08,-0.2);
    v[0] = Vector3D<float>(0.0,1.0,0.15);

    for(i=2; i<18;i+=2)
    {
      p[i]   = mat2*p[i-2];
      p[i+1] = mat2*p[i-1];
      v[i]   = mat2*v[i-2];
    }

    glNewList(_display_list+4, GL_COMPILE);
      glBegin(GL_TRIANGLE_STRIP);		//	For Linse
        for(i=0; i<18;i+=2)
        {
          glNormal(v[i]); glPoint(p[i]); glPoint(p[i+1]);
        }
      glEnd();
    glEndList();

  }


  /*! void Camera::resetC(float z)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   *	NB!!! Only for the constructors.
   */
  void Camera::resetC(float z) {

    basisChange(_side, _up, _dir, _pos);	// Must repete because the virtual functions do not work proper jet.
    _ratio		= 1.0;
    _near_plane = 1.0;
    _far_plane	= 1000.0;
    _eye_dist	= 0.08;
    setFocalDist(z*50);
    setSurroundingSphere(Sphere<float,3>(Point3D<float>(0,0,0),1.0));
    if (!_display_list) makeGraphics();
    setCoordSysVisible();
    setFrustumVisible();
    _type_id  = GM_SO_TYPE_CAMERA;
    _culling = true;
    _blend_sort = true;
    _select_color = GMcolor::Pink;
    _select_linewidth = 1.2f;
    _select_active_color = GMcolor::Yellow;
    _select_active_linewidth = 1.0f;
  }


  /*! void Camera::select(int type_id)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void Camera::select(int type_id) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    setPerspective();
    glViewport(_x,_y,_w,_h);
    glPushMatrix();
      glMultMatrix(_matrix);
      glMultMatrix(_matrix_scene_inv);
      _scene->_culling(_frustum);
      _scene->_select(type_id);
    glPopMatrix();
  }



  /*! void Camera::setPerspective()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void Camera::setPerspective() {

    float	hh = _near_plane*_angle_tan;
    float	rr = _ratio*hh;
    _frustum = Frustum(_matrix_scene,_pos,_dir,_up,_side,_angle_tan,_ratio,_near_plane,_far_plane);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-rr, rr, -hh, hh, _near_plane, _far_plane);
    glMatrixMode(GL_MODELVIEW);
  }


  void Camera::setSelectActiveColor( const Color& color ) {

    _select_active_color = color;
  }


  void Camera::setSelectActiveLineWidth( float width ) {

    _select_active_linewidth = width;
  }


  void Camera::setSelectColor( const Color& color ) {

    _select_color = color;
  }


  void Camera::setSelectLineWidth( float width ) {

    _select_linewidth = width;
  }
}
