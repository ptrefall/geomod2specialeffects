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



/*! \file gmPAsteroidalSphere.h
 *
 *  Interface for the PAsteroidalSphere surface class.
 *
 *  \date   2009-11-29
 */

#ifndef __gmPASTEROIDALSPHERE_H__
#define __gmPASTEROIDALSPHERE_H__


// GMlib includes+
#include "gmPCurve.h"


namespace GMlib {

  template <typename T>
  class PAsteroidalSphere : public PSurf<T> {
  public:
    PAsteroidalSphere( T sx = T(1), T sy = T(1), T sz = T(1) );
    PAsteroidalSphere( const PAsteroidalSphere<T>& copy );

    std::string   getIdentity() const;
    void          setConstants( T sx, T sy, T sz );

  protected:
    T             _a;
    T             _b;
    T             _c;

    void          eval( T u, T v, int d1, int d2, bool lu, bool lv );
    T             getEndPU();
    T             getEndPV();
    T             getStartPU();
    T             getStartPV();
    bool          isClosedU() const;
    bool          isClosedV() const;

  }; // END class PAsteroidalSphere

} // END namespace GMlib


// Include PAsteroidalSphere class function implementations
#include "gmPAsteroidalSphere.c"

#endif // __gmPASTEROIDALSPHERE_H__
