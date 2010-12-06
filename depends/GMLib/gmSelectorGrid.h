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



/*! \file gmSelectorGrid.h
 *  \brief Interface to the SelectorGrid class
 *
 *  Interface to the SelectorGrid class
 *
 *  \date 2008-08-04
 */


#ifndef __gmSELECTORGRID_H__
#define __gmSELECTORGRID_H__


#include "gmSelector.h"


namespace GMlib {

  /*! \class SelectorGrid gmSelectorGrid.h <gmSelectorGrid>
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  class SelectorGrid : public Selector<T,n> {
  public:
    SelectorGrid( Point<T,n>& mp, SceneObject* parent, const Color& c = Color(0.5,0.5,0.9));

    void add(Point<T,n>& p1, Point<T,n>& p2);


  private:
    Array<Point<T,n>* > _c;

    void localDisplay();
    void localSelect();

  }; // END class SelectorGrid

} // END namespace GMlib


#include "gmSelectorGrid.c"



#endif // __gmSELECTORGRID_H__
