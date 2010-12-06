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



/*! \file gmSurroundingSphere.c
 *  \brief SurroundingSphere class function implementations
 *
 *  Implementation of the SurroundingSphere class.
 *
 *  \date   2009-12-26
 */


// GMlib includes
#include "gmSphere3D.h"


// header
#include "gmSurroundingSphere.h"


namespace GMlib {



  SurroundingSphere::SurroundingSphere() {

    setSurroundingSphere( Sphere<float,3>( 1.0f, 0.0f ) );

    _ct = GMcolor::Yellow;
    _cc = GMcolor::White;
    _spheres = GM_SURROUNDINGSPHERE_CLEAN;
    _wireframe = true;
  }


  SurroundingSphere::SurroundingSphere( const SurroundingSphere& copy ) : DisplayObject( copy ) {}


  const Color& SurroundingSphere::getColor( unsigned int mask ) const {

    if( mask == GM_SURROUNDINGSPHERE_TOTAL )
      return _ct;
    else if( mask == GM_SURROUNDINGSPHERE_CLEAN )
      return _cc;
    else {
      static Color error;
      return error;
    }
  }


  std::string SurroundingSphere::getIdentity() const {

    return "SurroundingSphere";
  }


  unsigned int SurroundingSphere::getSpheres() const {

    return _spheres;
  }


  bool SurroundingSphere::isWireframe() const {

    return _wireframe;
  }


  void SurroundingSphere::localDisplay() {

    if( !_parent )
      return;

    glPushMatrix();

    HqMatrix<float,3> mat = _parent->getMatrixGlobal();
    mat.invertOrthoNormal();
    glMultMatrix( mat );

    // Push GL Attributes
    glPushAttrib( GL_LIGHTING_BIT | GL_POLYGON_BIT ); {

      // Disable Lighting
      glDisable( GL_LIGHTING );

      // Set Wireframe or not
      if( _wireframe )
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

      // Display Clean Surrounding Sphere
      if( (_spheres & GM_SURROUNDINGSPHERE_CLEAN) == GM_SURROUNDINGSPHERE_CLEAN ) {

        glColor( _cc );
        Sphere3D( _parent->getSurroundingSphereClean(), 10, 10 ).display();
      }

      // Display Surrounding Sphere
      if( (_spheres & GM_SURROUNDINGSPHERE_TOTAL) == GM_SURROUNDINGSPHERE_TOTAL ) {

        glColor( _ct );
        Sphere3D( _parent->getSurroundingSphere(), 10, 10 ).display();
      }

    // Pop GL Attributes
    } glPopAttrib();

    glPopMatrix();
  }


  void SurroundingSphere::setColor( const Color& color, unsigned int mask ) {

    if( (mask & GM_SURROUNDINGSPHERE_TOTAL) == GM_SURROUNDINGSPHERE_TOTAL )
      _ct = color;

    if( (mask & GM_SURROUNDINGSPHERE_CLEAN) == GM_SURROUNDINGSPHERE_CLEAN )
      _cc = color;
  }


  void SurroundingSphere::setSpheres( unsigned int mask ) {

    _spheres = mask;
  }


  void SurroundingSphere::setWireframe( bool wireframe ) {

    _wireframe = wireframe;
  }


} // END namespace GMlib
