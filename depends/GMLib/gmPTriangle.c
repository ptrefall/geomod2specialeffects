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



/*! \file gmPTriangle.c
 *
 *  Implementation of the PTriangle template class.
 *
 *  \date   2010-03-22
 */

#include <iomanip>

// local
#include "gmPTriangleVisualizer.h"

namespace GMlib {

  template <typename T>
  PTriangle<T>::PTriangle( int samples ) {

    _d1      = -1;
    _d2      = -1;
    _tr_u    = T(0);
    _sc_u    = T(1);
    _tr_v    = T(0);
    _sc_v    = T(1);
    _no_sam  = samples;
    setEval( 0 );

    _default_visualizer = new PTriangleVisualizer<T>();
    enableDefaultVisualizer( true );
  }

  template <typename T>
  PTriangle<T>::PTriangle( const PTriangle<T>& copy ) {

    _p            = copy._p;
    _n            = copy._n;
    _u            = copy._u;
    _v            = copy._v;
    _d1           = copy._d1;
    _d2           = copy._d2;
    _tr_u         = copy._tr_u;
    _sc_u         = copy._sc_u;
    _tr_v         = copy._tr_v;
    _sc_v         = copy._sc_v;
//    _sam_p_u      = copy._sam_p_u;
//    _sam_p_v      = copy._sam_p_v;
//    _sam         = copy._sam;
//    _sam2         = copy._sam2;
    _default_d    = copy._default_d;


//    _no_der_u     = copy._no_der_u;
//    _no_der_v     = copy._no_der_v;
//    _no_sam_u    = copy._no_sam_u;
//    _no_sam_v    = copy._no_sam_v;

    _default_visualizer = new PTriangleVisualizer<T>();
    enableDefaultVisualizer( true );
  }

  template <typename T>
  PTriangle<T>::~PTriangle() {

    enableDefaultVisualizer( false );
    delete _default_visualizer;
  }

  template <typename T>
  inline
  void PTriangle<T>::_eval( T u, T v ) {

    eval( u, v, 1-u-v );
  }


  template <typename T>
  inline
  int PTriangle<T>::_sum( int i ) {

    int r = 0;
    for(; i>0; i--) r += i;
    return r;
  }

  template <typename T>
  void PTriangle<T>::enableDefaultVisualizer( bool enable ) {

    if( !enable )
      removeVisualizer( _default_visualizer );
    else
      insertVisualizer( _default_visualizer );
  }

  template <typename T>
  inline
  const DMatrix<Vector<T,3> >& PTriangle<T>::evaluateGlobal( T u, T v, int d1, int d2  ) {

    static DMatrix<Vector<T,3> > p;
    p.setDim( d1+1, d2+1 );

    _eval(u,v);

    p[0][0] = this->_present * (Point<T,3>)_p[0][0];

    for( int j = 1; j < p.getDim2(); j++ )
      p[0][j] = this->_present * (Vector<T,3>)_p[0][j];

    for( int i = 1; i < p.getDim1(); i++ )
      for( int j = 0; j < p.getDim2(); j++ )
        p[i][j] = this->_present * (Vector<T,3>)_p[i][j];

    return p;
  }


  template <typename T>
  inline
  const DMatrix<Vector<T,3> >& PTriangle<T>::evaluateLocal( T u, T v, int d1, int d2 ) {

    _eval( u, v );
    return _p;
  }


  template <typename T>
  inline
  const DMatrix<Vector<T,3> >& PTriangle<T>::evaluateParent( T u, T v, int d1, int d2 ) {

    static DMatrix<Vector<T,3> > p;
    p.setDim( d1+1, d2+1 );

    _eval( u, v );

    p[0][0] = this->_matrix * (Point<T,3>)_p[0][0];

    for( int j = 1; j < p.getDim2(); j++ )
      p[0][j] = this->_matrix * (Vector<T,3>)_p[0][j];

    for( int i = 1; i < p.getDim1(); i++ )
      for( int j = 0; j < p.getDim2(); j++ )
        p[i][j] = this->_matrix * (Vector<T,3>)_p[i][j];

    return p;
  }


  template <typename T>
  T PTriangle<T>::getCurvatureGauss( T u, T v ) {

    Vector<T,3> du,dv,duv,duu,dvv;

    _eval(u,v);
    UnitVector<T,3> N = getUnitNormal(u,v);
    du=getDerU(u,v);
    dv=getDerV(u,v);
    duu=getDerUU(u,v);
    duv=getDerUV(u,v);
    dvv=getDerVV(u,v);

    T E=du*du;
    T F=du*dv;
    T G=dv*dv;
    T e=N*duu;
    T f=N*duv;
    T g=N*dvv;

    return (e*g - f*f)/(E*G-F*F);
  }


