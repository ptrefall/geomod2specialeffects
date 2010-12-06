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



/*! \file gmPERBSTriangle.h
 *
 *  Interface for the PERBSTriangle class.
 *
 *  \date   2010-03-25
 */

#ifndef __gmPERBSTRIANGLE_H__
#define __gmPERBSTRIANGLE_H__


#include "gmArray.h"
#include "gmPTriangle.h"
#include "gmPBezierTriangle.h"
#include "gmERBSEvaluator.h"


namespace GMlib {

  template <typename T>
  class PERBSTriangle : public PTriangle<T> {
  public:
    PERBSTriangle( PBezierTriangle<T>* c0, PBezierTriangle<T>* c1, PBezierTriangle<T>* c2 );
    virtual ~PERBSTriangle();

    void                            edit( SceneObject *obj );
    std::string                     getIdentity() const;
    DVector< PTriangle<T>* >&       getLocalPatches();
    virtual void                    hideLocalPatches();
    bool                            isLocalPatchesVisible() const;
    virtual void                    showLocalPatches();


  protected:
    ERBSEvaluator<long double>      *_basis;
    DVector< PTriangle<T>* >        _c;

    void                            eval( T u, T v, T w );
    void                            getB( DVector<T>& B, T t, int d );
    T                               getEndPU();
    T                               getEndPV();
    T                               getStartPU();
    T                               getStartPV();
    void                            insertPatch( PTriangle<T> *patch );

  }; // END class PERBSTriangle


} // END namespace GMlib

// Include PERBSTriangle class function implementations
#include "gmPERBSTriangle.c"

#endif // __gmPERBSTRIANGLE_H__
