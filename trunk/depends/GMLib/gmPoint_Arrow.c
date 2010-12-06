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



/*! \file gmPoint_Arrow.c
 *  Implementations for the Arrow class
 *
 *  \date   2008-06-19
 */



namespace GMlib {



  template <typename T, int n>
  inline
  Arrow<T, n>::Arrow() : Point<T, n>()	{
    _dir = Vector<T,n>(1);
  }

  template <typename T, int n>
  inline
  Arrow<T, n>::Arrow( const Point<T, n> &p ) : Point<T, n>(p) {
    _dir = Vector<T,n>(1);
  }

  template <typename T, int n>
  inline
  Arrow<T, n>::Arrow( const Point<T, n> &p, const Vector<T, n> &v ) : Point<T,n>(p) {
    _dir = v;
  }

  template <typename T, int n>
  inline
  Arrow<T, n>::Arrow( const Arrow<T, n> &a ) : Point<T, n>(a) {
    _dir = a._dir;
  }

  template <typename T, int n>
  inline
  const Vector<T, n>& Arrow<T, n>::getDir() const {
    return _dir;
  }

  template <typename T, int n>
  inline
  const Point<T, n>&  Arrow<T, n>::getPos() const {
    return (*this);
  }

  template <typename T, int n>
  inline
  void Arrow<T, n>::setDir( const Vector<T, n> &v ) {
    _dir = v;
  }

  template <typename T, int n>
  inline
  void Arrow<T, n>::setPos( const Point<T, n> &v ) {
    _cpy(v);
  }

  template <typename T, int n>
  inline
  Arrow<T, n>& Arrow<T, n>::operator = ( const Arrow<T, n> &a ) {
    memcpy( Point<T, n>::getPtr(), a.getPtr(), sizeof( Arrow<T, n> ) );
    return *this;
  } // setPos(v.pos()); setDir(v.dir()); return *this;}

  template <typename T, int n>
  inline
  Arrow<T, n>& Arrow<T, n>::operator += ( const Point<T, n> &p ) {
    Point<T, n>::operator += (p);
    return *this;
  }

  template <typename T, int n>
  inline
  Arrow<T, n>& Arrow<T, n>::operator -= ( const Point<T, n> &p ) {
    Point<T,n>::operator-=(p);
    return *this;
  }

  template <typename T, int n>
  inline
  Arrow<T, n> Arrow<T, n>::operator + ( const Point<T, n> &p ) const {
    //Point<T, n> r = (*this);
    Arrow<T, n> r = (*this);
    return r += p;
  }

  template <typename T, int n>
  inline
  Arrow<T, n> Arrow<T, n>::operator - ( const Point<T, n> &p ) const {
    //Point<T,n> r = (*this);
    Arrow<T,n> r = (*this);
    return r -= p;
  }

  template <typename T, int n>
  inline
  Arrow<T, n>& Arrow<T, n>::operator += ( const Vector<T, n> &v ) {
    _dir += v;
    return (*this);
  }

  template <typename T, int n>
  inline
  Arrow<T, n>& Arrow<T, n>::operator -= ( const Vector<T, n> &v ) {
    _dir -= v;
    return (*this);
  }

  template <typename T, int n>
  inline
  Arrow<T, n> Arrow<T, n>::operator + ( const Vector<T, n> &v ) const {
    //Point<T, n> r = (*this);
    Arrow<T, n> r = (*this);
    return r += v;
  }

  template <typename T, int n>
  inline
  Arrow<T, n> Arrow<T, n>::operator - ( const Vector<T, n> &v ) const {
    //Point<T, n> r = (*this);
    Arrow<T, n> r = (*this);
    return r -= v;
  }

  template <typename T, int n>
  inline
  Arrow<T, n> Arrow<T, n>::operator - () const {
    Point<T, n> p = -(*this);
    return p;
  }

  template <typename T, int n>
  template <class G, int m>
  inline
  Arrow<T, n>::operator Arrow<G, m>& () const {
    static Arrow<G,m> v;
    GM_Static1_<G,T,(n<m?n:m)>::eq( v.getPtr(), Point<T, n>::getPtr());
    GM_Static1_<G,T,(n<m?n:m)>::eq( v.getDir().getPtr(), _dir.getPtr());
    return v;
  }

  template <typename T, int n>
  inline
  Arrow<float, n>& Arrow<T, n>::toFloat() const {
    static Arrow<float,n> v;
    GM_Static1_<float,T,n>::eq( v.getPtr(), Point<T, n>::getPtr() );
    GM_Static1_<float,T,n>::eq( v.getDir().getPtr(), Point<T, n>::getPtr() );
    return v;
  }

  template <typename T, int n>
  inline
  Arrow<double, n>& Arrow<T, n>::toDouble() const
  {
    static Arrow<double,n> v;
    GM_Static1_<double,T,n>::eq( v.getPtr(), Point<T, n>::getPtr());
    GM_Static1_<double,T,n>::eq( v.getDir().getPtr(), Point<T, n>::getPtr());
    return v;
  }

}
