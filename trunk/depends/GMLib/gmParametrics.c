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



/*! \file gmParametrics.c
 *
 *  Implementation of the Parametrics class.
 *
 *  \date   2009-01-26
 */


namespace GMlib {

  template <typename T, int n>
  inline
  Parametrics<T,n>::Parametrics() {

    _initSoType();
  }


  template <typename T, int n>
  inline
  Parametrics<T,n>::Parametrics( const Parametrics<T,n>& copy ) : DisplayObject( copy ) {}


  template <typename T, int n>
  inline
  Parametrics<T,n>::~Parametrics() {}


  template <typename T, int n>
  void Parametrics<T,n>::_initSoType() {

    switch( n ) {

      case GM_POINT:
        _type_id = GM_SO_TYPE_POINT;
        break;
      case GM_CURVE:
        _type_id = GM_SO_TYPE_CURVE;
        break;
      case GM_SURFACE:
        _type_id = GM_SO_TYPE_SURFACE;
        break;
      case GM_FLOW:
        _type_id = GM_SO_TYPE_VOLUME;
        break;
    }
  }


  template <typename T, int n>
  inline
  void Parametrics<T,n>::rotate(Angle a, const Vector<float,3>& rot_axel) {

    DisplayObject::rotate( a, rot_axel );
    if( this->_parent )
      this->_parent->edit( this );
  }


  template <typename T, int n>
  inline
  void Parametrics<T,n>::rotate(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d) {

    DisplayObject::rotate( a, p, d );
    if( this->_parent )
      this->_parent->edit( this );
  }


  template <typename T, int n>
  inline
  void Parametrics<T,n>::rotateGlobal(Angle a, const Vector<float,3>& rot_axel) {

    DisplayObject::rotateGlobal( a, rot_axel );
    if( this->_parent )
      this->_parent->edit( this );
  }


  template <typename T, int n>
  inline
  void Parametrics<T,n>::rotateGlobal(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d) {

    DisplayObject::rotateGlobal( a, p, d );
    if( this->_parent )
      this->_parent->edit( this );
  }


  template <typename T, int n>
  void Parametrics<T,n>::setDerivationMethod( GM_DERIVATION_METHOD method ) {

    _dm = method;
  }


  template <typename T, int n>
  inline
  void Parametrics<T,n>::translate( const Vector<float,3>& trans_vector ) {

    DisplayObject::translate( trans_vector );
    if( this->_parent )
      this->_parent->edit( this );
  }


  template <typename T, int n>
  inline
  void Parametrics<T,n>::translateGlobal( const Vector<float,3>& trans_vector ) {

    DisplayObject::translateGlobal( trans_vector );
    if( this->_parent )
      this->_parent->edit( this );
  }

} // END namespace GMlib
