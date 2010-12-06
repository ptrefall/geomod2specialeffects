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



/*! \file gmArray.h
 *
 *  Interface for the Array classes.
 *
 *  \date   2008-07-02
 */


#ifndef __gmSTLOBJECT_H__
#define __gmSTLOBJECT_H__


#include <string>

#include "gmDisplayObject.h"
#include "gmArrayLX.h"
#include "gmPSphere.h"


namespace GMlib {


  template <typename T>
  class TSVertex;


  enum GM_STL_VISUALIZATION {
    GM_STL_POINT,
    GM_STL_TRIANGLE
  };


  class StlObject : public DisplayObject {
  public:
    StlObject( const std::string& filename, const Color& color = 5, int flip = 1 ); // From file, in given color
    StlObject( std::ifstream& stream, bool binary = true, const Color& color = GMcolor::Aqua );
    StlObject( PSurf<float> *obj, int m1 = 20, int m2 = 20, GM_STL_VISUALIZATION gsv = GM_STL_TRIANGLE );
    StlObject( float r = 10 );				 // Makes a Sphere, just for debugging
    ~StlObject();

    std::string                       getIdentity() const;
    unsigned int                      getNoNormals() const;
    unsigned int                      getNoPoints() const;
    Array< Vector<float,3> >          getNormals();
    const Array< Vector<float,3> >&   getNormals() const;
    Array<Point<float,3> >            getPoints();
    const Array<Point<float,3> >&     getPoints() const;
    float                             getPointSize();
    ArrayLX< TSVertex<float> >          getVertices();

    void                              load( std::ifstream& stream, bool binary = true );
    void                              replot( GM_STL_VISUALIZATION gsv = GM_STL_TRIANGLE );
    void                              save( std::ofstream& stream, bool binary = true );
    void                              setPointSize( float s = 5.0 );

  protected:
    void                              localDisplay();
    void                              localSelect();


  private:
    float                             _getFloat();
    unsigned int                      _getUint();
    unsigned long                     _getUli();
    int                               _readStlBinary( const std::string& filename );
    void                              _updateBounding();
    void                              _makeList( GLenum e = GL_TRIANGLES );
    void                              _init();

    unsigned int                      _dlist;
    PSphere<float>                    *_sphere;         // Debug

    std::string                       _identity;				// I put the filename in here,
    FILE*                             _stl_file;

    Array<Point<float,3> >            _vertices;        // storage, each three makes a triangle
    Array<Vector<float,3> >           _normals;         // with one normal for each triangle
    Box<float,3>                      _bbox;					  // Bounding box, should be an options
    float                             _point_size;

    // binary file utility functions to render it.


  };

}


// Include inline function implementations
#include "gmStlObject.c"



#endif // __gmSTLOBJECT_H__




