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



/*! \file gmPSurf.h
 *
 *  Interface for the PSurf class.
 *
 *  \date   2008-09-04
 */

#ifndef __gmDSURF_H__
#define __gmDSURF_H__

// STL
#include <fstream>

// Local
#include "gmArray.h"
#include "gmDVector.h"
#include "gmDMatrix.h"
#include "gmParametrics.h"


namespace GMlib {

  template <typename T>
  class PSurfVisualizer;

  template <typename T>
  class PSurf : public Parametrics<T,2> {
  public:

    PSurf( int s1 = 20, int s2 = 20 );
    PSurf( const PSurf<T>& copy );
    virtual ~PSurf();

    void                          enableDefaultVisualizer( bool enable = true );
    //virtual void                  estimateClpPar( const Point<T,3>& p, T& u, T& v );
    DMatrix<Vector<T,3> >&        evaluate( Point<T,2> p, int d );
    DMatrix<Vector<T,3> >&    	  evaluate( T u, T v, int d1, int d2 );
    DVector<Vector<T,3> >         evaluateD( Point<T,2> p, int d );
    DVector<Vector<T,3> >         evaluateD( T u, T v, int d1, int d2 );
    DMatrix<Vector<T,3> >&    	  evaluateGlobal( Point<T,2> p, int d );
    DMatrix<Vector<T,3> >&    	  evaluateGlobal( T u, T v, int d1, int d2 );
    DMatrix<Vector<T,3> >&    	  evaluateParent( Point<T,2> p, int d );
    DMatrix<Vector<T,3> >&    	  evaluateParent( T u, T v, int d1, int d2 );
    virtual T                     getCurvatureGauss( T u, T v );
    virtual T                     getCurvatureMean( T u, T v );
    virtual T                     getCurvaturePrincipalMax( T u, T v );
    virtual T                     getCurvaturePrincipalMin( T u, T v );
    int                           getDerivativesU() const;
    int                           getDerivativesV() const;
    Vector<T,3>&                  getDerU( T u, T v );
    Vector<T,3>&                  getDerV( T u, T v );
    Vector<T,3>&                  getDerUU( T u, T v );
    Vector<T,3>&                  getDerVV( T u, T v );
    Vector<T,3>&                  getDerUV( T u, T v );
    std::string                   getIdentity() const;
    virtual T                     getLocalMapping( T t, T ts, T tt, T te );
    Vector<T,3>&                  getNormal();
    T                             getParDeltaU();
    T                             getParDeltaV();
    T                             getParStartU();
    T                             getParStartV();
    T                             getParEndU();
    T                             getParEndV();
    int                           getSamPU( int i = 0 ) const;
    int                           getSamPV( int i = 0 ) const;
    int                           getSamplesU() const;
    int                           getSamplesV() const;
    void                          insertVisualizer( Visualizer *visualizer );
    virtual bool                  isClosedU() const;
    virtual bool                  isClosedV() const;
    virtual bool                  isClosestPoint( const Point<T,3>& q, T& u, T& v );
    virtual void                  preSample( int m1, int m2, int d1, int d2, T s_u = T(0), T s_v = T(0), T e_u = T(0), T e_v = T(0) );
    void                          removeVisualizer( Visualizer *visualizer );
    virtual void                  replot( int m1 = 0, int m2 = 0, int d1 = 0, int d2 = 0 );
    virtual void                  resample(DMatrix<DMatrix <DMatrix <Vector<T,3> > > >	& a, int m1, int m2, int d1, int d2 );
    virtual void                  resample(DMatrix<DMatrix <Vector<T,3> > >& a, int m1, int m2, int d1, int d2, T s_u = T(0), T s_v = T(0), T e_u = T(0), T e_v = T(0));
    virtual void                  resampleNormals( const DMatrix<DMatrix<Vector<T, 3> > > &sample, DMatrix<Vector<T, 3> > &normals ) const;
    void                          setDomainU( T start, T end );
    void                          setDomainUScale( T sc );
    void                          setDomainUTrans( T tr );
    void                          setDomainV( T start, T end );
    void                          setDomainVScale( T sc );
    void                          setDomainVTrans( T tr );
    void                          setNoDer( int d );
    virtual void                  setSurroundingSphere( const DMatrix< DMatrix< Vector<T, 3> > >& p );
    virtual Parametrics<T,2>*     split( T t, int uv );
    void                          toggleDefaultVisualizer();

    Point<T,3>&                   operator () ( T u, T v );

  protected:
    Array< PSurfVisualizer<T>* >  _psurf_visualizers;
    PSurfVisualizer<T>            *_default_visualizer;

    int                           _no_sam_u;    // Number of samples u for single sampling
    int                           _no_sam_v;    // Number of samples v for single sampling

    int                           _no_der_u;    // Number of derivatives u
    int                           _no_der_v;    // Number of derivatives u

    DVector< Vector<T,2> >        _sam_p_u;     // Sample partition u (start/stop)
    DVector< Vector<T,2> >        _sam_p_v;     // Sample partition v (start/stop)

    DVector< int >                _no_sam_p_u;  // Number of samples for each sampling partition in u
    DVector< int >                _no_sam_p_v;  // Number of samples for each sampling partition in v


    // Used by operator() for number of derivative to evaluate.
    int                           _default_d;


    // The result of the previous evaluation
    DMatrix< Vector<T,3> >        _p;           // Position and belonging partial derivatives
    Vector<T,3>                   _n;           // Surface normal, for display in 3D
    T                             _u;           // The parameter value in u-direction used for last evaluation
    T                             _v;           // The parameter value in v-direction used for last evaluation
    int                           _d1;          // Number of derivatives in u-direction computed last time
    int                           _d2;          // Number of derivatives in v-direction computed last time
    bool                          _diagonal;    // True if only upper left half of matrix is evaluated.

    // Shift of parameter
    T                             _tr_u;        // Translate u-parametre
    T                             _sc_u;        // Scale u-parametre

    T                             _tr_v;        // Translate v-parametre
    T                             _sc_v;        // Scale v-parametre

    virtual void                  eval( T u, T v, int d1, int d2, bool lu = true, bool lv = true ) = 0;
    virtual T                     getEndPU() = 0;
    virtual T                     getEndPV() = 0;
    virtual T                     getStartPU() = 0;
    virtual T                     getStartPV() = 0;
    T                             shiftU(T u);
    T                             shiftV(T v);

  private:
    void                          _eval( T u, T v, int d1, int d2 );
    void                          _evalDerDD( DMatrix< DMatrix< Vector<T,3> > >& a, int d1, int d2, T du, T dv ) const;
    void                          _evalNormal();
    void                          _setSam( int m1, int m2 );
    int                           _sum( int i, int j );


  };

}

// Include PSurf class function implementations
#include "gmPSurf.c"


#endif  //__gmDSURF_H__
