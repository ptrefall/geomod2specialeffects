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



/*! \file gmPoint_Sphere.c
 *  \brief Implementations for the Sphere class
 *
 *  Implementations for the Sphere class
 *
 *  \date   2008-06-20
 */


namespace GMlib {


  template <typename T, int n>
  inline
  Sphere<T, n>::Sphere( bool valid ) : ScalarPoint<T,n>() {
    _valid = valid;
  }

  template <typename T, int n>
  inline
  Sphere<T, n>::Sphere( const Point<T, n>& p, T v ) : ScalarPoint<T,n>(p,v)	{
    _valid = true;
  }

  template <typename T, int n>
  inline
  Sphere<T, n>::Sphere( const ScalarPoint<T, n>& s ) : ScalarPoint<T,n>(s) {
    _valid = true;
  }

  template <typename T, int n>
  inline
  Sphere<T, n>::Sphere( const Sphere<T, n>& s ) : ScalarPoint<T,n>(s) {
    _valid = s._valid;
  }

  template <typename T, int n>
  inline
  T	Sphere<T, n>::getRadius() const	{
    return ScalarPoint<T, n>::_value;
  }

  template <typename T, int n>
  inline
  bool Sphere<T, n>::isValid() const {
    return _valid;
  }

  template <typename T, int n>
  bool Sphere<T, n>::isIntersecting(const Sphere<T,n>& p) const {
    if(ScalarPoint<T, n>::_valid && p._valid)
    {
      T d = (ScalarPoint<T, n>::_pos - p._pos).getLength();
      return (ScalarPoint<T, n>::_value+p._value) > d;
    }
    return false;
  }

  template <typename T, int n>
  inline
  void Sphere<T, n>::resetPos( const Point<T, n>& p )	{
    _valid = true;
    ScalarPoint<T,n>::resetPos(p);
  }

  template <typename T, int n>
  inline
  void Sphere<T, n>::resetRadius( T t ) {
    resetValue(t);
  }

  template <typename T, int n>
  inline
  void Sphere<T, n>::reset() {
    _valid = false;
    ScalarPoint<T,n>::reset();
  }

  template <typename T, int n>
  Sphere<T, n>& Sphere<T, n>::operator += ( const Point<T, n>& p ) {
    if(_valid)
    {
      Vector<T,n> v = p - ScalarPoint<T, n>::_pos;
      T r, d = v.getLength();

      if (d > ScalarPoint<T, n>::_value)
      {
        r		= (d+ScalarPoint<T, n>::_value)/2;
        ScalarPoint<T, n>::_pos   += ((r-ScalarPoint<T, n>::_value)/d)*v;
        ScalarPoint<T, n>::_value	= r;
      }
    }
    else
    {
      ScalarPoint<T, n>::_pos   = p;
      ScalarPoint<T, n>::_value = T(0);
      _valid = true;
    }

    return *this;
  }



  template <typename T, int n>
  inline
  Sphere<T, n> Sphere<T, n>::operator +  ( const Point<T, n>& p ) const {

    Sphere<T, n> a = (*this);
    a += p;
    return a;
  }

  template <typename T, int n>
  Sphere<T, n>& Sphere<T, n>::operator += ( const Sphere<T, n>& p ) {

    if(p._valid)
    {
      if(_valid)
      {
        Vector<T,n> v =  p._pos - ScalarPoint<T, n>::_pos;
        T r, d = v.getLength();
        if(ScalarPoint<T, n>::_value > p._value)
        {
          if (d > ScalarPoint<T, n>::_value - p._value)
          {
            r		= (d+ScalarPoint<T, n>::_value+p._value)/2;
            ScalarPoint<T, n>::_pos   += ((r-ScalarPoint<T, n>::_value)/d)*v;
            ScalarPoint<T, n>::_value	= r;
          }
        }
        else
        {
          if (d > p._value - ScalarPoint<T, n>::_value)
          {
            r		= (d+ScalarPoint<T, n>::_value+p._value)/2;
            ScalarPoint<T, n>::_pos   += ((r-ScalarPoint<T, n>::_value)/d)*v;
            ScalarPoint<T, n>::_value	= r;
          }
          else
            *this = p;
        }
      }
      else
        *this  = p;
    }
    return *this;
  }

  template <typename T, int n>
  inline
  Sphere<T, n>  Sphere<T, n>::operator +  ( const Sphere<T, n>& p ) const {
    Sphere<T,n> a=(*this);
    a+=p;
    return a;
  }

}
