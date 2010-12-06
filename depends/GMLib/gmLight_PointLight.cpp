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



/*! \file gmLight_PointLight.cpp
 *
 *  Implementation of the PointLight class.
 *
 *  \date   2008-07-25
 */

// System includes
#include <float.h>

// GMlib includes
#include "gmLight.h"


namespace GMlib {



  /*! PointLight::PointLight()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  PointLight::PointLight() : Light(), DisplayObject(), _pos(0.0f), _light_sphere(Point3D<float>(0,0,0), FLT_MAX ) {

    _type_id  = GM_SO_TYPE_LIGHT;
  }


  /*! PointLight::PointLight(	const Point<float,3>& pos)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  PointLight::PointLight(	const Point<float,3>& pos) : Light(), _pos(0.0f) {

    translate(pos);
    _type_id  = GM_SO_TYPE_LIGHT;
  }


  /*! PointLight::PointLight(	const Color& amb, const Color& dif, const Color& spe, const Point<float,3>& pos )
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  PointLight::PointLight(
        const Color& amb,
        const Color& dif,
        const Color& spe,
        const Point<float,3>& pos
  ) : Light(amb,dif,spe),DisplayObject(),_pos(0.0f) {

    translate(pos);
    _type_id  = GM_SO_TYPE_LIGHT;
  }


  /*! PointLight::PointLight(	const PointLight& pl)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  PointLight::PointLight(	const PointLight& pl) : Light(pl), DisplayObject(pl), _pos(pl._pos) {

    _type_id  = GM_SO_TYPE_LIGHT;
  }


  /*! PointLight::~PointLight()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  PointLight::~PointLight() {}


  /*! void PointLight::culling( const Frustum& frustum )
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void PointLight::culling( const Frustum& frustum ) {

    if (!isCullable()) { Light::enable() ; return;}
    int k = frustum.isInterfering(_light_sphere);
    if (k < 0) Light::enable();
    else Light::enable();
  }


  /*! void PointLight::setAttenuation(float constant, float linear, float quadratic)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void PointLight::setAttenuation(float constant, float linear, float quadratic) {

    calculateRadius( constant, linear, quadratic );

    glLight(GL_CONSTANT_ATTENUATION, constant);
    glLight(GL_LINEAR_ATTENUATION, linear);
    glLight(GL_QUADRATIC_ATTENUATION, quadratic);
  }


  /*! void PointLight::setAttenuation(const float att[])
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void PointLight::setAttenuation(const float att[]) {

    setAttenuation(att[0],att[1],att[2]);
  }


  /*! void PointLight::calculateRadius(float constant, float linear, float quadratic)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void PointLight::calculateRadius(float constant, float linear, float quadratic) {

    _attenuation[0] = constant;
    _attenuation[1] = linear;
    _attenuation[1] = quadratic;
    double aa, solution;
    if ((linear == 0) && (quadratic == 0))
    {
      setCullable(false); // Disable culling
      solution = FLT_MAX;
    }
    else if (quadratic == 0)
    {
      if(constant <= _min_light_contribution)
        solution = (_min_light_contribution-constant) / linear;
      else
        solution = 0;
    }
    else
    {
      if(constant <= _min_light_contribution)
        aa= sqrt(linear*linear + 4 * (_min_light_contribution-constant) * quadratic);
      else
        aa = linear;
      solution = (aa -linear)/(2 * quadratic);
    }
    _light_sphere.resetValue((float)solution);
  }


  /*! void PointLight::lighting()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void PointLight::lighting() {

    glPushMatrix();
    // _present.inverse2().mult();
    glMultMatrix(_present);
    glLightPos(_pos);
    glPopMatrix();
  }

}
