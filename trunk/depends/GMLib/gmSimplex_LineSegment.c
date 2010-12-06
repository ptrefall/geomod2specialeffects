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



/*! \file gmSimplex_LineSegment.c
 *  File Description
 *
 *  \date   2008-06-17
 */


namespace GMlib {



  /*! LineSegment<T,n,2>::LineSegment()
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T, int n>
  inline
  LineSegment<T,n>::LineSegment() : Simplex<T,n,2>() {
  }

  /*! LineSegment<T,n,2>::LineSegment(const Point<T,n>& p)
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */

  template <typename T, int n>
  inline
  LineSegment<T,n>::LineSegment(const Point<T,n>& p) : Simplex<T,n,2>(p) {
  }

    /*! LineSegment<T,n,2>::LineSegment(const Point<T,n>& p1 ,const Point<T,n>& p2)
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T, int n>
  inline
  LineSegment<T,n>::LineSegment(const Point<T,n>& p1 ,const Point<T,n>& p2) : Simplex<T,n,2>(p1,p2) {
  }

    /*! LineSegment<T,n,2>::LineSegment(const Arrow<T,n>& a)
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T, int n>
  inline
  LineSegment<T,n>::LineSegment(const Arrow<T,n>& a) :  Simplex<T,n,2>(a) {
  }

    /*! LineSegment<T,n,2>::LineSegment(const SubSpace<T,n,1>& s)
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T, int n>
  inline
  LineSegment<T,n>::LineSegment(const SubSpace<T,n,1>& s) :  Simplex<T,n,2>(s) {
  }

    /*! LineSegment<T,n,2>::LineSegment(const Vector<Point<T,n>,1>& s)
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T, int n>
  inline
  LineSegment<T,n>::LineSegment(const Vector<Point<T,n>,1>& s) :  Simplex<T,n,2>(s)	{}

}
