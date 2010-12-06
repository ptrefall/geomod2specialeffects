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



/*! \file gmPButterfly.h
 *
 *  Interface for the PButterfly class.
 *
 *  \date   2008-09-10
 */

#ifndef __gmPBUTTERFLY_H__
#define __gmPBUTTERFLY_H__


// GMlib includes+
#include "gmPCurve.h"


namespace GMlib {


  template <typename T>
  class PButterfly : public PCurve<T> {
  public:
    PButterfly( T size = T(5) );
    PButterfly( const PButterfly<T>& copy );
    virtual ~PButterfly();

    std::string   getIdentity() const;
    bool          isClosed() const;


  protected:
    T             _size;

    void	        eval(T t, int d, bool l);
    T             getEndP();
    T             getStartP();

  }; // END class PButterfly

} // END namepace GMlib

// Include PButterfly class function implementations
#include "gmPButterfly.c"


#endif // __gmPBUTTERFLY_H__

