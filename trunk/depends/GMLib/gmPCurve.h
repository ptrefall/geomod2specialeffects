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



/*! \file gmPCurve.h
 *
 *  Interface for the PCurve class.
 *
 *  \date   2008-09-09
 */

#ifndef __gmPCURVE_H__
#define __gmPCURVE_H__


#include "gmArray.h"
#include "gmParametrics.h"
#include "gmDVector.h"
#include "gmPCurveVisualizer.h"



namespace GMlib {


  template <typename T>
  class PCurve : public Parametrics<T,1> {
  public:
    PCurve( int s = 20 );
    PCurve( const PCurve<T>& copy );
    ~PCurve();

    void                      enableDefaultVisualizer( bool enable = true );
    DVector<Vector<T,3> >&    evaluate( T t, int d );
    DVector<Vector<T,3> >&    evaluateGlobal( T t, int d );
    DVector<Vector<T,3> >&    evaluateParent( T t, int d );
    T                         getCurvature( T t );
    T                         getCurveLength( T a = 0, T b = -1 );
    int                       getDerivatives() const;
    Vector<T,3>               getDer1( T t );
    Vector<T,3>               getDer2( T t );
    std::string               getIdentity() const;
    float                     getLineWidth() const;
    virtual T                 getLocalMapping( T t, T ts, T ti, T te );
    T                         getParDelta();
    T                         getParEnd();
    T                         getParStart();
    T                         getRadius( T t );
    int                       getSamples() const;
    T                         getSpeed( T t );
    void                      insertVisualizer( Visualizer* visualizer );
    virtual bool              isClosed() const;
    virtual void              preSample( int m, int d, T s = T(0), T e = T(0) );
    virtual void              replot( int m = 0, int d = 2 );
    void                      removeVisualizer( Visualizer* visualizer );
//    virtual void              resample( Array<Point<T,3> >& a, T eps );	// Always smooth, requires derivatives
//    virtual void              resample( Array<Point<T,3> >& a, int m );					// Given sampling rate
//    virtual void              resample( Array<Point<T,3> >& a, int m, T start, T end );	// Given sampling rate
    virtual void              resample( DVector< DVector< Vector<T, 3> > >& p, int m, int d, T start, T end );
    void                      setDomain( T start, T end );
    void                      setDomainScale( T sc );
    void                      setDomainTrans( T tr );
    void                      setLineWidth( float width = 1.0 );
    void                      setNoDer( int d );
    virtual void              setSurroundingSphere( const DVector< DVector< Vector<T, 3> > >& p );
    void                      toggleDefaultVisualizer();

    Point<T,3>                operator()( T t );

  protected:
    Array<PCurveVisualizer<T>*>   _pcurve_visualizers;
    PCurveVisualizer<T>           *_default_visualizer;

    int                       _no_sam;      // Number of samples for single sampling
    int                       _no_der;      // Number of derivatives
    float                     _line_width;


    DVector< Vector<T,2> >    _sam_p;       // Sampling partition (start/stop)
    DVector< int >            _no_sam_p;    // Number of samples for each partition
    int                       _defalt_d;    // used by operator() for number of derivative to evaluate.


    // The result of the previous evaluation
    DVector<Vector<T,3> >     _p;           // Position and belonging derivatives
    T                         _t;           // The parameter value used for last evaluation
    int                       _d;           // Number of derivatives computed last time

    // Shift of parameter.
    T                         _tr;          // translate
    T                         _sc;          // scale

    virtual void              eval(T t, int d, bool l = true ) = 0;
    virtual T                 getEndP() = 0;
    virtual T                 getStartP() = 0;
    T                         shift( T t );

  private:
    void                      _eval( T t, int d );
    void                      _evalDerDD( DVector< DVector< Vector<T, 3> > > & p, int d, T du ) const;
    T                         _integral(T a, T b, double eps);

  }; // END class PCurve

} // END namespace GMlib

// Include PCurve class function implementations
#include "gmPCurve.c"


#endif  // __gmPCURVE_H__

