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



/*! \file gmPSteinerSurf.h
 *  \brief Interface for the PSteinerSurf class.
 *
 *  \date   2008-09-22
 */

#ifndef __gmPSTEINERSURF_H__
#define __gmPSTEINERSURF_H__



#include <string>

#include "gmPSurf.h"


namespace GMlib {

  template <typename T>
  class PSteinerSurf : public PSurf<T> {
  public:
    PSteinerSurf( T radius = T(20) );
    PSteinerSurf( const PSteinerSurf<T>& dpss );
    virtual ~PSteinerSurf();

    std::string       getIdentity() const;
    bool              isClosedU() const;
    bool              isClosedV() const;


  protected:
    T                 _r;

    void              eval(T u, T v, int d1, int d2, bool lu = true, bool lv = true );
    T                 getEndPU();
    T                 getEndPV();
    T                 getStartPU();
    T                 getStartPV();

  }; // END class PSteinerSurf


} // END namespace GMlib

// Include PSteinerSurf class function implementations
#include "gmPSteinerSurf.c"



#endif // __gmPSTEINERSURF_H__


