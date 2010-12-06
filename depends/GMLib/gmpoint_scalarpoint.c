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



/*! \file gmPoint_ScalarPoint.c
 *  \brief Implementations for the ScalarPoint class
 *
 *  Implementations for the ScalarPoint class
 *
 *  \date   2008-06-20
 */


namespace GMlib {



  template <typename T, int n>
  inline
  ScalarPoint<T, n>::ScalarPoint() : _pos( T(0) ), _value( T(0) ) {}


  template <typename T, int n>
  inline
  ScalarPoint<T, n>::ScalarPoint( const Point<T, n>& p, T v )	{
    _pos = p;
    _value = v;
  }

  template <typename T, int n>
  inline
  ScalarPoint<T, n>::ScalarPoint( const ScalarPoint<T, n>& s )			{
    _pos = s._pos;
    _value = s._value;
  }

  template <typename T, int n>
  inline
  Point<T, n> ScalarPoint<T, n>::getPos() const {
    return _pos;
  }

  template <typename T, int n>
  inline
  T* ScalarPoint<T, n>::getPtr() const {
    return (T*)this;
  }

  template <typename T, int n>
  inline
  T ScalarPoint<T, n>::getValue() const {
    return _value;
  }

  template <typename T, int n>
  inline
  void ScalarPoint<T, n>::reset( const Point<T, n>& p , T v )	{
    _pos = p;
    _value = v;
  }

  template <typename T, int n>
  inline
  void ScalarPoint<T, n>::reset() {
    _pos = (T)0;
    _value = (T)0;
  }

  template <typename T, int n>
  inline
  void ScalarPoint<T, n>::resetValue( T t ) {
    _value = t;
  }

  template <typename T, int n>
  inline
  void ScalarPoint<T, n>::resetPos( const Point<T, n>& p ) {
    _pos = p;
  }

  template <typename T, int n>
  inline
  ScalarPoint<T, n>& ScalarPoint<T, n>::operator += ( const Point<T, n>& p ) {
    _pos += p;
    return *this;
  }

  template <typename T, int n>
  inline
  ScalarPoint<T, n>  ScalarPoint<T, n>::operator +  ( const Point<T, n>& p ) const	{
    ScalarPoint<T,n> a=(*this);
    a+=p;
    return a;
  }

  template <typename T, int n>
  inline
  ScalarPoint<T, n>& ScalarPoint<T, n>::operator += ( T p ) {
    _value += p;
    return *this;
  }

  template <typename T, int n>
  inline
  ScalarPoint<T, n>  ScalarPoint<T, n>::operator +  ( T p ) const {
    ScalarPoint<T,n> a=(*this);
    a+=p;
    return a;
  }

  template <typename T, int n>
  inline
  ScalarPoint<T, n>& ScalarPoint<T, n>::operator += ( const ScalarPoint<T, n>& p ) {
    _pos += p._pos;
    _pos /= 2.0;
    _value += p._value;
    _value /= 2.0;
    return *this;
  }

  template <typename T, int n>
  inline
  ScalarPoint<T, n>  ScalarPoint<T, n>::operator +  ( const ScalarPoint<T, n>& p ) const {
    ScalarPoint<T,n> a=(*this);
    a+=p;
    return a;
  }

  template <typename T, int n>
  inline
  ScalarPoint<T, n>& ScalarPoint<T, n>::operator *= ( double d ) {
    _value *= (T)d;
    return *this;
  }

  template <typename T, int n>
  inline
  ScalarPoint<T, n>  ScalarPoint<T, n>::operator *  ( double d ) const {
    ScalarPoint<T,n> a=(*this);
    a*=d;
    return a;
  }

  template <typename T, int n>
  inline
  ScalarPoint<T, n>& ScalarPoint<T, n>::operator /= ( double d ) {
    _value /= d;
    return *this;
  }

  template <typename T, int n>
  inline
  ScalarPoint<T, n>  ScalarPoint<T, n>::operator /  ( double d ) const {
    ScalarPoint<T,n> a=(*this);
    a/=d;
    return a;
  }

  template <typename T, int n>
  inline
  ScalarPoint<T, n>& ScalarPoint<T, n>::operator %= ( const Point<T, n>& p ) {
    _pos %= p;
    return *this;
  }

  template <typename T, int n>
  inline
  ScalarPoint<T, n>  ScalarPoint<T, n>::operator %  ( const Point<T, n>& p ) const	{
    ScalarPoint<T,n> a=(*this);
    a%=p;
    return a;
  }

}
