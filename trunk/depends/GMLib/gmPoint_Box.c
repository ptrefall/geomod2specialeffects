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



/*! \file gmPoint_Box.c
 *  Implementations for the Box class
 *
 *  \date   2008-06-20
 */


namespace GMlib {



  template <typename T, int n>
  inline
  Box<T, n>::Box() {
    _min = _max = (T) 0;
  }

  template <typename T, int n>
  inline
  Box<T, n>::Box( const Point<T, n>& p ) {
    _min = _max = p;
  }

  template <typename T, int n>
  inline
  Box<T, n>::Box( const Box<T, n>& b ) {
    _min = b._min;
    _max = b._max;
  }

  template <typename T, int n>
  inline
  Box<T, n>::Box( const Point<T, n>& p1, const Point<T, n>& p2 )	{
    _min = _max = p1;
    insert(p2);
  }

  template <typename T, int n>
  inline
  Box<T, n>::Box( const Point<T, n>& p1, const Point<T, n>& p2, const Point<T,n>& p3 ) {
    _min = _max = p1;
    insert(p2);
    insert(p3);
  }

  template <typename T, int n>
  inline
  Point<T, n>	Box<T, n>::getPointMin() const {
    return _min;
  }

  template <typename T, int n>
  inline
  Point<T, n>	Box<T, n>::getPointMax() const {
    return _max;
  }

  template <typename T, int n>
  inline
  Point<T, n>	Box<T, n>::getPointCenter() const {
    return (_max + _min)*0.5;
  }

  template <typename T, int n>
  inline
  Vector<T, n>	Box<T, n>::getPointDelta() const {
    return _max - _min;
  }

  template <typename T, int n>
  inline
  T* Box<T, n>::getPtr() const {
    return (T*)this;
  }

  template <typename T, int n>
  inline
  T&		Box<T, n>::getValueAt( int i, int j ) {
    return i == 0 ? _min[j] : _max[j];
  }

  template <typename T, int n>
  inline
  T Box<T, n>::getValueMin( int i ) const	{
    return _min(i);
  }

  template <typename T, int n>
  inline
  T Box<T, n>::getValueMax( int i ) const	{
    return _max(i);
  }

  template <typename T, int n>
  inline
  T Box<T, n>::getValueCenter( int i ) const {
    return (_max(i) + _min(i))*0.5;
  }

  template <typename T, int n>
  inline
  T Box<T, n>::getValueDelta( int i ) const {
    return _max(i) - _min(i);
  }

  template <typename T, int n>
  void Box<T, n>::insert( const Point<T, n>& p) {
    for(int i=0;i<n;i++)
    {
      if(p(i) < _min[i]) _min[i] = p(i);
      if(p(i) > _max[i]) _max[i] = p(i);
    }
  }


  template <typename T, int n>
  void Box<T, n>::insert( const Box<T, n>& b) {
    for(int i=0;i<n;i++)
    {
      if(b._min(i) < _min[i]) _min[i] = b._min(i);
      if(b._max(i) > _max[i]) _max[i] = b._max(i);
    }
  }

  template <typename T, int n>
  bool Box<T, n>::isIntersecting( const Box<T,n>& b ) const {
    for(int i=0;i<n;i++)
    {
      if(b._min(i) > _max(i)) return false;
      if(b._max(i) < _min(i)) return false;
    }
    return true;
  }

  template <typename T, int n>
  bool Box<T, n>::isSurrounding( const Point<T,n>& p ) const {
    for(int i=0;i<n;i++)
    {
      if(p(i) < _min(i)) return false;
      if(p(i) > _max(i)) return false;
    }
    return true;
  }

  template <typename T, int n>
  bool Box<T, n>::isSurrounding( const Box<T,n>& b )  const {
    for(int i=0;i<n;i++)
    {
      if(b._min(i) < _min(i)) return false;
      if(b._max(i) > _max(i)) return false;
    }
    return true;
  }

  template <typename T, int n>
  inline
  void Box<T, n>::reset() {
    reset( Point<T, n>( (T)0 ) );
  }

  template <typename T, int n>
  inline
  void Box<T, n>::reset( const Point<T, n>& p ) {
    _min = _max = p;
  }

  template <typename T, int n>
  inline
  Box<T,n>&	Box<T, n>::operator += ( const Point<T, n>& p ) {
    insert(p);
    return *this;
  }

  template <typename T, int n>
  inline
  Box<T,n> Box<T, n>::operator +  ( const Point<T, n>& p ) {
    Box<T,n> a=(*this);
    a+=p;
    return a;
  }

  template <typename T, int n>
  inline
  Box<T,n>&	Box<T, n>::operator += ( const Box<T, n>& b ) {
    insert(b);
    return *this;
  }

  template <typename T, int n>
  inline
  Box<T,n> Box<T, n>::operator +  ( const Box<T, n>& b ) {
    Box<T,n> a=(*this);
    a+=b;
    return a;
  }

}
