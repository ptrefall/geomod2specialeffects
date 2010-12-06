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



/*! \file gmPCircularSurface.h
 *
 *  Interface for the PCircularSurface class.
 *
 *  \date   2010-02-14
 */

#ifndef __gmPCircularSurface_H__
#define __gmPCircularSurface_H__



// STL
#include <string>

// GMlib
#include "gmPSurf.h"


namespace GMlib {

  template <typename T>
  class PCircularSurface : public PSurf<T> {
  public:
    PCircularSurface( T radius = T(1) );
    PCircularSurface( T radius, int s1, int s2 );
    PCircularSurface( const PCircularSurface<T>& copy );
    virtual ~PCircularSurface();

  public:
    std::string   getIdentity() const;
    T             getRadius() const;
    void          setRadius( T radius );

  protected:
    T             _radius;

    void          eval(T u, T v, int d1, int d2, bool lu = true, bool lv = true );
    T             getEndPV();
    T             getEndPU();
    T             getStartPU();
    T             getStartPV();
    bool          isClosedU() const;
    bool          isClosedV() const;

  }; // END class PCircularSurface

} // END namespace GMlib

// Include PCircularSurface class function implementations
#include "gmPCircularSurface.c"




#endif // __gmPCircularSurface_H__
