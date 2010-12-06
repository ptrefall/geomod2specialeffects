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



/*! \file gmPCurvePointsVisualizer.h
 *
 *  Interface for the PCurvePointsVisualizer class.
 *
 *  \date   2010-04-13
 */


#ifndef __GMPCURVEPOINTSVISUALIZER_H__
#define __GMPCURVEPOINTSVISUALIZER_H__

#include "gmPoint.h"
#include "gmColor.h"
#include "gmDVector.h"
#include "gmPCurveVisualizer.h"


namespace GMlib {


  template <typename T>
  class PCurvePointsVisualizer : public PCurveVisualizer<T> {
  public:
    PCurvePointsVisualizer();

    void              display();
    const Color&      getColor() const;
    std::string       getIdentity() const;
    float             getSize() const;
    void              setColor( const Color& color );
    void              setSize( float size );

  protected:
    float             _size;
    Color             _color;
  };

} // END namespace GMlib

// Include PCurvePointsVisualizer class function implementations
#include "gmPCurvePointsVisualizer.c"


#endif // __GMPCURVEPOINTSVISUALIZER_H__
