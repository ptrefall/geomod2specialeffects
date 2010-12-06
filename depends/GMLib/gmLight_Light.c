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



/*! \file gmLight.cpp
 *  \brief Inline Light class implementations.
 *
 *  Inline implementation of Light class.
 *
 *  \date   2008-08-03
 */


namespace GMlib {


  /*! void Light::culling( const Frustum& )
   * \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Light::culling( const Frustum& ) {};


  /*! void Light::disable()
   * \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Light::disable() {

    glDisable(_light_name);
  }


  /*! void Light::enable()
   * \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Light::enable() {

    glEnable(_light_name);
  }


  /*! bool Light::isCullable()
   * \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  bool Light::isCullable() {

    return _cullable;
  };


  /*! bool Light::isEnabled()
   * \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  bool Light::isEnabled() {

    return glIsEnabled(_light_name) ? true : false;
  }


  /*! void Light::lighting()
   * \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Light::lighting() {}



  /*! void Light::setColor( const Color& ambient, const Color& diffuse, const Color& specular )
   * \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Light::setColor(
    const Color& ambient,
    const Color& diffuse,
    const Color& specular
  ) {

    _ambient		= Color( ambient );
    _diffuse		= Color( diffuse );
    _specular		= Color( specular );

    setIntensity(1.0);
  }


  /*! void Light::setCullable( bool cullable )
   * \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Light::setCullable( bool cullable ) {

    _cullable = cullable;
  };


  /*! void Light::setIntensity(double d,int i)
   * \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Light::setIntensity(double d,int i) {

    if(i==0 || i == 1)
      glLight(GL_AMBIENT,d*_ambient);
    if(i==0 || i == 2)
      glLight(GL_DIFFUSE,d*_diffuse);
    if(i==0 || i == 3)
      glLight(GL_SPECULAR,d*_specular);
  }


  /*! const Color& Light::getAmbient()
   * \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  const Color& Light::getAmbient() {

    return _ambient;
  }


  /*! const Color& Light::getDiffuse()
   * \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  const Color& Light::getDiffuse() {

    return _diffuse;
  }


  /*! unsigned int Light::getLightName()
   * \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  unsigned int Light::getLightName() {

    return _light_name;
  }


  /*! const Color& Light::getSpecular()
   * \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  const Color& Light::getSpecular()	{

    return _specular;
  }


  /*! void Light::glLight( GLenum pn, const Color& co)
   * \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Light::glLight( GLenum pn, const Color& co) {

    GMlib::glLight(_light_name, pn, co);
  }


  /*! void Light::glLight( GLenum pn, float f )
   * \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Light::glLight( GLenum pn, float f ) {

    GMlib::glLight(_light_name, pn, f);
  }


  /*! void Light::glLight( GLenum pn, int f )
   * \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Light::glLight( GLenum pn, int f ) {

    GMlib::glLight(_light_name, pn, f);
  }


  /*! void Light::glLightDir( const Vector<float,3>& dir )
   * \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Light::glLightDir( const Vector<float,3>& dir ) {

    GMlib::glLightDir(_light_name, dir);
  }


  /*! void Light::glLightPos( const Point<float,3>& pos )
   * \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Light::glLightPos( const Point<float,3>& pos ) {

    GMlib::glLightPos(_light_name, pos);
  }


  /*! void Light::glLightSun( const Vector<float,3>& pos )
   * \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Light::glLightSun( const Vector<float,3>& pos ) {

    GMlib::glLightSun(_light_name, pos);
  }

}
