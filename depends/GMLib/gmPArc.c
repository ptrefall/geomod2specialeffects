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



/*! \file gmPArc.c
 *
 *  Implementation of the PArc template class.
 *
 *  \date   2008-11-16
 */


namespace GMlib {


  template <typename T>
  inline
  PArc<T>::PArc( T speed, T curvature ) {

    _d = speed;
    _k = curvature;

    _start = T(0);
    _end =  T( M_2PI );
  }


  template <typename T>
  inline
  PArc<T>::PArc( T speed, T curvature, T start, T end ) {

    _d = speed;
    _k = curvature;

    _start = start;
    _end = end;
  }


  template <typename T>
  inline
  PArc<T>::PArc( DVector< Vector<T,3> >& p, T s, T t, T e ) {

    Vector<T,3> x, y, z, y_;

    _d      = p[1].getLength();
    _start  = (s-t);
    _end    = (e-t);

    DVector< Vector<T,3> > xyz(3);
    x = p[1] / _d;
    y_ = ( p[2] - ( x * p[2] ) * x ) / (_d * _d);


    _k = y_.getLength();

    if( y_.getLength() > 1e-5 ) {

      y = y_ / y_.getLength();
      z = Vector3D<T>(y) ^ x;
    }
    else
      y = z = Vector<T,3>( T(0) );


    // Do basis change
    this->_side = y;
    this->_up   = z;
    this->_dir  = x;
    this->_pos  = p[0];
    DisplayObject::basisChange( this->_side, this->_up, this->_dir, this->_pos );
  }


  template <typename T>
  inline
  PArc<T>::PArc( const PArc<T>& copy ) : PCurve<T>(copy) {

    _d = copy._d;
    _k = copy._k;

    _start = copy._start;
    _end = copy._end;
  }


  template <typename T>
  inline
  PArc<T>::~PArc() {}


  template <typename T>
  inline
  void PArc<T>::eval( T t, int d, bool /*l*/ ) {

    this->_p.setDim( d + 1 );

    if( _k < 1e-5 ) {


      this->_p[0][0] = _d * t;
      this->_p[0][1] = T(0);
      this->_p[0][2] = T(0);

      if( this->_dm == GM_DERIVATION_EXPLICIT ) {

        if( d > 0 ) {

          this->_p[1][0] = _d;
          this->_p[1][1] = T(0);
          this->_p[1][2] = T(0);
        }

        if( d > 1 ) {

          this->_p[2][0] = T(0);
          this->_p[2][1] = T(0);
          this->_p[2][2] = T(0);
        }
      }
    }
    else { // if _k > 0


      this->_p[0][0] = T( sin( _k * _d * t ) );
      this->_p[0][1] = T( 1.0 - cos( _k * _d * t ) );
      this->_p[0][2] = T(0);

      this->_p *= T(1) / _k;

      if( this->_dm == GM_DERIVATION_EXPLICIT ) {

        const T g = _k * _d;

        if( d > 0 ) {

          this->_p[1][0] = g * T( cos( _k * _d * t ) );
          this->_p[1][1] = g * T( sin( _k * _d * t ) );
          this->_p[1][2] = T(0);
        }

        if( d > 1 ) {

          this->_p[2][0] = g * T( -sin( _k * _d * t ) );
          this->_p[2][1] = g * T(  cos( _k * _d * t ) );
          this->_p[2][2] = T(0);
        }
      }
    }

  }


  template <typename T>
  inline
  T PArc<T>::getCurvature() const {

    return _k;
  }


  template <typename T>
  inline
  T PArc<T>::getCurvature( DVector< Vector<T,3> >& p ) {

    Vector<T,3> d1 = p[1];
    T a1= d1.getLength();

    if( a1 < T(1.0e-5) )
      return T(0);

    d1 /= a1;

    Vector<T,3> d2 = ( p[2] - ( d1 * p[2] ) * d1 ) / ( a1 * a1 );

    return d2.getLength();
  }


  template <typename T>
  inline
  T PArc<T>::getEndP() {

    return _end;
  }


  template <typename T>
  inline
  std::string PArc<T>::getIdentity() const {

    return "PArc";
  }


  template <typename T>
  inline
  T PArc<T>::getLocalMapping( T t, T ts, T ti, T te ) {

    return this->getParStart() + (t - ti) / (te-ts) * this->getParDelta();
  }


  template <typename T>
  inline
  T PArc<T>::getSpeed() const {

    return _d;
  }


  template <typename T>
  inline
  T PArc<T>::getStartP() {

    return _start;
  }


  template <typename T>
  inline
  bool PArc<T>::isClosed() const {

    return (_end - _start) < 1e-5;
  }


  template <typename T>
  inline
  void PArc<T>::setCurvature( T curvature ) {

      _k = curvature;
  }


  template <typename T>
  inline
  void PArc<T>::setEnd( T end ) {

      _end = end;
  }


  template <typename T>
  inline
  void PArc<T>::setSpeed( T speed ) {

      _d = speed;
  }


  template <typename T>
  inline
  void PArc<T>::setStart( T start ) {

      _start = start;
  }

} // END namespace GMlib



