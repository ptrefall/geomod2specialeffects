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



/*! \file gmPoint_UnitVector.c
 *  \brief Implementations for the UnitVector class
 *
 *  Implementations for the UnitVector class
 *
 *  \date   2008-06-19
 */

#include <iostream>

namespace GMlib {



  template <typename T, int n>
  inline
  UnitVector<T, n>::UnitVector( T t ) : Vector<T, n>(t) {
    Point<T, n>::operator/=(Point<T,n>::getLength());
  }


  template <typename T, int n>
  inline
  UnitVector<T, n>::UnitVector( const T t[n] ) : Vector<T, n>(t) {
    Point<T, n>::operator/=( Point<T,n>::getLength() );
  }


  template <typename T, int n>
  inline
  UnitVector<T, n>::UnitVector( const Point<T, n> &p ) : Vector<T,n>(p) {
    Point<T, n>::operator/=( Point<T,n>::getLength() );
  }


  template <typename T, int n>
  inline
  UnitVector<T, n>::UnitVector( const UnitVector<T, n> &uv ) : Vector<T, n>(uv) {}


  template <typename T, int n>
  inline
  Point<T, n>& UnitVector<T, n>::operator = ( const T t ) {
    _cpy(t);
    return Point<T,n>::operator/=( Point<T,n>::getLength() );
  }


  template <typename T, int n>
  inline
  Point<T, n>& UnitVector<T, n>::operator = ( const T t[n] ) {
    _cpy(t);
    return Point<T,n>::operator/=( Point<T,n>::getLength() );
  }


  template <typename T, int n>
  inline
  Point<T, n>& UnitVector<T, n>::operator = ( const Point<T, n> &p ) {
    _cpy(p);
    return Point<T,n>::operator/=( Point<T,n>::getLength() );
  }


  template <typename T, int n>
  inline
  Point<T, n>& UnitVector<T, n>::operator = ( const UnitVector<T, n>& uv )	{
    _cpy(uv);
    return *this;
  }


  template <typename T, int n>
  inline
  const T& UnitVector<T, n>::operator [] ( int i ) {
    return Point<T,n>::_pt[i];
  }


  template <typename T, int n>
  inline
  Point<T,n>& UnitVector<T, n>::operator += ( const Point<T, n> &p ) {
    Point<T,n>::operator += (p);
    return Point<T,n>::operator/=( Point<T,n>::getLength() );
  }


  template <typename T, int n>
  inline
  Point<T,n>& UnitVector<T, n>::operator -= ( const Point<T, n> &p ) {

    Point<T,n>::operator-=(p);
    return Point<T,n>::operator/=( Point<T,n>::getLength() );
  }


  template <typename T, int n>
  inline
  Point<T,n>& UnitVector<T, n>::operator %= ( const Point<T, n> &p ) {

    Point<T,n>::operator%=(p); return Point<T,n>::operator/=( Point<T,n>::getLength() );
  }


  template <typename T, int n>
  inline
  Point<T,n>& UnitVector<T, n>::operator *= ( const double d ) {

    return *this;
  }


  template <typename T, int n>
  inline
  Point<T,n>& UnitVector<T, n>::operator /= ( double d ) {

    return *this;
  }

}
