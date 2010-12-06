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
 *  \date   2008-07-08
 */

#ifndef __gmPOINT2D_H__
#define __gmPOINT2D_H__

#include "gmPoint.h"
#include "gmArray.h"


namespace GMlib {

  /*! \class  Point2D gmPoint2D.h <gmPoint2D.h>
   *
   *  \brief  Point2D class
   *
   *  Detailed Description of class
   */
  template <typename T>
  class Point2D : public Point<T,2> {
  public:

    Point2D(T d=0);
    Point2D(const T p[2]);
    Point2D(const Point<T,2>& v);
    Point2D(const Point<T,3>& v);
    Point2D(const T& x,const T& y);


    Point<T,2>  getNormal();  // Return a vector 90 deg. to this.
    int         isInside(const Point<T,2>& v1,const Point<T,2>& v2,const Point<T,2>& v3) const;
    int         isInside(const Array<Point<T,2> >&) const;
    int         isInsideCircle(const Point<T,2>&,const Point<T,2>&,const Point<T,2>&) const;


    T           operator^(const Point<T,2>& v) const;		// Semi vector product.

  }; // END class Point2D



  /*! \class  Vector2D gmPoint2D.h <gmPoint2D.h>
   *
   *  \brief  Vector2D class
   *
   *  Detailed Description of class
   */
  template <typename T>
  class Vector2D : public Vector<T,2>
  {
  public:
    Vector2D(T d=1);
    Vector2D(const T p[2]);
    Vector2D(const Point<T,2>& v);
    Vector2D(const T& x,const T& y);

    Point<T,2>  getNormal();              						  // Return a vector 90 deg. to this.

    T           operator^(const Point<T,2>& v) const;   // Semi vector product.

  }; // END class Vector2D



  /*! \class  UnitVector2D gmPoint2D.h <gmPoint2D.h>
   *
   *  \brief  UnitVector2D class
   *
   *  Detailed Description of class
   */
  template <typename T>
  class UnitVector2D : public UnitVector<T,2>
  {
  public:
    UnitVector2D(T d=1);
    UnitVector2D(const T p[2]);
    UnitVector2D(const Point<T,2>& v);
    UnitVector2D(const T& x,const T& y);

    Point<T,2>  getNormal();						                    // Return a vector 90 deg. to this.

    T           operator^(const Point<T,2>& v) const;        // Semi vector product.

  }; // END class UnitVector2D



  /*! bool Point2D<T>::convexHullFrom(Array<Point<T,2> >& a, const Vector2D<T>& v)
   *  \brief  Compute the convex hull of a point set
   *
   * This function compute the convex hull of a point
   * set stored in the array a.
   * The convex hull is also stored in the array a,
   * and it is a counter clockwise oriented polygon.
   * If the convex hull consist off all original points
   * from a then false is retuned else true is returned.
   */
  template <typename T>
  bool convexHullFrom(Array<Point<T,2> >& a, const Vector2D<T>& v) {

    bool removed = false;
    if (a.size()<4)	return removed;

    int i,j,k;
    Point2D<T> p;

    for(i=0; i<a.size(); i++) p += a[i];

    p.setTestType(3,p/a.size(),v);
    a.sort();

    for(i=0; i<a.size(); i++)	{
      if(i<a.size()-2)		{ j=i+1; k=i+2; }
      else if(i<a.size()-1)	{ j=i+1; k=0;   }
      else					{ j=0;   k=1;   }
      p = a[j]-a[i];
      if((p^(a[k]-a[j])) < 0)	{
        a.removeIndex(j);
        removed = true;
        if(i==a.size()) i-=3;
        else if(i>0)	i-=2;
        else			i--;
      }
    }
    return removed;
  }

} // end namespace GMlib

// Include Point2D class implementations
#include "gmPoint2D_Point2D.c"

// Include Vector2D class implementations
#include "gmPoint2D_Vector2D.c"

// Include UnitVector2D class implementations
#include "gmPoint2D_UnitVector2D.c"






#endif   /* __gmPOINT2D_H__ */
