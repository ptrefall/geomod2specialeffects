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



/*! \file gmCoordinateSystem.h
 *
 *  Interface for the CoordinateSystem class.
 *  Rewrite/port of the old VCoordinateSystem of 2009-08-25
 *
 *  \date   2009-12-21
 */

#ifndef __gmCOORDINATESYSTEM_H__
#define __gmCOORDINATESYSTEM_H__


// STL
#include <string>

// GMlib
#include "gmDisplayObject.h"


namespace GMlib {


  enum GM_COORDSYS {
    GM_COORDSYS_LOCAL,
    GM_COORDSYS_GLOBAL,
    GM_COORDSYS_PARENT
  };

  class CoordinateSystem : public DisplayObject {
  public:
    CoordinateSystem();
    CoordinateSystem( const CoordinateSystem& copy );
    ~CoordinateSystem();

    GM_COORDSYS        getCoordinateSystem() const;
    std::string        getIdentity() const;
    void               setCoordinateSystem( GM_COORDSYS coordsys );

  protected:
    void               localDisplay();

    GM_COORDSYS        _cs;


  };

} // END namespace GMlib


#endif // __gmCOORDINATESYSTEM_H__





