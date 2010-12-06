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



/*! \file gmPArc.h
 *
 *  Interface for the PArc class.
 *
 *  \date   2008-11-16
 */

#ifndef __gmPARC_H__
#define __gmPARC_H__


// GMlib includes+
#include "gmPCurve.h"


namespace GMlib {


  template <typename T>
  class PArc : public PCurve<T> {
  public:
    PArc( T speed, T curvature );
    PArc( T speed, T curvature, T start, T end );
    PArc( DVector< Vector<T,3> >& p, T s, T t, T e );
    PArc( const PArc<T>& copy );
    virtual ~PArc();

    T                   getCurvature() const;
    std::string         getIdentity() const;
    T                   getLocalMapping( T t, T ts, T ti, T te );
    T                   getSpeed() const;
    bool                isClosed() const;
    void                setCurvature( T curvature );
    void                setEnd( T end );
    void                setSpeed( T speed );
    void                setStart( T start );


  protected:
    T                   _d;       // Delta
    T                   _k;       // Kappa
    T                   _start;   // Start
    T                   _end;     // End

    void	              eval(T t, int d, bool l);
    T                   getCurvature( DVector< Vector<T,3> >& p );
    T                   getEndP();
    T                   getStartP();

  }; // END class PArc

} // END namepace GMlib

// Include PArc class function implementations
#include "gmPArc.c"


#endif // __gmPARC_H__

