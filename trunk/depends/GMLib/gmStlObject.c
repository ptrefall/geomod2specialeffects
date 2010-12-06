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



/*! \file gmStlObject.c
 *
 *  Implementation of StlObject class inline functions.
 *
 *  \date   2008-10-21
 */


#include "gmTriangleSystem.h"


namespace GMlib {



  inline
  std::string StlObject::getIdentity() const {

    return _identity;
  }


  inline
  unsigned int StlObject::getNoNormals() const {

    return _normals.getSize();
  }


  inline
  unsigned int StlObject::getNoPoints() const {

    return _vertices.getSize();
  }


  inline
  Array< Vector<float,3> > StlObject::getNormals() {

    return _normals;
  }


  inline
  const Array< Vector<float,3> >& StlObject::getNormals() const {

    return _normals;
  }


  inline
  Array< Point<float,3> > StlObject::getPoints() {

    Array< Point<float,3> > v;         // returns copy, no cast between Point3D<float> and Point<float,3>
    v.setSize( _vertices.getSize() );
    for( int i = 0; i < _vertices.getSize(); i++ )
      v[i] = _vertices[i];

    return v;
  }


  inline
  const Array< Point<float,3> >& StlObject::getPoints() const {

    return _vertices;
  }


  inline
  ArrayLX< TSVertex<float> > StlObject::getVertices() {

    ArrayLX< TSVertex<float> > v;         // returns copy, no cast between Point3D<float> and Point<float,3>
    v.setSize( _vertices.getSize() );
    for( int i = 0; i < _vertices.getSize(); i++ )
      v[i] = TSVertex<float>( _vertices[i], _normals[i/3] );

    return v;
  }


  inline
  void StlObject::localDisplay() {

    glPushAttrib( GL_LIGHTING_BIT );

    if( this->isLighted() )
    {
      this->_material.glSet();
    }
    else
    {
      glDisable( GL_LIGHTING );
      glColor(this->_color);
    }

    if( _dlist )
      glCallList( _dlist );

    glPopAttrib();
  }


  inline
  void StlObject::localSelect() {

    glCallList( _dlist+1 );
  }


}
