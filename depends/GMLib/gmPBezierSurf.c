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



/*! \file gmPBezierSurf.c
 *
 *  Implementation of the PBezierSurf template class.
 *
 *  \date   2008-11-20
 */

// local
#include "gmDMatrix.h"
#include "gmEvaluatorStatic.h"
#include "gmSelector.h"
#include "gmSelectorGrid.h"

namespace GMlib {



  template <typename T>
  inline
  PBezierSurf<T>::PBezierSurf( const DMatrix< Vector<T, 3> >& cp ) {

    this->_type_id = GM_SO_TYPE_SURFACE_BEZIER;

    init();

    // Set Control Points
    setControlPoints( cp );
  }


  template <typename T>
  inline
  PBezierSurf<T>::PBezierSurf( const DMatrix< Vector<T, 3> >& c, T s_u, T u, T e_u, T s_v, T v, T e_v  ) {

    this->_type_id = GM_SO_TYPE_SURFACE_BEZIER;

    init();

    // Generate the control points
    DMatrix<T> bhpu, bhpv;
    EvaluatorStatic<T>::evaluateBhp( bhpu, c.getDim1()-1, ( u - s_u ) / ( e_u - s_u ), T(1)/(e_u-s_u) );
    EvaluatorStatic<T>::evaluateBhp( bhpv, c.getDim2()-1, ( v - s_v ) / ( e_v - s_v ), T(1)/(e_v-s_v) );
    bhpu.invert();
    bhpv.invert();
    bhpv.transpose();

    _c = bhpu * (c^bhpv);


    for( int i = 0; i < c.getDim1(); i++ )
      for( int j = 0; j < c.getDim2(); j++ )
        _c[i][j] -= c(0)(0);

    this->translateGlobal( c(0)(0) );
  }


  template <typename T>
  inline
  PBezierSurf<T>::PBezierSurf( const PBezierSurf<T>& dpbs ) : PSurf<T>( dpbs ) {

    init();
  }


  template <typename T>
  inline
  PBezierSurf<T>::~PBezierSurf() {}


  template <typename T>
  void PBezierSurf<T>::edit( int /*selector*/ ) {

    _c_moved = true;
    this->replot();
    if( this->_parent )
      this->_parent->edit( this );
    _c_moved = false;
  }


  template <typename T>
  inline
  void PBezierSurf<T>::eval( T u, T v, int /*d1*/, int /*d2*/, bool /*lu*/, bool /*lv*/ ) {

//    // Send the control to the pre-eval evaluator
//    if( _resamp_mode == GM_RESAMPLE_PREEVAL ) {
//
//      evalPre( u, v, d1, d2, lu, lv );
//      return;
//    }

    // Set Dimensions
    this->_p.setDim( getDegreeU()+1, getDegreeV()+1 );

    // Compute the Bernstein-Hermite Polynomials
    DMatrix< T > bu, bv;
    EvaluatorStatic<T>::evaluateBhp( bu, this->getDegreeU(), u, _su );
    EvaluatorStatic<T>::evaluateBhp( bv, this->getDegreeV(), v, _sv );
//    bv.transpose();

    for( int i = 0; i < bu.getDim1(); i++ )
      for( int j = 0; j < bv.getDim2(); j++ )
        this->_p[i][j] = bu[i] * ( _c^bv[j] );
  }


  template <typename T>
  inline
  void PBezierSurf<T>::evalPre( T u, T v, int /*d1*/, int /*d2*/, bool /*lu*/, bool /*lv*/ ) {

    // Find the u/v index for the preevaluated data.
    int iu, iv;
    iv = 0;
    iu = 0;
    findIndex( u, v, iu, iv );

    // Set Dimensions
    this->_p.setDim( getDegreeU()+1, getDegreeV()+1 );

    DMatrix<T> bu = _u[iu][iv];
    DMatrix<T> bv = _v[iu][iv];

    for( int i = 0; i < bu.getDim1(); i++ )
      for( int j = 0; j < bu.getDim2(); j++ )
        this->_p[i][j] = bu[i] * ( _c^bv[j] );
  }


  template <typename T>
  inline
  void PBezierSurf<T>::findIndex( T u, T v, int& iu, int& iv ) {

    iu = (this->_no_samp_u-1)*(u-this->getParStartU())/(this->getParDeltaU())+0.1;
    iv = (this->_no_samp_v-1)*(v-this->getParStartV())/(this->getParDeltaV())+0.1;
  }


  template <typename T>
  inline
  DMatrix< Vector<T,3> >& PBezierSurf<T>::getControlPoints() {

    return _c;
  }

  template <typename T>
  inline
  int PBezierSurf<T>::getDegreeU() const {

    return _c.getDim1() - 1;
  }


  template <typename T>
  inline
  int PBezierSurf<T>::getDegreeV() const {

    return _c.getDim2() - 1;
  }


  template <typename T>
  inline
  T PBezierSurf<T>::getEndPU() {

    return T(1);
  }


  template <typename T>
  inline
  T PBezierSurf<T>::getEndPV() {

    return T(1);
  }


  template <typename T>
  inline
  std::string PBezierSurf<T>::getIdentity() const {

    return "PBezierSurf";
  }


  template <typename T>
  inline
  T PBezierSurf<T>::getLocalMapping( T t, T ts, T /*tt*/, T te ) {

    return (t - ts) / (te-ts);
  }


  template <typename T>
  inline
  T PBezierSurf<T>::getStartPU() {

    return T(0);
  }


  template <typename T>
  inline
  T PBezierSurf<T>::getStartPV() {

    return T(0);
  }


