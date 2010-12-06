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



/*! \file gmSubSpace_Cube.c
 *  \brief Implementation of the Static Cube template class.
 *
 *  Implementation of the Static Cube template class.
 *
 *  \date   2008-07-08
 */


#include "gmPoint.h"


namespace GMlib {



  /*!
   *  \brief  Default constructor
   */
  template <class T, int n>
  inline
  Cube<T,n>::Cube() : SubSpace<T,n,3>() {
  }


  /*!
   *  \brief  Default constructor
   */
  template <class T, int n>
  inline
  Cube<T,n>::Cube( const Point<T,n>& p ) : SubSpace<T,n,3>(p) {
  }


  /*!
   *  \brief  Default constructor
   */
  template <class T, int n>
  inline
  Cube<T,n>::Cube( const Point<T,n>& p, const Vector<T,n>& v ) : SubSpace<T,n,3>(p,v) {
  }


  /*!
   *  \brief  Default constructor
   */
  template <class T, int n>
  inline
  Cube<T,n>::Cube( const Arrow<T,n>& a ) :  SubSpace<T,n,3>(a) {
  }


  /*!
   *  \brief  Default constructor
   */
  template <class T, int n>
  inline
  Cube<T,n>::Cube( const SubSpace<T,n,3>& s ) : SubSpace<T,n,3>(s) {
  }

}
