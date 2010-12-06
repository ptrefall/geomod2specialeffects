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



/*! \file gmPCurveGLSLVisualizer.h
 *
 *  Interface for the PCurveGLSLVisualizer class.
 *
 *  \date   2010-04-15
 */


#ifndef __GMPCURVEGLSLVISUALIZER_H__
#define __GMPCURVEGLSLVISUALIZER_H__


// local
#include "gmGLSL.h"
#include "gmPCurveVisualizer"


#ifdef GM_GPU_GLSL

namespace GMlib {

  namespace GLSL {

    template <typename T>
    class PCurveGLSLVisualizer : public PCurveVisualizer<T>, public GLProgram {
    public:
      PCurveGLSLVisualizer();

      void          display();
      std::string   getIdentity() const;

    }; // END class PCurveGLSLVisualizer


  } // END namespace GLSL

} // END namespace GMlib

// Include PSurfGLSLVisualizer class function implementations
#include "gmPCurveGLSLVisualizer.c"

#endif // GM_GPU_GLSL


#endif // __GMPCURVEGLSLVISUALIZER_H__
