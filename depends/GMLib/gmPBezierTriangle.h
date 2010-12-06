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



/*! \file gmPBezierTriangle.h
 *
 *  Interface for the PBezierTriangle class.
 *
 *  \date   2010-03-23
 */

#ifndef __gmPBEZIERTRIANGLE_H__
#define __gmPBEZIERTRIANGLE_H__



#include "gmPTriangle.h"
#include "gmSelector.h"
#include "gmSelectorGrid.h"


namespace GMlib {

  template <typename T>
  class PBezierTriangle : public PTriangle<T> {
  public:
    PBezierTriangle( const DVector< Vector<T,3> >& c );
    PBezierTriangle( const PBezierTriangle& copy );
    ~PBezierTriangle();

    DVector< Vector<T,3> >      getControlPoints();
    virtual void                edit( int selector );
    virtual void                hideSelectors();
    bool                        isSelectorsVisible() const;
    void                        setControlPoints( const DVector< Vector<T,3> >& c );
    virtual void                showSelectors( bool grid, Color selector_color = GMcolor::DarkBlue, Color grid_color = GMcolor::LightGreen );
    void                        updateCoeffs( const Vector<T,3>& d );

  protected:
    DVector< Vector<T,3> >      _c;

    bool                        _selectors;
    SelectorGrid<T,3>*          _sg;
    DVector< Selector<T,3>* >   _s;
    bool                        _c_moved;

    void                        eval( T u, T v, T w );

    T                           getEndPU();
    T                           getEndPV();
    T                           getStartPU();
    T                           getStartPV();

  }; // END class PBezierTriangle



} // END namespace GMlib




// Include PBezierTriangle class function implementations
#include "gmPBezierTriangle.c"


#endif // __gmPBEZIERTRIANGLE_H__
