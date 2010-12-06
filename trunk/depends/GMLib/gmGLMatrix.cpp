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



/*! \file gmGLMatrix.cpp
 *  \brief GLMatrix class implementations
 *
 *  Implementation of the GLMatrix class (non inline).
 *  (previously located in: <gmOpenGL_GLMatrix.cpp>)
 *
 *  \date   2010-04-14 (2008-08-03)
 */


// header
#include "gmGLMatrix.h"

namespace GMlib {


  /*! Point<float,3> GLMatrix::operator *(const Point<float,3>& p) const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  Point<float,3> GLMatrix::operator *(const Point<float,3>& p) const {

    Point<float,3> lp;

    lp[0] = _matrix[0]*p(0) + _matrix[4]*p(1) + _matrix[8]*p(2)  + _matrix[12];
    lp[1] = _matrix[1]*p(0) + _matrix[5]*p(1) + _matrix[9]*p(2)  + _matrix[13];
    lp[2] = _matrix[2]*p(0) + _matrix[6]*p(1) + _matrix[10]*p(2) + _matrix[14];
    return lp;
  }


  /*! Vector<float,3> GLMatrix::operator *(const Vector<float,3>& p) const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  Vector<float,3> GLMatrix::operator *(const Vector<float,3>& p) const {

    Point<float,3> lp;
    lp[0] = _matrix[0]*p(0) + _matrix[4]*p(1) + _matrix[8]*p(2);
    lp[1] = _matrix[1]*p(0) + _matrix[5]*p(1) + _matrix[9]*p(2);
    lp[2] = _matrix[2]*p(0) + _matrix[6]*p(1) + _matrix[10]*p(2);
    return lp;
  }


  /*! Arrow<float,3> GLMatrix::operator *(const Arrow<float,3>& b) const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  Arrow<float,3> GLMatrix::operator *(const Arrow<float,3>& b) const {

    Arrow<float,3> lp;
    lp.setPos((*this)*b.getPos());
    lp.setDir((*this)*b.getDir());
    return lp;
  }


  /*! Box<float,3> GLMatrix::operator *(const Box<float,3>& b) const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  Box<float,3> GLMatrix::operator *(const Box<float,3>& b) const {

    Box<float,3> lp;
    Point<float,3> p = b.getPointMin();
    p *= (*this);
    lp.reset(p);
    p = b.getPointMax();
    p *= (*this);
    lp += p;
    return lp;
  }


  /*! Sphere<float,3> GLMatrix::operator *(const Sphere<float,3>& b) const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  Sphere<float,3> GLMatrix::operator *(const Sphere<float,3>& b) const {

    Sphere<float,3> lp;
    if(b.isValid())
    {
      Point<float,3> p = b.getPos();
      p *= (*this);
      lp.resetPos(p);
      Vector<float,3> v;
      v[0]= b.getRadius(); v[1] = v[2] = 0.0;
      v *= (*this);
      lp.resetRadius(v.getLength());
    }
    return lp;
  }


} // END namespace GMlib
