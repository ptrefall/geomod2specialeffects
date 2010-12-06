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



/*! \file gmEvaluatorStatic.h
 *
 *  Interface for the EvaluatorStatic class.
 *
 *  \date   2008-11-29
 */

#ifndef __gmEVALUATRORSTATIC_H__
#define __gmEVALUATRORSTATIC_H__

#include "gmDMatrix.h"

namespace GMlib {


  template <typename T>
  class EvaluatorStatic {
  public:
    static void evaluateBhp( DMatrix<T>& mat, int degree, T t, T scale );
  };
}


// Include function implementations
#include "gmEvaluatorStatic.c"

#endif // __gmEVALUATORSTATIC_H__
