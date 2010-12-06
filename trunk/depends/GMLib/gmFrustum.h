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



/*! \file gmFrustum.h
 *
 *  Frustum class definitions
 *  (previously located in <gmOpenGL.h>
 *
 *  \date   2010-04-14 (2008-08-03)
 */


#ifndef __GMFRUSTUM_H__
#define __GMFRUSTUM_H__

// local
#include "gmPoint.h"
#include "gmMatrix.h"


namespace GMlib {


  /*! \class Frustum
   *  \brief  Pending Documentation
   *
   *  A class to describe a frutrum to a perspectiv or isometric view.
   */
  class Frustum {
  public:
    Frustum();                          // Default constructor
    Frustum(                            // Standar perspective constructor
      const HqMatrix<float,3>& m,
      const Point<float,3>& p,
      const Vector<float,3>& d,
      const Vector<float,3>& u,
      const Vector<float,3>& s,
      float angle_tan,
      float ratio,
      float nearplane,
      float farplane);

    Frustum(
      const HqMatrix<float,3>& m,       // Iso constructor
      const Point<float,3>& p,
      float width,
      float ratio,
      const Vector<float,3>& d,
      const Vector<float,3>& u,
      const Vector<float,3>& s,
      float nearplane,
      float farplane);

    Frustum(const Frustum&  v);

    void              set(              // Perspective
      const HqMatrix<float,3>& m,
      const Point<float,3>& p,
      const Vector<float,3>& d,
      const Vector<float,3>& u,
      const Vector<float,3>& s,
      float angle_tan,
      float ratio,
      float nearplane,
      float farplane);

    void              set(              // Iso
      const HqMatrix<float,3>& m,
      const Point<float,3>& p,
      float width,
      float ratio,
      const Vector<float,3>& d,
      const Vector<float,3>& u,
      const Vector<float,3>& s,
      float nearplane,
      float farplane);

    Point<float,3>    getPos(int i) const;
    Vector<float,3>   getNormal(int i) const;

    int               isInterfering(const Sphere<float,3>& s) const;

  private:
    Point<float,3>    _p[2];	// p[0]: høyre/opp/bak-hjørne  p[1]: venstre/ned/foran-hjørne
    Vector<float,3>   _v[6];	// normal: venstre, høyre, opp, ned, bak, fram.

  }; // END class Frustum

} // END namespace GMlib

// Include inline Frustum class implementations
#include "gmFrustum.c"


#endif // __GMFRUSTUM_H__
