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



/*! \file gmPBezierCurve.c
 *
 *  Implementation of the PBezierCurve template class.
 *
 *  \date   2008-10-28
 */

#include "gmEvaluatorStatic.h"

namespace GMlib {


  template <typename T>
  inline
  PBezierCurve<T>::PBezierCurve( const DVector< Vector<T, 3> >& c ) {

    this->_type_id = GM_SO_TYPE_CURVE_BEZIER;

    init();

    // Set Control Points
    setControlPoints( c );
  }


  template <typename T>
  inline
  PBezierCurve<T>::PBezierCurve( const DVector< Vector<T, 3> >& c, T s, T t, T e ) {

    this->_type_id = GM_SO_TYPE_CURVE_BEZIER;

    init();

    // Generate the control points
    DMatrix<T> bhp;
    EvaluatorStatic<T>::evaluateBhp( bhp, c.getDim()-1, (t-s)/(e-s), T(1)/(e-s) );
    bhp.invert();
    _c.setDim( c.getDim() );
    _c = bhp * c;

    for( int i = 0; i < c.getDim(); i++ )
      _c[i] -= c(0);
    this->translate( c(0) );
  }


  template <typename T>
  inline
  PBezierCurve<T>::PBezierCurve( const PBezierCurve<T>& copy ) : PCurve<T>( copy ) {

    init();
  }


  template <typename T>
  PBezierCurve<T>::~PBezierCurve() {}


  template <typename T>
  inline
  DVector< Vector<T,3> >& PBezierCurve<T>::getControlPoints() {

    return _c;
  }


  template <typename T>
  inline
  int PBezierCurve<T>::getDegree() const {

    return _c.getDim() - 1;
  }


  template <typename T>
  void PBezierCurve<T>::edit( int /*selector*/ ) {

    _c_moved = true;
    PCurve<T>::replot(0,false);

    if( this->_parent )
      this->_parent->edit( this );

    _c_moved = false;
  }


  template <typename T>
  inline
  void PBezierCurve<T>::eval( T t, int /*d*/, bool /*l*/ ) {

    // Send the control to the pre-eval evaluator
//    if( _resamp_mode == GM_RESAMPLE_PREEVAL ) {
//
//      evalPre( t, d, l );
//      return;
//    }

    // Compute the Bernstein-Hermite Polynomials
    DMatrix< T > bhp;
    EvaluatorStatic<T>::evaluateBhp( bhp, getDegree(), t, _scale );

    this->_p = bhp * _c;
  }


  template <typename T>
  inline
  void PBezierCurve<T>::evalPre( T t, int /*d*/, bool /*l*/ ) {

    // Compute the Bernstein-Hermite Polynomials
//    DMatrix< T > bhp;
//    EvaluatorStatic<T>::evaluateBhp( bhp, getDegree(), t, _scale );

    int it = 0;
    findIndex( t, it );

    this->_p = _t[it] * _c;
  }

  template <typename T>
  inline
  void PBezierCurve<T>::findIndex( T t, int& it ) {

    it = (this->_no_samp-1)*(t-this->getParStart())/(this->getParDelta())+0.1;
  }


  template <typename T>
  T PBezierCurve<T>::getEndP() {

    return T(1);
  }


  template <typename T>
  inline
  std::string PBezierCurve<T>::getIdentity() const {

    return "PBezierCurve";
  }


  template <typename T>
  inline
  T PBezierCurve<T>::getLocalMapping( T t, T ts, T /*ti*/, T te ) {

    return (t - ts) / (te-ts);
  }


  template <typename T>
  T PBezierCurve<T>::getStartP() {

    return T(0);
  }


  template <typename T>
  inline
  void PBezierCurve<T>::hideSelectors() {

    if( !_selectors )
      return;

    // Remove Selector Grid
    DisplayObject::remove( _sg );
    delete _sg;
    _sg = 0;

    // Remove Selectors
    for( int i = 0; i < _s.getDim(); i++ ) {
      DisplayObject::remove( _s[i] );
      delete _s[i];
    }

    _selectors = false;
  }


