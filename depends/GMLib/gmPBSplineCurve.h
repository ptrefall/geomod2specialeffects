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



/*! \file gmPBSplineCurve.h
 *
 *  Interface for the PBSplineCurve class.
 *
 *  \date   2008-10-28
 */

#ifndef __gmPBSPLINECURVE_H__
#define __gmPBSPLINECURVE_H__


// GMlib includes+
#include "gmPCurve.h"


namespace GMlib {


  template <typename T>
  class PBSplineCurve : public PCurve<T> {
  public:
    PBSplineCurve( const DVector< Vector<T, 3> >& cv, int d  );
    PBSplineCurve( const PBSplineCurve<T>& dpbsc );
    virtual ~PBSplineCurve();

    int                       getDegree() const;
    std::string               getIdentity() const;
    void                      generateKnotVector();
    bool                      isClosed() const;
    void                      resample( DVector< DVector< Vector<T,3> > >& p, int m, int d, T start, T end );
    void                      setControlPoints( const DVector< Vector<T,3> >& cv, bool gen_kv = true );
    void                      setDegree( int d );
    void                      setKnotVector( const DVector<T>& kv );
    void                      setResampleMode( GM_RESAMPLE_MODE mode );
    void                      setScale( T d );


  protected:
    DVector< Vector<T,3> >    _cp;
    T                         _scale;

    DVector< DMatrix< T > >   _bhps;
    DVector< int >            _indices;
    DVector<T>                _kv;
    int                       _degree;

    GM_RESAMPLE_MODE          _resamp_mode;
    bool                      _pre_eval;

    void	                    eval( T t, int d = 0, bool l = false );
    void                      evalBernsteinHermite( DMatrix<T>& bp_mat, T t, int idx ) const;
    T                         getEndP();
    int                       getIndex( T t, int m ) const;
    T                         getStartP();
    T                         getW( T t, int idx, int d ) const;
    T                         getWder( T t, int idx, int d ) const;
    void                      resampleInline( DVector< DVector< Vector<T,3> > >& p, int m, T dt );
    void                      resamplePreEval( DVector< DVector< Vector<T,3> > >& p, int m, T dt );



  }; // END class PBSplineCurve




} // END namepace GMlib

// Include PBSplineCurve class function implementations
#include "gmPBSplineCurve.c"


#endif // __gmPBSPLINECURVE_H__