  template <typename T>
  void PBezierSurf<T>::hideSelectors() {

    if( !_selectors )
      return;

    // Remove Selector Grid
    DisplayObject::remove( _sg );
    delete _sg;
    _sg = 0;

    // Remove Selectors
    for( int i = 0; i < _s.getDim1(); i++ ) {
      for( int j = 0; j < _s.getDim2(); j++ ) {
        DisplayObject::remove( _s[i][j] );
        delete _s[i][j];
      }
    }

    _selectors = false;
  }


  template <typename T>
  inline
  void PBezierSurf<T>::init() {

    _selectors = false;
    _sg = 0;
    _c_moved = false;

    _cu = false;
    _cv = false;
    _su = T(1);
    _sv = T(1);
    _pre_eval = true;
    _resamp_mode = GM_RESAMPLE_PREEVAL;
  }


  template <typename T>
  inline
  bool PBezierSurf<T>::isClosedU() const {

    return _cu;
  }


  template <typename T>
  inline
  bool PBezierSurf<T>::isClosedV() const {

    return _cv;
  }


  template <typename T>
  bool PBezierSurf<T>::isSelectorsVisible() const {

    return _selectors;
  }

  template <typename T>
  inline
  void PBezierSurf<T>::preSample(
    int m1, int m2, int /*d1*/, int /*d2*/,
    T s_u, T s_v, T e_u, T e_v
  ) {

    // break out of the preSample function if no preevalution is to be used
    switch( _resamp_mode ) {
    case GM_RESAMPLE_PREEVAL: break;
    case GM_RESAMPLE_INLINE:
    default:
      return;
    }

    // break out and return if preevaluation isn't necessary.
    if( !_pre_eval && m1 == _u.getDim1() && m2 == _u.getDim2() )
      return;

    // compute du and dv (step in parametric u and v direction)
    const T du = ( e_u - s_u ) / T(m1-1);
    const T dv = ( e_v - s_v ) / T(m2-1);

    // Set the dimension of the Bernstein-Hermite Polynomial DVector
    _u.setDim(m1,m2);
    _v.setDim(m1,m2);

    // Compute the Bernstein-Hermite Polynomiale, for the Bezier Surface
    for( int i = 0; i < m1; i++ ) {
      for( int j = 0; j < m2; j++ ) {

        EvaluatorStatic<T>::evaluateBhp( _u[i][j], getDegreeU(), i*du, _su );
        EvaluatorStatic<T>::evaluateBhp( _v[i][j], getDegreeV(), j*dv, _sv );
      }
    }

    // Disable the pre-evaluation step
    _pre_eval = false;

  }


  template <typename T>
  inline
  void PBezierSurf<T>::setClosed( bool closed_u, bool closed_v ) {

    _cu = closed_u;
    _cv = closed_v;
  }


  template <typename T>
  inline
  void PBezierSurf<T>::setControlPoints( const DMatrix< Vector<T,3> >& cp ) {


    if( _c.getDim1() == cp.getDim1() || _c.getDim2() == cp.getDim2() ) {

      bool no_change = true;
      for( int i = 0; i < cp.getDim1(); i++ )
        for( int j = 0; j < cp.getDim2(); j++ )
          if( _c[i][j] != cp(i)(j) )
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
  void PBezierSurf<T>::setResampleMode( GM_RESAMPLE_MODE mode ) {

    _resamp_mode = mode;
  }


  template <typename T>
  inline
  void PBezierSurf<T>::setScale( T du, T dv ) {

    if( du == _su || dv == _sv )
      return;

    _su = du;
    _sv = dv;
    _pre_eval = true;
  }


  template <typename T>
  void PBezierSurf<T>::showSelectors( bool grid, const Color& _selector_color, const Color& grid_color ) {

    if( _selectors )
      return;

//    DMatrix< Vector<T, 3> > &c = _l_ref->getControlPoints();

    _s.setDim( _c.getDim1(), _c.getDim2() );
    for( int i = 0, s_id = 0; i < _c.getDim1(); i++ ) {
      for( int j = 0; j < _c.getDim2(); j++ ) {

        Selector<T,3> *sel = new Selector<T,3>( _c[i][j], s_id++, this, T(1), _selector_color );
        DisplayObject::insert( sel );
        _s[i][j] = sel;
      }
    }


    if( grid ) {

//      DMatrix< Vector<T, 3> > &c = _l_ref->getControlPoints();

      _sg = new SelectorGrid<T,3>( _c[0][0], this, grid_color );

      for( int i = 0; i < _c.getDim1(); i++ ) {
        for( int j = 0; j < _c.getDim2(); j++ ) {

          if(j!=0) _sg->add(_c[i][j-1], _c[i][j]);  // Horisontal lines in grid
          if(i!=0) _sg->add(_c[i-1][j], _c[i][j]);  // Vertical ilines in grid
        }
      }

      DisplayObject::insert( _sg );
    }

    _selectors = true;
  }


  template <typename T>
  inline
  void PBezierSurf<T>::updateCoeffs( const Vector<T,3>& d ) {

		if( _c_moved ) {

		  HqMatrix<T,3> invmat = this->_matrix;
		  invmat.invertOrthoNormal();

			Vector<T,3> diff = invmat*d;
			for( int i = 0; i < _c.getDim1(); i++ ) {
				for( int j = 0; j < _c.getDim2(); j++ ) {

					_c[i][j] += diff;
					_s[i][j]->translate( diff );
				}
			}
			DisplayObject::translate( -d );
			this->replot();
		}
  }

} // END namespace GMlib


