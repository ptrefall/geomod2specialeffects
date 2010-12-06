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



/*! \file gmPBasisCurve.h
 *
 *  Interface for the PBasisCurve class.
 *
 *  \date   2010-06-21
 */

#ifndef __gmPBASISCURVE_H__
#define __gmPBASISCURVE_H__




#include "gmPCurve.h"
#include "gmBasisEvaluator.h"


namespace GMlib {


  enum GM_BASIS_CURVE_DISPLAY {
    GM_BASIS_CURVE_F      = 0,
    GM_BASIS_CURVE_D      = 1,
    GM_BASIS_CURVE_DD     = 2,
    GM_BASIS_CURVE_DDD    = 3
  };


  template <typename T, typename G = long double>
  class PBasisCurve : public PCurve<T> {
  public:
    PBasisCurve();
    ~PBasisCurve();

    void                            setDisplay( int display );
    void                            setEvaluator( BasisEvaluator<G>* e );

  protected:
    void                            eval( T t, int d, bool l );
    T                               getEndP();
    T                               getStartP();
    bool                            isClosed() const;

  private:
    BasisEvaluator<G>     *_B;
    int                             _d_no;

  }; // class ERBSBasisCurve

} // END namespace GMlib


// Include PBasisCurve class function implementations
#include "gmPBasisCurve.c"


#endif // __gmPBASISCURVE_H__
