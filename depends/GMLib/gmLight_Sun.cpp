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



/*! \file gmLight_Sun.cpp
 *
 *  Implementation of the Sun class.
 *
 *  \date   2008-07-25
 */


// GMlib includes
#include "gmLight.h"


namespace GMlib {




  /*! Sun::Sun( const Vector<float,3>& dir )
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  Sun::Sun( const Vector<float,3>& dir ) {

    _dir = dir;
    _type_id  = GM_SO_TYPE_LIGHT;
    setDayLight();
  }


  /*! Sun::~Sun()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  Sun::~Sun() {}


  /*! void Sun::setDayLight( const Color& amb )
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void Sun::setDayLight( const Color& amb ) {

    _global_ambient = Color(amb);
    _setDayLight(1);
  }



  /*! void Sun::lighting()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void Sun::lighting() {

    glPushMatrix();
      glMultMatrix(_present);
      glLightSun(_dir);
    glPopMatrix();
  }



  /*! void Sun::setDayLight(double d)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void Sun::_setDayLight(double d) {

    Color	a = d*_global_ambient;
    float f[4];
    f[0] = float(a.getRedC());
    f[1] = float(a.getGreenC());
    f[2] = float(a.getBlueC());
    f[3] = float(a.getAlphaC());
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,f);
  }

}
