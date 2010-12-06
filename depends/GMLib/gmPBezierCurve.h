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



/*! \file gmPBezierCurve.h
 *
 *  Interface for the PBezierCurve class.
 *
 *  \date   2008-10-28
 */

#ifndef __gmPBEZIERCURVE_H__
#define __gmPBEZIERCURVE_H__


// GMlib includes+
#include "gmPCurve.h"
#include "gmSelectorGrid.h"


namespace GMlib {


  template <typename T>
  class PBezierCurve : public PCurve<T> {
  public:
    PBezierCurve( const DVector< Vector<T,3> >& c );
    PBezierCurve( const DVector< Vector<T,3> >& c, T s, T t, T e );
    PBezierCurve( const PBezierCurve<T>& copy );
    virtual ~PBezierCurve();

    void                          edit( int selector );
    DVector< Vector<T,3> >&       getControlPoints();
    int                           getDegree() const;
    std::string                   getIdentity() const;
    T                             getLocalMapping( T t, T ts, T ti, T te );
    virtual void                  hideSelectors();
    bool                          isClosed() const;
    bool                          isSelectorsVisible() const;
    void                          preSample( int m, int d, T start, T end );
    void                          setClosed( bool state );
    void                          setControlPoints( const DVector< Vector<T,3> >& cv );
    void                          setResampleMode( GM_RESAMPLE_MODE mode );
    void                          setScale( T d );
    virtual void                  showSelectors( bool grid = false, const Color& _selector_color = GMcolor::DarkBlue, const Color& grid_color = GMcolor::LightGreen );
    void                          updateCoeffs( const Vector<T,3>& d );


  protected:

    DVector< Vector<T, 3> >       _c;
    T                             _scale;
    DVector< DMatrix< T > >       _t;
    bool                          _closed;

    GM_RESAMPLE_MODE              _resamp_mode;
    bool                          _pre_eval;

    bool                          _selectors;
    SelectorGrid<T,3>*			      _sg;
    DVector< Selector<T,3>* >     _s;
    bool                          _c_moved;

    void	                        eval( T t, int d = 0, bool l = false );
    void                          evalPre( T t, int d = 0, bool l = false );
    void                          findIndex( T t, int& it );
    T                             getEndP();
    T                             getStartP();
    virtual void                  init();
  }; // END class PBezierCurve

} // END namepace GMlib


// Include PBezierCurve class function implementations
#include "gmPBezierCurve.c"


#endif // __gmPBEZIERCURVE_H__