  template <typename T>
  T PTriangle<T>::getCurvatureMean( T u, T v ) {

    Vector<T,3> du,dv,duv,duu,dvv;

    _eval( u, v );
    UnitVector<T,3> N = getUnitNormal(u,v);
    du=getDerU(u,v);
    dv=getDerV(u,v);
    duu=getDerUU(u,v);
    duv=getDerUV(u,v);
    dvv=getDerVV(u,v);

    T E=du*du;
    T F=du*dv;
    T G=dv*dv;
    T e=N*duu;
    T f=N*duv;
    T g=N*dvv;

    return 0.5*(e*G-2*(f*F)+g*E)/(E*G-F*F);
  }


  template <typename T>
  inline
  const Vector<T,3>& PTriangle<T>::getDerU( T u, T v ) {

    _eval(u,v);
    return _p[1][0];
  }


  template <typename T>
  inline
  const Vector<T,3>& PTriangle<T>::getDerV( T u, T v ) {

    _eval(u,v);
    return _p[0][1];
  }


  template <typename T>
  inline
  const Vector<T,3>& PTriangle<T>::getDerUU( T u, T v ) {

    _eval(u,v);
    return _p[2][0];
  }


  template <typename T>
  inline
  const Vector<T,3>& PTriangle<T>::getDerUV( T u, T v ) {

    _eval(u,v);
    return _p[1][1];
  }


  template <typename T>
  inline
  const Vector<T,3>& PTriangle<T>::getDerVV( T u, T v ) {

    _eval(u,v);
    return _p[0][2];
  }


  template <typename T>
  std::string PTriangle<T>::getIdentity() const {

    return "PTriangle";
  }


  template <typename T>
  const Vector<T,3>& PTriangle<T>::getNormal( T u, T v ) {

    _eval( u, v );
    return _n;
  }


  template <typename T>
  inline
  T PTriangle<T>::getParDeltaU() {

    return _sc_u * ( getEndPU() - getStartPU() );
  }


  template <typename T>
  inline
  T PTriangle<T>::getParDeltaV() {

    return _sc_v * ( getEndPV() - getStartPV() );
  }


  template <typename T>
  inline
  T PTriangle<T>::getParEndU() {

    return getParStartU() + getParDeltaU();
  }


  template <typename T>
  inline
  T PTriangle<T>::getParEndV() {

    return getParStartV() + getParDeltaV();
  }


  template <typename T>
  inline
  T PTriangle<T>::getParStartU() {

    return getStartPU() + _tr_u;
  }


  template <typename T>
  inline
  T PTriangle<T>::getParStartV() {

    return getStartPV() + _tr_v;
  }


  template <typename T>
  UnitVector<T,3> PTriangle<T>::getUnitNormal( T u, T v ) {

    return getNormal( u, v );
  }

  template <typename T>
  inline
  void PTriangle<T>::insertVisualizer( Visualizer *visualizer ) {

    PTriangleVisualizer<T> *visu = dynamic_cast<PTriangleVisualizer<T>*>( visualizer );
    if( !visu )
      return;

    if( _ptriangle_visualizers.exist( visu ) )
      return;

    _ptriangle_visualizers += visu;

    SceneObject::insertVisualizer( visualizer );
  }

  template <typename T>
  bool PTriangle<T>::isClosestPoint( const Point<T,3>& q, T& u, T& v ) {

    T a11,a12,a21,a22,b1,b2;
    T du,dv,det;

    HqMatrix<float,3> invmat = this->_present;
    invmat.invertOrthoNormal();
    Point<T,3> p = invmat * q;  // Egentlig _present

    for(int i=0; i<20;i++) {

      _eval( u, v );

      Vector<T,3> d = p - _p[0][0];

      a11 = d*_p[2][0]-_p[1][0]*_p[1][0];
      a12 = d*_p[1][1]-_p[1][0]*_p[0][1];
      a21 = a12;
      a22 = d*_p[0][2]-_p[0][1]*_p[0][1];

      b1  = -(d*_p[1][0]);
      b2  = -(d*_p[0][1]);

      det = a11*a22-a12*a21;
      du  = (b1*a22-a12*b2)/det;
      dv  = (a11*b2-b1*a21)/det;
      if(fabs(du)< 1e-6 && fabs(dv) < 1e-6) break;
      u += du;
      v += dv;
    }
    return true;
  }

