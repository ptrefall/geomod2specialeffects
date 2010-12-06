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



/*! \file gmStlObject.cpp
 *
 *  Implementation of StlObject class functions.
 *
 *  \date   2008-10-21
 */


#include "gmStlObject.h"


namespace GMlib {


  StlObject::StlObject(float r) {
    _identity = std::string( "STL place holder" );
    _sphere = new PSphere<float>( r );
    _sphere->replot();
    insert( _sphere );

    // update bounding sphere
    Point3D<float> pos(0,0,0);
    Sphere<float,3> s(pos,r);

    setSurroundingSphere(s);

    _init();
  }


  StlObject::StlObject( PSurf<float> *obj, int m1, int m2, GM_STL_VISUALIZATION gsv ) {

    // Resample DSurf
    DMatrix< DMatrix< Vector<float, 3> > > p;
    obj->resample(
      p, m1, m2, 1, 1,
      obj->getParStartU(),
      obj->getParStartV(),
      obj->getParEndU(),
      obj->getParEndV()
    );

    // Set Array Max Size (speedup)
    _normals.setMaxSize( (p.getDim1()-1)*(p.getDim2()-1)*2 );
    _vertices.setMaxSize( _normals.getMaxSize()*3 );

    for( int i = 0; i < p.getDim1() - 1; i++ ) {
      for( int j = 1; j < p.getDim2(); j++ ) {

        Vector<float,3> &v1 = p[i][j-1][0][0];
        Vector<float,3> &v2 = p[i+1][j-1][0][0];
        Vector<float,3> &v3 = p[i][j][0][0];
        Vector<float,3> &v4 = p[i+1][j-1][0][0];
        Vector<float,3> &v5 = p[i+1][j][0][0];
        Vector<float,3> &v6 = p[i][j][0][0];

        Vector<float,3> n1 = Vector3D<float>(v2 - v1) ^ Vector3D<float>(v3 - v1);
        Vector<float,3> n2 = Vector3D<float>(v5 - v4) ^ Vector3D<float>(v6 - v4);

        _normals.insertAlways( n1 );
        _vertices.insertAlways( v1 );
        _vertices.insertAlways( v2 );
        _vertices.insertAlways( v3 );

        _normals.insertAlways( n2 );
        _vertices.insertAlways( v4 );
        _vertices.insertAlways( v5 );
        _vertices.insertAlways( v6 );
      }
    }

    _init();
    replot( gsv );
  }


  StlObject::StlObject( const std::string& filename, const Color& color, int /*flip*/ ) {

    _dlist = 0;

    _color = color;
    _identity = filename;

    _readStlBinary( filename );

    _init();
    replot();
  }


  StlObject::StlObject( std::ifstream& stream, bool binary, const Color& color ) {

    _dlist = 0;

    _color = color;

    load( stream, binary );
    _init();
    replot();
  }



  StlObject::~StlObject() {

    glDeleteLists( _dlist, 2 );
  }


  unsigned long StlObject::_getUli() {

    unsigned char byte1,byte2,byte3,byte4;
    unsigned long int number;
    byte1=(unsigned char)fgetc( _stl_file );
    byte2=(unsigned char)fgetc( _stl_file );
    byte3=(unsigned char)fgetc( _stl_file );
    byte4=(unsigned char)fgetc( _stl_file );
    number = (unsigned long int)byte1 + ((unsigned long int)byte2<<8)
        + ((unsigned long int)byte3<<16) + ((unsigned long int)byte4<<24);
    return( number );
  }


  float StlObject::_getFloat() {

    float number;
    unsigned char stream[5];
    // used to be 3,2,1,0
    stream[0]=(unsigned char)fgetc( _stl_file );
    stream[1]=(unsigned char)fgetc( _stl_file );
    stream[2]=(unsigned char)fgetc( _stl_file );
    stream[3]=(unsigned char)fgetc( _stl_file );

    stream[4] = '\0';

    memcpy( &number, &stream, 4 );

    return( number );
  }


  unsigned int StlObject::_getUint() {

    unsigned char byte1,byte2;
    unsigned int number;
    byte1=(unsigned char)fgetc( _stl_file );
    byte2=(unsigned char)fgetc( _stl_file );
    number = (unsigned int)byte1 + ((unsigned int)byte2<<8);
    return( number );
  }


  void StlObject::_init() {

    _point_size = 5.0;
  }


  void StlObject::_makeList( GLenum e ) {



    if( _dlist ) {

      glDeleteLists( _dlist, 2 );
      _dlist = 0;
    }


    // make display lists
    _dlist = glGenLists( 2 );

    glPushAttrib( GL_POINT_BIT );

    glNewList( _dlist, GL_COMPILE ); {

      if( e == GL_POINTS )
        glPointSize( _point_size );

      glBegin( e ); {

        for( int i = 0; i < _normals.getSize(); i++) {
          glNormal( _normals[i] );                // STL file only carries one normal
          for( int j = 0; j < 3; j++ )            // for each triangle, makes a facet shading,
            glPoint( _vertices[ 3*i+j ] );        // they must be averaged for true smooth surfaces.
        }
      } glEnd();
    } glEndList();

    // Build a new list for selection
    glNewList( _dlist+1, GL_COMPILE ); {
      glBegin( GL_TRIANGLES ); {

        for( int i = 0; i < _normals.getSize(); i++ ) {
          for( int j = 0;j < 3; j++ )
            glPoint( _vertices[ 3*i+j ] );
        }
      } glEnd();
    } glEndList();

    glPopAttrib();
  }