  template <typename T>
  void PBezierCurve<T>::init() {

    _selectors = false;
    _sg = 0;
    _c_moved = false;

    _scale = T(1);
    _closed = false;
    _pre_eval = true;
    _resamp_mode = GM_RESAMPLE_PREEVAL;
  }


  template <typename T>
  inline
  bool PBezierCurve<T>::isClosed() const {

    return _closed;
  }


  template <typename T>
  bool PBezierCurve<T>::isSelectorsVisible() const {

    return _selectors;
  }


  template <typename T>
  inline
  void PBezierCurve<T>::preSample( int m, int /*d*/, T start, T end ) {

    // break out of the preSample function if no preevalution is to be used
    switch( _resamp_mode ) {
    case GM_RESAMPLE_PREEVAL: break;
    case GM_RESAMPLE_INLINE:
    default:
      return;
    }

    // Check whether to redo the preEvaluation
    if( !_pre_eval && m == _t.getDim() )
      return;

    // dt; sample step value
    const T dt = (end-start) / T(m-1);

    // Set the dimension of the Bernstein-Hermite Polynomial DVector
    _t.setDim(m);

    // For each sample point on the uniform curve calculate the Bernstein-Hermite Polynomials
    for( int i = 0; i < m; i++ )
      EvaluatorStatic<T>::evaluateBhp( _t[i], getDegree(), i*dt, _scale );

    // Disable the pre-evaluation step
    _pre_eval = false;
  }


  template <typename T>
  inline
  void PBezierCurve<T>::setClosed( bool state ) {

    _closed = state;
  }

  template <typename T>
  inline
  void PBezierCurve<T>::setControlPoints( const DVector< Vector<T,3> >& cp ) {


    if( _c.getDim() == cp.getDim() ) {

      bool no_change = true;
      for( int i = 0; i < cp.getDim(); i++ )
        if( _c[i] != cp(i) )
          no_change = false;

      if( no_change )
        return;
    }
    else {

      _pre_eval = true;
    }

    _c = cp;
  }


  template <typename T>
  inline
  void PBezierCurve<T>::setResampleMode( GM_RESAMPLE_MODE mode ) {

    _resamp_mode = mode;
  }


  template <typename T>
  inline
  void PBezierCurve<T>::setScale( T d ) {

    if( d == _scale )
      return;

    _scale = d;
    _pre_eval = true;
  }


  template <typename T>
  inline
  void PBezierCurve<T>::showSelectors( bool grid, const Color& _selector_color, const Color& grid_color ) {

    if( _selectors )
      return;

//    DVector< Vector<T, 3> > &c = _l_ref->getControlPoints();

    _s.setDim( _c.getDim() );
    for( int i = 0, s_id = 0; i < _c.getDim(); i++ ) {

      Selector<T,3> *sel = new Selector<T,3>( _c[i], s_id++, this, T(1), _selector_color );
      DisplayObject::insert( sel );
      _s[i] = sel;
    }


    if( grid ) {

      _sg = new SelectorGrid<T,3>( _c[0], this, grid_color );

      for( int i = 1; i < _c.getDim(); i++ )
          _sg->add(_c[i-1], _c[i]);  // Lines in grid

      DisplayObject::insert( _sg );
    }

    _selectors = true;
  }


  template <typename T>
  inline
  void PBezierCurve<T>::updateCoeffs( const Vector<T,3>& d ) {

		if( _c_moved ) {

		  HqMatrix<T,3> invmat = this->_matrix;
		  invmat.invertOrthoNormal();

			Vector<T,3> diff = invmat*d;
			for( int i = 0; i < _c.getDim(); i++ ) {

        _c[i] += diff;
        _s[i]->translate( diff );
			}
			DisplayObject::translate( -d );
			this->replot();
		}
  }


} // END namespace GMlib

