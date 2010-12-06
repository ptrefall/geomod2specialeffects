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



/*! \file gmLightG_PointLightG.cpp
 *
 *  Implementation of the PointLightG class.
 *
 *  \date   2009-01-22
 */

// GMlib includes
#include "gmSphere3D.h"
#include "gmLightG.h"


namespace GMlib {


  PointLightG::PointLightG() {

    _init();
  }


  PointLightG::PointLightG( const Point<float,3>& pos) : PointLight( pos ) {

    _init();
  }


	PointLightG::PointLightG(
    const Color& amb,
    const Color& dif,
    const Color& spe,
    const Point<float,3>& pos
  ) : PointLight( amb, dif, spe, pos ) {

    _init();
  }


  PointLightG::PointLightG( const PointLight& copy ) : PointLight( copy ) {

    _init();
  }


  PointLightG::PointLightG( const PointLightG& copy ) : PointLight( copy ) {

    _dlist = copy._dlist;
    setSurroundingSphere( Sphere<float,3>( Point3D<float>( 0.0 ), 1.0 ) );
  }


  void PointLightG::_init() {

    _dlist = 0;
    setSurroundingSphere( Sphere<float,3>( Point3D<float>( 0.0 ), 1.0 ) );

    _makeDisplayList();
  }


  void PointLightG::_makeDisplayList() {

    Sphere3D sp(1.0,12,8);
    _dlist = glGenLists(1);
    glNewList(_dlist, GL_COMPILE);
      sp.display();
    glEndList();
  }


  std::string PointLightG::getIdentity() const {

    return "PointLightG";
  }

  void PointLightG::localDisplay() {

    glPushAttrib( GL_LIGHTING_BIT ); {

      glDisable( GL_LIGHTING );

      glColor(getAmbient());
      glCallList( _dlist );

    } glPopAttrib();
  }


  void PointLightG::localSelect() {

    glCallList( _dlist );
  }

}
