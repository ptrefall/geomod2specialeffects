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



/*! \file gmArrow3D.h
 *
 *  A graphical implementation of the Arrow class
 *
 *  \date   2009-03-06
 */

#ifndef __gmARROW3D_H__
#define __gmARROW3D_H__




namespace GMlib {

  class Arrow3D : public Arrow<float,3> {
  public:
    Arrow3D( const Arrow<float,3>& a, int m = 7 );

    void    display();

  private:
    int     _m;
    float   _l;
    float   _r;
    float   _h;
    float   _lw;

  }; // END class Arrow3D

} // END namespace GMlib


// Include Arrow3D class inline function implementations
#include "gmArrow3D.c"

#endif // __gmARROW3D_H__
