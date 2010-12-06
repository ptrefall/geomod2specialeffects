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



/*! \file gmPERBSSurf.h
 *
 *  Interface for the PERBSSurf class.
 *
 *  \date   2008-10-28
 */

#ifndef __gmPERBSSURF_H__
#define __gmPERBSSURF_H__


// GMlib includes
#include "gmPSurf.h"
#include "gmPBezierSurf.h"
#include "gmERBSEvaluator.h"


namespace GMlib {


  template <typename T>
  class PERBSSurf : public PSurf<T> {
  public:
    PERBSSurf(); // Dummy
    PERBSSurf( PSurf<T>* g, int no_locals_u, int no_locals_v, int d1, int d2 );
    PERBSSurf( PSurf<T>* g, int no_locals_u, int no_locals_v, int d1, int d2, T u_s, T u_e, T v_s, T v_e );
    PERBSSurf( const DMatrix< PBezierSurf<T>* >& c, DVector<T> u, DVector<T> v, bool closed_u, bool closed_v );
    PERBSSurf( const PERBSSurf<T>& copy );
    virtual ~PERBSSurf();

    void                                edit( SceneObject *obj );
    void                                generateKnotVector( PSurf<T>* g );
    void                                generateKnotVector( PSurf<T>* g, T u_s, T u_e, T v_s, T v_e );
    std::string                         getIdentity() const;
    DVector<T>&                         getKnotsU();
    DVector<T>&                         getKnotsV();
    DMatrix<PSurf<T>* >&                getLocalPatches();
    int                                 getNoLocalPatchesU() const;
    int                                 getNoLocalPatchesV() const;
    virtual void                        hideLocalPatches();
    bool                                isClosedU() const;
    bool                                isClosedV() const;
    bool                                isLocalPatchesVisible() const;
    void                                preSample( int m1, int m2, int d1, int d2, T s_u, T s_v, T e_u, T e_v );
    void                                setResampleMode( GM_RESAMPLE_MODE mode );
    virtual void                        showLocalPatches();


  protected:
    bool                                _closed_u;
    bool                                _closed_v;

    ERBSEvaluator<T>                    *_evaluator;

    DMatrix< DVector<T> >               _Bu;
    DMatrix< DVector<T> >               _Bv;
    DVector< DVector<T> >               _Bc;
    DMatrix< DMatrix< Vector<T,3> > >   _c0;
    DMatrix< DMatrix< Vector<T,3> > >   _c1;

    DMatrix< int >                      _uk;
    DMatrix< int >                      _vk;
    DVector<T>                          _u;
    DVector<T>                          _v;

    GM_RESAMPLE_MODE                    _resamp_mode;
    bool                                _pre_eval;

    DMatrix< PSurf<T>* >                _c;

    void	                              eval( T u, T v, int d1 = 0, int d2 = 0, bool lu = false, bool lv = false );
    void                                evalPre( T u, T v, int d1 = 0, int d2 = 0, bool lu = false, bool lv = false );
    void                                findIndex( T u, T v, int& iu, int& iv );
    void                                generateKnotVector( DVector<T>& kv, const T s, const T d, int kvd, bool closed );
    void                                getB( DVector<T>& B, const DVector<T>& kv, int tk, T t, int d );
    DMatrix< Vector<T,3> >              getC( T u, T v, int uk, int vk, T du, T dv );
    DMatrix< Vector<T,3> >              getCPre( T u, T v, int uk, int vk, T du, T dv, int iu, int iv );
    T                                   getEndPU();
    T                                   getEndPV();
    T                                   getStartPU();
    T                                   getStartPV();
    virtual void                        init();
    void                                insertPatch( PSurf<T> *patch );

  }; // END class PERBSSurf

} // END namepace GMlib

// Include PERBSSurf class function implementations
#include "gmPERBSSurf.c"


#endif // __gmPERBSSURF_H__



