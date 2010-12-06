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



/*! \file gmSurroundingSphere.h
 *
 *  Interface for the SurroundingSphere class.
 *
 *  \date   2009-12-26
 */

#ifndef __gmSURROUNDINGSPHERE_H__
#define __gmSURROUNDINGSPHERE_H__


#include "gmDisplayObject.h"
#include "gmColor.h"


namespace GMlib {


  enum GM_SURROUNDINGSPHERE {
    GM_SURROUNDINGSPHERE_TOTAL = 1,
    GM_SURROUNDINGSPHERE_CLEAN  = 2

  };


  class SurroundingSphere : public DisplayObject {
  public:
    SurroundingSphere();
    SurroundingSphere( const SurroundingSphere& copy );

    const Color&        getColor( unsigned int mask ) const;
    std::string         getIdentity() const;
    unsigned int        getSpheres() const;
    bool                isWireframe() const;
    void                setColor( const Color& color, unsigned int mask );
    void                setSpheres( unsigned int mask );
    void                setWireframe( bool wireframe );

  protected:
    void                localDisplay();
    unsigned int        _spheres;
    bool                _wireframe;
    Color               _ct;
    Color               _cc;

  }; // END class SurroundingSphere


} // END namespace GMlib


#endif // __gmSURROUNDINGSPHERE_H__