  template <typename T>
  inline
  void PTriangle<T>::removeVisualizer( Visualizer *visualizer ) {

    PTriangleVisualizer<T> *visu = dynamic_cast<PTriangleVisualizer<T>*>( visualizer );
    if( visu )
      _ptriangle_visualizers.remove( visu );

    SceneObject::removeVisualizer( visualizer );
  }


  template <typename T>
  inline
  void PTriangle<T>::replot( int m ) {

    if( m < 2 )
      m = _no_sam;
    else
      _no_sam = m;


    // Sample Positions and related Derivatives
    DVector< DMatrix< Vector<T,3> > > p;
    resample( p, m );

    int i,j,k;
    for(k=0,i=0; i<m; i++)
      for(j=0;j<=i;j++)
        k++;


    // Set The Surrounding Sphere
    setSurroundingSphere( p );

    // Replot Visaulizers
    for( int i = 0; i < this->_ptriangle_visualizers.getSize(); i++ )
      this->_ptriangle_visualizers[i]->replot( p, m );
  }


  template <typename T>
  inline
  void PTriangle<T>::resample(
    DVector< DMatrix < Vector<T,3> > >& p,
    int m
  ) {

    T u,v,du = T(1)/(m-1);
    p.setDim(_sum(m));
    int i,j,k;
    for(k=0,i=0; i<m; i++) {
      for( j=0; j<=i; j++ ) {

        v = j*du;
        u = (i-j)*du;
        eval(u,v,1-u-v);
        p[k++] = _p;
      }
    }
  }


  template <typename T>
  inline
  void PTriangle<T>::setDomainU( T start, T end ) {

    _sc_u = (end-start) / (getEndPU()-getStartPU());
    _tr_u = start - getStartPU();
  }


  template <typename T>
  inline
  void PTriangle<T>::setDomainUScale( T sc ) {

    _sc_u = sc;
  }


  template <typename T>
  inline
  void PTriangle<T>::setDomainUTrans( T tr ) {

    _tr_u = tr;
  }


  template <typename T>
  inline
  void PTriangle<T>::setDomainV( T start, T end ) {

    _sc_v = (end-start) / (getEndPV()-getParStartV());
    _tr_v = start - getStartPV();
  }


  template <typename T>
  inline
  void PTriangle<T>::setDomainVScale( T sc ) {

    _sc_v = sc;
  }


  template <typename T>
  inline
  void PTriangle<T>::setDomainVTrans( T tr ) {

    _tr_v = tr;
  }


  template <typename T>
  inline
  void PTriangle<T>::setEval( int d ) {

    _default_d = d;
  }


  template <typename T>
  inline
  void PTriangle<T>::setSurroundingSphere( const DVector<DMatrix<Vector<T, 3> > >& p ) {

    Sphere<float,3>  s( (p(0)(0)(0)).toFloat() );

    s += Point<float,3>( p( p.getDim()-1)(0)(0) );
    for( int i = 1; i < p.getDim() - 1; i++ )
      s += Point<float,3>( p(i)(0)(0) );

    Parametrics<T,2>::setSurroundingSphere(s);
  }


  template <typename T>
  inline
  T PTriangle<T>::shiftU( T u ) {

    return getStartPU() + _sc_u * ( u - getParStartU() );
  }


  template <typename T>
  inline
  T PTriangle<T>::shiftV( T v ) {

    return getStartPV() + _sc_v * ( v - getParStartV() );
  }


  template <typename T>
  inline
  Parametrics<T,2>* PTriangle<T>::split( T t, int uv ) {

    return 0x0;
  }

  template <typename T>
  void PTriangle<T>::toggleDefaultVisualizer() {

    if( !_ptriangle_visualizers.exist( _default_visualizer ) )
      enableDefaultVisualizer( true );
    else
      enableDefaultVisualizer( false );
  }

  template <typename T>
  inline
  void PTriangle<T>::updateCoeffs( const Vector<T,3>& /*d*/ ) {}


  template <typename T>
  inline
  const Point<T,3>& PTriangle<T>::operator()( T u, T v ) {

    _eval(u,v);
    return static_cast< Point<T,3> >( _p[0][0] );
  }



} // END namespace GMlib
