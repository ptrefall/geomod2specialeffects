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



/*! \file gmPSurfNormalsVisualizer.h
 *
 *  Interface for the PSurfNormalsVisualizer class.
 *
 *  \date   2010-04-13
 */


#ifndef __GMPSURFNORMALSVISUALIZER_H__
#define __GMPSURFNORMALSVISUALIZER_H__


#include "gmPoint.h"
#include "gmDVector.h"
#include "gmDMatrix.h"
#include "gmColor.h"
#include "gmPSurfVisualizer.h"


namespace GMlib {

  template <typename T>
  class PSurfNormalsVisualizer : public PSurfVisualizer<T> {
  public:
    PSurfNormalsVisualizer();
    ~PSurfNormalsVisualizer();

    void                          display();
    const Color&                  getColor() const;
    std::string                   getIdentity() const;
    double                        getSize() const;
    void                          replot(
      DMatrix< DMatrix< Vector<T, 3> > >& p,
      DMatrix< Vector<T, 3> >& normals,
      int m1, int m2, int d1, int d2
    );
    void                          setColor( const Color& color );
    void                          setSize( double size = 1.0 );

  public:
    GLuint                        _vbo;
    int                           _no_elements;

    Color                         _color;
    double                        _size;


  };

} // END namespace GMlib

// Include PSurfNormalsVisualizer class function implementations
#include "gmPSurfNormalsVisualizer.c"





#endif // __GMPSURFNORMALSVISUALIZER_H__
