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



/*! \file gmPChrysanthemumCurve.c
 *
 *  Implementation of the PChrysanthemumCurve template class.
 *
 *  \date   2009-11-28
 */


namespace GMlib {



  template <typename T>
  PChrysanthemumCurve<T>::PChrysanthemumCurve( T radius ) {

    this->_dm = GM_DERIVATION_DD;
    _r = radius;
  }


  template <typename T>
  PChrysanthemumCurve<T>::PChrysanthemumCurve( const PChrysanthemumCurve<T>& copy ) : PCurve<T>( copy ) {}


  template <typename T>
  inline
  void PChrysanthemumCurve<T>::eval( T t, int d, bool l ) {

    this->_p.setDim( d+1 );

    const double p4 = sin( 17.0 * t / 3.0 );
    const double p8 = sin( 2.0 * cos( 3.0 * t ) - 28.0 * t );
    const double r = 5.0 * ( 1.0 + sin( 11.0 * t / 5.0 ) ) - 4 * pow( p4, 4 ) * pow( p8, 8 );

    this->_p[0][0] = _r * T( r * cos( t ) );
    this->_p[0][1] = _r * T( r * sin( t ) );
    this->_p[0][2] = T(0);

  }


  template <typename T>
  inline
  T PChrysanthemumCurve<T>::getEndP() {

    return T( 21 * M_PI );
  }


  template <typename T>
  std::string PChrysanthemumCurve<T>::getIdentity() const {

    return "PChrysanthemumCurve";
  }


  template <typename T>
  inline
  T PChrysanthemumCurve<T>::getStartP() {

    return T(0);
  }


  template <typename T>
  inline
  bool PChrysanthemumCurve<T>::isClosed() const {

    return true;
  }


} // END namespace GMlib

