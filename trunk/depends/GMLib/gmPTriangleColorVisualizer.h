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



/*! \file gmPTriangleColorVisualizer.h
 *
 *  Interface for the PTriangleColorVisualizer class.
 *
 *  \date   2010-06-19
 */


#ifndef __gmPTRIANGLECOLORVISUALIZER_H__
#define __gmPTRIANGLECOLORVISUALIZER_H__


#include <gmPoint.h>
#include <gmDVector.h>
#include <gmDMatrix.h>
#include <gmPTriangleVisualizer.h>
#include <gmOpenGL.h>

namespace GMlib {


  enum GM_PTRIANGLE_COLORVISUALIZER_COLOR_MODE {
    GM_PTRIANGLE_COLORVISUALIZER_HSV,
    GM_PTRIANGLE_COLORVISUALIZER_RGB
  };


  template <typename T>
  class PTriangleColorVisualizer : public PTriangleVisualizer<T> {
  public:
    PTriangleColorVisualizer();
    ~PTriangleColorVisualizer();

    void        display();
    GM_PTRIANGLE_COLORVISUALIZER_COLOR_MODE
                getColorMode() const;
    void        getColors( Color& c1, Color& c2, Color& c3 );
    void        replot(
        DVector< DMatrix< Vector<T,3> > >& p,
        int m
        );
    void        setColorMode( GM_PTRIANGLE_COLORVISUALIZER_COLOR_MODE color_mode );
    void        setColors( const Color& c1, const Color& c2, const Color& c3 );
    void        setTranslucency( double a );

  protected:
    GM_PTRIANGLE_COLORVISUALIZER_COLOR_MODE
                _color_mode;
    GLuint      _vbo_color;

    Color       _c1;
    Color       _c2;
    Color       _c3;

  }; // END class PTriangleColorVisualizer

} // END namespace GMlib


// Include PTriangleColorVisualizer class function implementations
#include "gmPTriangleColorVisualizer.c"

#endif // __gmPTRIANGLECOLORVISUALIZER_H__
