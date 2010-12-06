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



/*! \file gmRandom.h
 *
 *  Interface for the gmRamdon template class.
 *
 *  \date   2008-07-16
 */

#ifndef __gmRANDOM_H__
#define __gmRANDOM_H__

// Numeric includes
#include <cmath>

// System includes
#include <cstdlib>


namespace GMlib {


  /*! \class  Random gmRandom.h <gmRandom>
   *  \brief  This is a Random class
   *
   *  This is a Random class.
   */
  template <typename T>
  class Random {
  public:
    Random();
    Random( T vLow, T vHigh );

    T       get();
    void    set( T vLow, T vHigh );
    //void    setGauss( float sigma, float sentervalue );
    void    setSeed( unsigned int s );


  private:
    T     _high, _low;


  }; // END class


} // END namespace


// Including template definition file.
#include "gmRandom.c"

#endif // __gmRANDOM_H__
