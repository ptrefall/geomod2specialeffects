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



/*! \file gmPoint3D.h
 *  File Description
 *
 *  \date   2008-07-02
 */

#ifndef __gmPOINT3D_H__
#define __gmPOINT3D_H__


// GMlib includes
#include "gmPoint.h"



namespace GMlib {



  /*! \class Point3D gmPoint3D.h <gmPoint3D.h>
   *
   *  \brief Point3D class
   *
   *  Detailed Description of class
   */
  template <typename T>
  class Point3D: public Point<T,3> {
  public:

   Point3D(T d=0);
   Point3D(const T p[3]);
   Point3D(const Point<T,3>& v);
   Point3D(const T& x,const T& y,const T& z);

   // Vector product.
   Point<T,3> operator^(const Point<T,3>& v)  const;

  }; // END class Point3D













  /*! \class  Vector3D gmPoint3D.h <gmPoint3D.h>
   *
   *  \brief  Vector3D class
   *
   *  Detailed Description of class
   */
  template <typename T>
  class Vector3D : public Vector<T,3>{
  public:
    Vector3D(T d=1);
    Vector3D(const T p[3]);
    Vector3D(const Point<T,3>& v);
    Vector3D(const T& x,const T& y,const T& z);

    // Vector product.
    Point<T,3> operator^(const Point<T,3>& v) const;

  }; // END class Vector3D












  /*! \class  UnitVector3D gmPoint3D.h <gmPoint3D.h>
   *
   *  \brief  UnitVector3D class
   *
   *  Detailed Description of class
   */
  template <typename T>
  class UnitVector3D : public UnitVector<T,3> {
  public:
    UnitVector3D(T d=1);
    UnitVector3D(const T p[3]);
    UnitVector3D(const Point<T,3>& v);
    UnitVector3D(const T& x,const T& y,const T& z);

    // Vector product.
    Point<T,3> operator ^ (const Point<T,3>& v) const;

  }; // END class UnitVector3D












  /*! \class  Plane3D gmPoint3D.h <gmPoint3D.h>
   *
   *  \brief  Plane3D class
   *
   *  Detailed Description of class
   */
  template <typename T, int n>
  class Plane3D : public Arrow<T,3> {
  public:
    Plane3D();
    Plane3D(const Point<T,3>& p);
    Plane3D(const Point<T,3>& p ,const Vector<T,n>& v);
    Plane3D(const Arrow<T,3>& a);

    void                setNormal(const Vector<T,3>& v);

    const Vector<T,3>&	getNormal() const;
    Point<T,3>          getClosestPoint(const Point<T,3>& p) const;
    Vector<T,3>         getDistanceVector(const Point<T,3>& p) const;
    T                   getDistanceTo(const Point<T,3>& p) const;

  }; // END class Plane

} // END namespace GMlib



// Include Point3D class implementations
#include "gmPoint3D_Point3D.c"

// Include Vector3D class implementations
#include "gmPoint3D_Vector3D.c"

// Include UnitVector3D class implementations
#include "gmPoint3D_UnitVector3D.c"

// Include Plane class implementations
#include "gmPoint3D_Plane3D.c"







#endif   // __gmPOINT3D_H__ */

