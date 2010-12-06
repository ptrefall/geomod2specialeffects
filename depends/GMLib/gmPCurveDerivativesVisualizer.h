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



/*! \file gmPCurveDerivativesVisualizer.h
 *
 *  Interface for the PCurveDerivativesVisualizer class.
 *
 *  \date   2010-04-13
 */


#ifndef __GMPCURVEDERIVATIVESVISUALIZER_H__
#define __GMPCURVEDERIVATIVESVISUALIZER_H__


#include "gmPoint.h"
#include "gmDVector.h"
#include "gmColor.h"
#include "gmPCurveVisualizer.h"


namespace GMlib {

  enum GM_PCURVE_DERIVATIVESVISUALIZER_SIZE {
    GM_PCURVE_DERIVATIVESVISUALIZER_NORMALIZED,
    GM_PCURVE_DERIVATIVESVISUALIZER_RELATIVE,
    GM_PCURVE_DERIVATIVESVISUALIZER_ABSOLUTE,
  };


  template <typename T>
  class PCurveDerivativesVisualizer : public PCurveVisualizer<T> {
  public:
    PCurveDerivativesVisualizer();
    ~PCurveDerivativesVisualizer();

    void            display();
    const Color&    getColor() const;
    int             getDerivative() const;
    std::string     getIdentity() const;
    double          getSize() const;

    GM_PCURVE_DERIVATIVESVISUALIZER_SIZE
                    getMode() const;

    void            replot(
      DVector< DVector< Vector<T, 3> > >& p,
      int m, int d
    );
    void            setColor( const Color& color );
    void            setDerivative( int t = 1 );
    void            setMode( GM_PCURVE_DERIVATIVESVISUALIZER_SIZE mode );
    void            setSize( double size = 1.0 );

  protected:
    Color           _color;

    GLuint          _vbo;
    int             _no_elements;

    GM_PCURVE_DERIVATIVESVISUALIZER_SIZE
                    _mode;

    double          _size;
    int             _t;
  };



} // END namespace GMlib

// Include PCurveDerivativesVisualizer class function implementations
#include "gmPCurveDerivativesVisualizer.c"



#endif // __GMPCURVEDERIVATIVESVISUALIZER_H__
