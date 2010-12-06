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



/*! \file gmPCurveVisualizer.h
 *
 *  Interface for the PCurveVisualizer class.
 *
 *  \date   2010-04-13
 */


#ifndef __GMPCURVEVISUALIZER_H__
#define __GMPCURVEVISUALIZER_H__

#include "gmPoint.h"
#include "gmDVector.h"
#include "gmVisualizer.h"
#include "gmOpenGL.h"


namespace GMlib {

  template <typename T>
  class PCurve;

  template <typename T>
  class PCurveVisualizer : public Visualizer {
  public:
    PCurveVisualizer();
    ~PCurveVisualizer();

    void          display();
    std::string   getIdentity() const;
    virtual void  replot(
      DVector< DVector< Vector<T, 3> > >& p,
      int m, int d
    );
    void          select();
    void          set( SceneObject* obj );

  protected:
    PCurve<T>     *_curve;

    GLuint        _vbo;
    int           _no_vertices;

  };







} // END namespace GMlib

// Include PCurveVisualizer class function implementations
#include "gmPCurveVisualizer.c"


#endif // __GMPCURVEVISUALIZER_H__
