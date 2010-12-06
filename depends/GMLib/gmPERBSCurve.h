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



/*! \file gmPERBSCurve.h
 *
 *  Interface for the PERBSCurve class.
 *
 *  \date   2008-10-31
 */

#ifndef __gmPERBSCURVE_H__
#define __gmPERBSCURVE_H__


// GMlib includes
#include "gmPCurve.h"
#include "gmERBSEvaluator.h"


namespace GMlib {


  template <typename T>
  class PERBSCurve : public PCurve<T> {
  public:
    PERBSCurve(); // Dummy
    PERBSCurve( PCurve<T>* g, int no_locals );
    PERBSCurve( PCurve<T>* g, int no_locals, int d );
    PERBSCurve( const PERBSCurve<T>& copy );
    virtual ~PERBSCurve();

    void                            edit( SceneObject *obj );
    void                            generateKnotVector( PCurve<T>* g );
    std::string                     getIdentity() const;
    DVector< PCurve<T>* >&          getLocalPatches();
    int                             getNoLocalPatches() const;
    virtual void                    hideLocalPatches();
    bool                            isClosed() const;
    bool                            isLocalPatchesVisible() const;
    void                            preSample( int m, int d, T start, T end );
    virtual void                    showLocalPatches();
    void                            setResampleMode( GM_RESAMPLE_MODE mode );

  protected:
    bool                            _closed;

    ERBSEvaluator<long double>      *_evaluator;

    DVector< DVector<T> >           _B;
    DVector< int >                  _tk;
    DVector<T>                      _t;
//
    GM_RESAMPLE_MODE                _resamp_mode;
    bool                            _pre_eval;

    DVector< PCurve<T>* >           _c;

    void                            eval( T t, int d = 0, bool l = false );
    void                            evalPre( T t, int d = 0, bool l = false );
    void                            findIndex( T t, int& it );
    void                            getB( DVector<T>& B, int tk, T t, int d );
    T                               getEndP();
    T                               getStartP();
    virtual void                    init();
    void                            insertPatch( PCurve<T> *patch );

  }; // END class PERBSCurve

} // END namepace GMlib

// Include PERBSCurve class function implementations
#include "gmPERBSCurve.c"


#endif // __gmDPERBSCURVE_H__


