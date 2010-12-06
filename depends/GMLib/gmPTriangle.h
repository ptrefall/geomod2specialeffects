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



/*! \file gmPTriangle.h
 *
 *  Interface for the PTriangle class.
 *
 *  \date   2010-03-22
 */

#ifndef __gmPTRIANGLE_H__
#define __gmPTRIANGLE_H__


#include "gmPoint.h"
#include "gmDMatrix.h"
#include "gmParametrics.h"


namespace GMlib {

  template <typename T>
  class PTriangleVisualizer;

  template <typename T>
  class PTriangle : public Parametrics<T,2> {
  public:
    PTriangle( int samples = 20 );
    PTriangle( const PTriangle<T>& copy );
    ~PTriangle();

    void                              enableDefaultVisualizer( bool enable = true );
    const DMatrix<Vector<T,3> >&      evaluateGlobal( T u, T v, int d1, int d2 );
    const DMatrix<Vector<T,3> >&      evaluateLocal( T u, T v, int d1, int d2 );
    const DMatrix<Vector<T,3> >&      evaluateParent( T u, T v, int d1, int d2 );

    virtual T                         getCurvatureGauss( T u, T v );
    virtual T                         getCurvatureMean( T u, T v );

    const Vector<T,3>&                getDerU( T u, T v );
    const Vector<T,3>&                getDerV( T u, T v );
    const Vector<T,3>&                getDerUU( T u, T v );
    const Vector<T,3>&                getDerVV( T u, T v );
    const Vector<T,3>&                getDerUV( T u, T v );
    std::string                       getIdentity() const;
    const Vector<T,3>&                getNormal( T u, T v );
    T                                 getParDeltaU();
    T                                 getParDeltaV();
    T                                 getParEndU();
    T                                 getParEndV();
    T                                 getParStartU();
    T                                 getParStartV();
    UnitVector<T,3>                   getUnitNormal( T u, T v );
    void                              insertVisualizer( Visualizer *visualizer );
    virtual bool                      isClosestPoint( const Point<T,3>& p, T& u, T& v );
    void                              removeVisualizer( Visualizer *visualizer );
    virtual void                      replot( int m = 0 );
//    virtual void                      resample(DVector<DMatrix<Vector<T,3> > >& p, int m, int d1, int d2, T s_u = T(0), T s_v = T(0), T e_u = T(0), T e_v = T(0));
    virtual void                      resample( DVector<DMatrix<Vector<T, 3> > > &p, int m );
    void                              setDomainU( T start, T end );
    void                              setDomainUScale( T sc );
    void                              setDomainUTrans( T tr );
    void                              setDomainV( T start, T end );
    void                              setDomainVScale( T sc );
    void                              setDomainVTrans( T tr );
    void                              setEval(int d);
    Parametrics<T,2>*                 split( T t, int uv );
    virtual void                      updateCoeffs( const Vector<T,3>& d );
//    virtual void                      estimateClpPar(const Point<T,n>& p, T& u, T& v) {}
//    virtual void                      setBp( Array<Point<T,n> >bp ) {}
    void                              toggleDefaultVisualizer();

    const Point<T,3>&                 operator()( T u, T v );






  protected:
    Array< PTriangleVisualizer<T>* >  _ptriangle_visualizers;
    PTriangleVisualizer<T>            *_default_visualizer;

    int                               _no_sam;      //  int				__sam;
    DMatrix< Vector<T,3> >            _p;           //  DMatrix<Vector<T,n> >	__p;
    Vector<T,3>                       _n;           //  Vector<T,3>		__n; // For display in 3D
    T                                 _u;           //  T	__u;
    T                                 _v;           //  T	__v;
    int                               _d1;          //  int	__d1;
    int                               _d2;          //  int	__d2;
    bool                              _diagonal;    //  bool	__diagonal; // True if only upper left half is evaluated.
    int                               _default_d;   //  int	__defalt_d; // used by operator() for number of derivative to evaluate.

    T                                 _tr_u;        //  T	__tr_u;	// translate u-parametre
    T                                 _sc_u;        //  T	__sk_u;	// skale
    T                                 _tr_v;        //  T	__tr_v;	// translate v-parametre
    T                                 _sc_v;        //  T	__sk_v;	// skale


    virtual void                      eval( T u, T v, T w ) = 0;
    virtual T                         getEndPU() = 0;
    virtual T                         getEndPV() = 0;
    virtual T                         getStartPU() = 0;
    virtual T                         getStartPV() = 0;


    virtual void                      setSurroundingSphere( const DVector<DMatrix<Vector<T, 3> > > &p );


    T                                 shiftU( T u );
    T                                 shiftV( T u );


  private:
    void                              _eval( T u, T v );
    int                               _sum(int i);


  }; // END class PTriangle





} // END namespace GMlib



// Include PTriangle class function implementations
#include "gmPTriangle.c"



#endif // __gmPTRIANGLE_H__
