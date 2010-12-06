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
 *
 *  Implementation of Light class.
 *
 *  \date   2008-07-25
 */

#include "gmLight.h"

namespace GMlib {


  Array<unsigned int>   Light::_free_light(100);
  unsigned int          Light::_next_light = GL_LIGHT0;
  float         Light::_min_light_contribution = 100;



  /*! Light::Light()
   * \brief Pending Documentation
   *
   *  Pending Documentation
   */
  Light::Light() {

    if(_free_light.getSize()>0)
    {
      _light_name = _free_light[_free_light.getSize()-1];
      _free_light.removeBack();
    }
    else			_light_name	= _next_light++;
    setColor();
    setCullable(false);
  }


  /*! Light::Light(const Color& amb , const Color& dif, const Color& spe)
   * \brief Pending Documentation
   *
   *  Pending Documentation
   */
  Light::Light(const Color& amb , const Color& dif, const Color& spe) {

    if(_free_light.getSize()>0)
    {
      _light_name = _free_light[_free_light.getSize()-1];
      _free_light.removeBack();
    }
    else			_light_name	= _next_light++;
    setColor(amb,dif,spe);
  }


  /*! Light::Light(const Light& orig)
   * \brief Pending Documentation
   *
   *  Pending Documentation
   */
  Light::Light(const Light& orig) {

    if(_free_light.getSize()>0)
    {
      _light_name = _free_light[_free_light.getSize()-1];
      _free_light.removeBack();
    }
    else			_light_name	= _next_light++;
    setColor( orig._ambient, orig._diffuse, orig._specular);
  }


  /*! Light::~Light()
   * \brief Pending Documentation
   *
   *  Pending Documentation
   */
  Light::~Light() {

    _free_light += _light_name;
    glDisable(_light_name);
  }

}
