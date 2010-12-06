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



/*! \file gmPAsteroidalSphere.c
 *
 *  Implementation of the PAsteroidalSphere template class.
 *
 *  \date   2009-11-29
 */


namespace GMlib {

  template <typename T>
  PAsteroidalSphere<T>::PAsteroidalSphere( T sx, T sy, T sz ) {

    this->_dm = GM_DERIVATION_EXPLICIT;
    setConstants( sx, sy, sz );
  }


  template <typename T>
  PAsteroidalSphere<T>::PAsteroidalSphere( const PAsteroidalSphere<T>& copy ) : PSurf<T>( copy ) {

    setConstants( copy.sx, copy.sy, copy.sz );
  }


  template <typename T>
  void PAsteroidalSphere<T>::eval( T u, T v, int d1, int d2, bool /*lu*/, bool /*lv*/ ) {

    this->_p.setDim( d1+1, d2+1 );


    this->_p[0][0][0] =	T( pow( ( _a * cos(u)*cos(v) ), 3.0 ) );
    this->_p[0][0][1] =	T( pow( ( _b * sin(u)*cos(v) ), 3.0 ) );
    this->_p[0][0][2] =	T( pow( ( _c * sin(v) ), 3.0 ) );

    if( this->_dm == GM_DERIVATION_EXPLICIT ) {

      if(d1) //u
      {
        this->_p[1][0][0] =	-T(3)*_a*_a*_a*cos(u)*cos(u)*cos(v)*cos(v)*cos(v)*sin(u);
        this->_p[1][0][1] =	-T(3)*_b*_b*_b*(-1.0+cos(u)*cos(u))*cos(v)*cos(v)*cos(v)*cos(u);
        this->_p[1][0][2] =	T(0);
      }
      if(d1>1)//uu
      {
        this->_p[2][0][0] = -T(3)*_a*_a*_a*cos(u)*cos(v)*cos(v)*cos(v)*(-2.0+3.0*cos(u)*cos(u));
        this->_p[2][0][1] =	T(3)*_b*_b*_b*sin(u)*cos(v)*cos(v)*cos(v)*(3.0*cos(u)*cos(u)-1.0);
        this->_p[2][0][2] =	T(0);
      }
      if(d2) //v
      {
        this->_p[0][1][0] =	-T(3)*_a*_a*_a*cos(u)*cos(u)*cos(u)*cos(v)*cos(v)*sin(v);
        this->_p[0][1][1] =	T(3)*_b*_b*_b*(-1.0+cos(u)*cos(u))*sin(u)*cos(v)*cos(v)*sin(v);
        this->_p[0][1][2] =	-T(3)*_c*_c*_c*(-1.0+cos(v)*cos(v))*cos(v);
      }
      if(d2>1) //vv
      {
        this->_p[0][2][0] =	-T(3)*_a*_a*_a*cos(u)*cos(u)*cos(u)*cos(v)*(-2.0+3.0*cos(v)*cos(v));
        this->_p[0][2][1] =	T(3)*_b*_b*_b*(-1.0+cos(u)*cos(u))*sin(u)*cos(v)*(-2.0+3.0*cos(v)*cos(v));
        this->_p[0][2][2] =	T(3)*_c*_c*_c*sin(v)*(3.0*cos(v)*cos(v)-1.0);
      }
      if(d1 && d2) //uv
      {
        this->_p[1][1][0] =  T(9)*_a*_a*_a*cos(u)*cos(u)*cos(v)*cos(v)*sin(u)*sin(v);
        this->_p[1][1][1] =	T(9)*_b*_b*_b*(-1.0+cos(u)*cos(u))*cos(v)*cos(v)*cos(u)*sin(v);
        this->_p[1][1][2] =	T(0);
      }
      if(d1>1 && d2)//uuv
      {
        this->_p[2][1][0] =	T(9)*_a*_a*_a*cos(u)*cos(v)*cos(v)*sin(v)*(-2.0+3.0*cos(u)*cos(u));
        this->_p[2][1][1] =	-T(9)*_b*_b*_b*sin(u)*cos(v)*cos(v)*sin(v)*(3.0*cos(u)*cos(u)-1.0);
        this->_p[2][1][2] =	T(0);
      }
      if(d1 && d2>1) //uvv
      {
        this->_p[1][2][0] =	T(9)*_a*_a*_a*cos(u)*cos(u)*cos(v)*sin(u)*(-2.0+3.0*cos(v)*cos(v));
        this->_p[1][2][1] =	T(9)*_b*_b*_b*(-1.0+cos(u)*cos(u))*cos(v)*cos(u)*(-2.0+3.0*cos(v)*cos(v));
        this->_p[1][2][2] =	T(0);
      }
      if(d1>1 && d2>1) //uuvv
      {
        this->_p[2][2][0] =	T(9)*_a*_a*_a*cos(u)*cos(v)*(4.0-6.0*cos(v)*cos(v)-6.0*cos(u)*cos(u)+9.0*cos(u)*cos(u)*cos(v)*cos(v));
        this->_p[2][2][1] =	-T(9)*_b*_b*_b*sin(u)*cos(v)*(-6.0*cos(u)*cos(u)+9.0*cos(u)*cos(u)*cos(v)*cos(v)+2.0-3.0*cos(v)*cos(v));
        this->_p[2][2][2] =	T(0);
      }
    }
  }


  template <typename T>
  T PAsteroidalSphere<T>::getEndPU() {

    return T( M_2PI );
  }


  template <typename T>
  T PAsteroidalSphere<T>::getEndPV() {

    return T( M_PI * 0.5 );
  }


  template <typename T>
  std::string PAsteroidalSphere<T>::getIdentity() const {

    return "PAsteroidalSphere";
  }


  template <typename T>
  T PAsteroidalSphere<T>::getStartPU() {

    return T(0);
  }


  template <typename T>
  T PAsteroidalSphere<T>::getStartPV() {

    return -T( M_PI * 0.5 );
  }


  template <typename T>
  bool PAsteroidalSphere<T>::isClosedU() const {

    return true;
  }


  template <typename T>
  bool PAsteroidalSphere<T>::isClosedV() const {

    return false;
  }


  template <typename T>
  void PAsteroidalSphere<T>::setConstants( T sx, T sy, T sz ) {

    _a = sx;
    _b = sy;
    _c = sz;
  }

} // END namespace GMlib
