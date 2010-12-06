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



/*! \file gmPCircle.h
 *
 *  Interface for the PCircle class.
 *
 *  \date   2008-09-09
 */

#ifndef __gmPCIRCLE_H__
#define __gmPCIRCLE_H__


// GMlib includes+
#include "gmPCurve.h"


namespace GMlib {


  template <typename T>
  class PCircle : public PCurve<T> {
  public:
    PCircle( T radius = T(20) );
    PCircle( const PCircle<T>& copy );
    virtual ~PCircle();

    std::string     getIdentity() const;
    T               getRadius();
    bool            isClosed() const;
    void            setRadius( T radius = T(20) );


  protected:
    T               _r;

    void	          eval(T t, int d, bool l);
    T               getEndP();
    T               getStartP();

  }; // END class PCircle




} // END namepace GMlib

// Include PCircle class function implementations
#include "gmPCircle.c"


#endif // __gmPCIRCLE_H__