  int StlObject::_readStlBinary(const std::string& filename) {

    if( ( _stl_file = fopen( filename.c_str(), "rb" ) ) == NULL )
      return(-1);

    unsigned long int t;

    // Skipping comment line
    for( t=0; t<80 ; t++ )
      fgetc( _stl_file );

    // Get number for triangles
    unsigned long int n_triangles = _getUli();
    float x,y,z;
    _normals.setMaxSize( n_triangles+1 );
    _vertices.setMaxSize( (n_triangles*3)+1 );

    // Read all the triangles
    for( t=0; t<n_triangles; t++ ) {

      // and put in array
      x=_getFloat(); y=_getFloat(); z=_getFloat();
      _normals.insertAlways( UnitVector3D<float>(x,y,z) );


      x=_getFloat(); y=_getFloat(); z=_getFloat();
      _vertices.insertAlways( Point3D<float> (x,y,z) );

      x=_getFloat(); y=_getFloat(); z=_getFloat();
      _vertices.insertAlways( Point3D<float> (x,y,z) );

      x=_getFloat(); y=_getFloat(); z=_getFloat();
      _vertices.insertAlways( Point3D<float> (x,y,z) );

      // Get number of attribute bytes (is always zero and can be ignored)
      _getUint();
    }

    fclose( _stl_file );
    return 1;
  }


  void StlObject::_updateBounding() {


    // update bounding box
    _bbox.reset( _vertices[0] );
    for( int i = 0; i < _vertices.getSize()-1; i++ )
      _bbox += _vertices[i];

    // update bounding sphere
    Point3D<float> pos( _bbox.getPointCenter() );          // which can be far from origo
    Sphere<float,3> s( pos, _bbox.getPointDelta().getLength() * 0.5f );

    setSurroundingSphere( s );
  }


  float StlObject::getPointSize() {

    return _point_size;
  }


  void StlObject::replot( GM_STL_VISUALIZATION gsv ) {

    if( gsv == GM_STL_POINT )
      _makeList( GL_POINTS );
    else
      _makeList( GL_TRIANGLES );

    _updateBounding();
  }


  void StlObject::load( std::ifstream& stream, bool binary ) {

    // Binary
    if( binary ) {

      // Read header
      char hbuff[80];
      stream.read( hbuff, 80 );

      _identity = hbuff;

      unsigned int facets;
      stream.read( (char*)&facets, sizeof( unsigned int ) );


      // Allocate memory
      _normals.setSize(facets);
      _vertices.setSize(_normals.getMaxSize()*3);

      // Read Normal and Vertices and Attribute bit of each face
      for( int i = 0; i < (int)facets; i++ ) {

        // Normal
        stream.read( (char*)&_normals[i], 3 * sizeof( unsigned int ) );

        // Vertices
        stream.read( (char*)&_vertices[i*3], 9 * sizeof( unsigned int ) );

        // Attribute
        unsigned short attrib = 0;
        stream.read( (char*)&attrib, sizeof( unsigned short ) );
      }
    }
  }


  void StlObject::save( std::ofstream& stream, bool binary ) {


    // Binary
    if( binary ) {

      std::stringstream header;
      header << "GMlib STL: " << this->getIdentity();

      char hbuff[80]; for( int i = 0; i < 80; i++ ) hbuff[i] = ' ';
      memcpy( hbuff, header.str().c_str(), header.str().length() );
      stream.write( hbuff, 80 );


      unsigned int facets = _normals.getSize();
      stream.write( (char*)&facets, sizeof( unsigned int ) );

      for( int i = 0; i < _normals.getSize(); i++ ) {

        // Normal
        stream.write( (char*)&_normals[i], 3 * sizeof( unsigned int ) );

        // Vertices
        stream.write( (char*)&_vertices[i*3], 9 * sizeof( unsigned int ) );

        // Attribute
        unsigned short attrib = 0;
        stream.write( (char*)&attrib, sizeof( unsigned short ) );
      }
    }
    else {

      std::stringstream content;
      content << "solid " << this->getIdentity() << std::endl;

      for( int i = 0; i < _normals.getSize(); i++ ) {

        const Vector<float,3> &v0 = _vertices(i*3);
        const Vector<float,3> &v1 = _vertices(i*3+1);
        const Vector<float,3> &v2 = _vertices(i*3+2);

        // Normal
        const Vector<float,3> &n = _normals(i);

        content << "  facet normal " << n(0) << " " << n(1) << " " << n(2) << std::endl;

          content << "    outer loop" << std::endl;


            // Vertices
            content << "      vertex " << v0(0) << " " << v0(1) << " " << v0(2) << std::endl;
            content << "      vertex " << v1(0) << " " << v1(1) << " " << v1(2) << std::endl;
            content << "      vertex " << v2(0) << " " << v2(1) << " " << v2(2) << std::endl;

          content << "    endloop" << std::endl;

        content << "  endfacet" << std::endl;
      }

      content << "endsolid " << this->getIdentity() << std::endl;

      stream.write( content.str().c_str(), content.str().length() * sizeof( char ) );
    }
  }


  void StlObject::setPointSize( float s ) {

    _point_size = s;
  }


}
