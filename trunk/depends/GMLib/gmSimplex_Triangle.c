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



/*! \file gmSimplex_Triangle.c
 *  File Description
 *
 *  \date   2008-06-17
 */


namespace GMlib {



  /*! Triangle<T,n,3>::Triangle()
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T, int n>
  inline
  Triangle<T,n>::Triangle() : Simplex<T,n,3>() {
  }

  /*! Triangle<T,n,3>::Triangle(const Point<T,n>& p)
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T, int n>
  inline
  Triangle<T,n>::Triangle(const Point<T,n>& p) : Simplex<T,n,3>(p) {
  }

  /*! Triangle<T,n,3>::Triangle(const Arrow<T,n>& a)
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T, int n>
  inline
  Triangle<T,n>::Triangle(const Point<T,n>& p ,const Vector<T,n>& v) : Simplex<T,n,3>(p,v) {
  }

  /*! Triangle<T,n,3>::Triangle(const Arrow<T,n>& a)
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T, int n>
  inline
  Triangle<T,n>::Triangle(const Arrow<T,n>& a) :  Simplex<T,n,3>(a) {
  }

  /*! Triangle<T,n,3>::Triangle(const SubSpace<T,n,2>& s)
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T, int n>
  inline
  Triangle<T,n>::Triangle(const SubSpace<T,n,2>& s): Simplex<T,n,3>(s) {
  }

  /*! Triangle<T,n,3>::Triangle(const Vector<Point<T,n>,3>& s)
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T, int n>
  inline
  Triangle<T,n>::Triangle(const Vector<Point<T,n>,3>& s) :  Simplex<T,n,3>(s)	{
  }

}
