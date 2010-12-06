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



/*! \file gmPoint2D_Point2D.c
 *  File Description
 *
 *  \date   2008-07-08
 */



namespace GMlib {



  /*! int Point2D<T>::isInside(const Point<T,2>& v1,const Point<T,2>& v2,const Point<T,2>& v3) const
   *  \brief  Check if point is inside polygon
   *
   * See if this point is inside a closed polygon
   * If it is inside the return value is 1.
   * If it is on the edges the return value is -n,
   * where n is the nuber on the actual edge.
   * If it is outside the polygon the retun value is 0.
   */
  template <typename T>
  int Point2D<T>::isInside(const Array<Point<T,2> >& a) const{
    Array<int> v;
    double r;

    for (int i=0,j=1; i<a.size(); i++,j++) {
      if (j == a.size())	j = 0;
      UnitVector2D<T> b = a(j) - a(i);
      r = b^((*this) - a(i));
      if (r < - POS_TOLERANCE)		return 0;
      if (std::fabs(r) < POS_TOLERANCE)	v += -i-1;
    }

    if (v.size() == 0)	return 1;
    else				return v[0];
  }


  /*! int Point2D<T>::isInside(const Point<T,2>& v1,const Point<T,2>& v2,const Point<T,2>& v3) const
   *  \brief  Check if point is inside circle
   *
   * See if this point is inside a circle defined
   * by tree points on the circle.
   * If it is inside the circle the return value is true
   * else it is false.
   */
  template <typename T>
  int  Point2D<T>::isInsideCircle(const Point<T,2>& p1,const Point<T,2>& p2, const Point<T,2>& p3) const {
    T b1 = p1*p1;
    T b2 = p2*p2;
    T b3 = p3*p3;

    Point2D<T> b(b2-b1,b3-b2);
    Point2D<T> a1 = p2 - p1;
    Point2D<T> a2 = p3 - p2;

    Point2D<T> c = (0.5/(a1^a2))*
            Point2D<T>(Point2D<T>(a2[1],-a1[1])*b,Point2D<T>(-a2[0],a1[0])*b);
    a1 = (*this) - c;
    a2 = p1 - c;

    T r = a1*a1;
    T s = a2*a2;

    if (std::fabs(r-s) < POS_TOLERANCE)	return -1;
    else if (r < s)					return  1;
    else							return  0;
  }


  /*! Point2D<T>::Point2D(T d=0)
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T>
  inline
  Point2D<T>::Point2D(T d) : Point<T,2>(d) {}


  /*! Point2D<T>::Point2D(const T p[2])
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T>
  inline
  Point2D<T>::Point2D(const T p[2]) : Point<T,2>(p) {}


  /*! Point2D<T>::Point2D(const Point<T,2>& v)
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T>
  inline
  Point2D<T>::Point2D(const Point<T,2>& v) : Point<T,2>(v) {}


  /*! Point2D<T>::Point2D(const Point<T,3>& v)
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T>
  inline
  Point2D<T>::Point2D(const Point<T,3>& v) {
    this->_pt[0] = v(0);
    this->_pt[1] = v(1);
  }

  /*! Point2D<T>::Point2D(const T& x,const T& y)
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T>
  inline
  Point2D<T>::Point2D(const T& x,const T& y) {
    this->_pt[0]=x;
    this->_pt[1]=y;
  }

  /*! T Point2D<T>::operator^(const Point<T,2>& v) const
   *  \brief  Operator ^ Semi vector product.
   *
   *  Detailed description of
   *  the operator
   */
  template <typename T>
  inline
  T Point2D<T>::operator^(const Point<T,2>& v) const {
    return this->_pt[0]*v(1) - this->_pt[1]*v(0);
  }

  /*! Point<T,2> Point2D<T>::getNormal()
   *  \brief  Return a vector 90 deg. to this.
   *
   *  Detailed description of
   *  the operator
   */
  template <typename T>
  inline
  Point<T,2> Point2D<T>::getNormal() {
    return Point2D<T>(-this->_pt[1], this->_pt[0]);
  }

  /*! int Point2D<T>::isInside(const Point<T,2>& v1,const Point<T,2>& v2,const Point<T,2>& v3) const
   *  \brief
   *
   *  Detailed description of
   *  the function
   */
  template <typename T>
  inline
  int Point2D<T>::isInside(const Point<T,2>& v1,const Point<T,2>& v2,const Point<T,2>& v3) const {
    Array<Point<T,2> > arr;
    arr+=v1;
    arr+=v2;
    arr+=v3;
    return isInside(arr);
  }

}// end namespace GMlib


