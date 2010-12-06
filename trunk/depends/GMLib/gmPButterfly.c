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



/*! \file gmPButterfly.c
 *
 *  Implementation of the PButterfly template class.
 *
 *  \date   2008-09-10
 */


namespace GMlib {


  template <typename T>
  inline
  PButterfly<T>::PButterfly( T size ) {

    _size = size;
    this->_dm = GM_DERIVATION_EXPLICIT;
  }


  template <typename T>
  inline
  PButterfly<T>::PButterfly( const PButterfly<T>& copy ) : PCurve<T>( copy ) {}


  template <typename T>
  PButterfly<T>::~PButterfly() {}


  template <typename T>
  inline
  void PButterfly<T>::eval( T t, int d, bool /*l*/ ) {

    this->_p.setDim( d + 1 );

    const double  a  = ( exp( cos(t) ) - 2 * cos(4 * t) - pow( sin(t / 12.0), 5.0 ) );
    const double  a1 = ( -exp( cos(t) ) * sin(t) + 8.0 * sin(4.0 * t) - (5.0/12.0)* pow( sin(t / 12.0), 4.0 ) * cos(t/12.0) );
    const double  a2 = ( exp( cos(t) )*sin(t)*sin(t) - exp( cos(t) ) * cos(t) + 8.0* 4.0 *cos(4.0 * t) - (5.0/12.0)*( (1.0/3.0)* pow( sin(t / 12.0), 3.0 )*pow( cos(t / 12.0), 2.0 ) - (1.0/12.0)* pow( sin(t / 12.0), 5.0 ) ));


    this->_p[0][0] = _size * T(cos(t) * a);
    this->_p[0][1] = _size * T(sin(t) * a);
    this->_p[0][2] = T(0);

    if( this->_dm == GM_DERIVATION_EXPLICIT ) {

      if( d > 0 ) {

        this->_p[1][0] = _size * T( -sin(t) * a + cos(t) * a1 );
        this->_p[1][1] = _size * T(  cos(t) * a + sin(t) * a1 );
        this->_p[1][2] = T(0);
      }


      if( d > 1 ) {

        this->_p[2][0] = _size * T( -cos(t) * a - sin(t) * a1 - sin(t) * a1 + cos(t) * a2 );
        this->_p[2][1] = _size * T( -sin(t) * a + cos(t) * a1 + cos(t) * a1 + sin(t) * a2 );
        this->_p[2][2] = T(0);
      }
    }
  }


  template <typename T>
  inline
  T PButterfly<T>::getEndP() {

    return T( M_PI * 24.0 );
  }


  template <typename T>
  inline
  std::string PButterfly<T>::getIdentity() const {

    return "PButterfly";
  }


  template <typename T>
  inline
  T PButterfly<T>::getStartP() {

    return T(0);
  }


  template <typename T>
  inline
  bool PButterfly<T>::isClosed() const {

    return true;
  }
}
