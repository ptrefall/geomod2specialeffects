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



/*! \file gmParametrics.h
 *
 *  Interface for the Parametrics class.
 *
 *  \date   2009-01-26
 */

#ifndef __gmPARAMETRICS_H__
#define __gmPARAMETRICS_H__

// Global namespace types
namespace GMlib {


  enum GM_PARAMETRICS {
    GM_POINT = 0,
    GM_CURVE = 1,
    GM_SURFACE = 2,
    GM_FLOW = 3
  };

  enum GM_RESAMPLE_MODE {
    GM_RESAMPLE_INLINE,
    GM_RESAMPLE_PREEVAL
  };

  enum GM_DERIVATION_METHOD {
    GM_DERIVATION_EXPLICIT,
    GM_DERIVATION_DD
  };

} // END namespace GMlib


// STL
#include <string>

// GMlib
#include "gmArray.h"
#include "gmMaterial.h"
#include "gmDisplayObject.h"

namespace GMlib {


  template <typename T, int n>
  class Parametrics : public DisplayObject {
  public:
    Parametrics();
    Parametrics( const Parametrics<T,n>& copy );
    ~Parametrics();

    void                                  rotate(Angle a, const Vector<float,3>& rot_axel);
    void                                  rotate(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d);
    void                                  rotateGlobal(Angle a, const Vector<float,3>& rot_axel);
    void                                  rotateGlobal(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d);
    void                                  setDerivationMethod( GM_DERIVATION_METHOD method );
    void                                  translate(const Vector<float,3>& trans_vector);
    void                                  translateGlobal(const Vector<float,3>& trans_vector);

  protected:
    GM_DERIVATION_METHOD                  _dm;

  private:
    void                                  _initSoType();


  }; // END class Parametrics
}

// Include Paramterics class function implementations
#include "gmParametrics.c"



#endif // __gmPARAMETRICS_H__
