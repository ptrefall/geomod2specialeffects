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



/*! \file gmVisualizer.h
 *
 *  Interface for the Visualizer class.
 *
 *  \date   2008-09-10
 */

#ifndef __gmVISUALIZER_H__
#define __gmVISUALIZER_H__


// stl
#include <string>

namespace GMlib {


  class SceneObject;

  class Visualizer {
  public:
    Visualizer();
    Visualizer( const Visualizer& v );
    virtual ~Visualizer();

    virtual void          display() = 0;
    virtual std::string   getIdentity() const;

    virtual void          select() = 0;
    virtual void          set( SceneObject* obj );

    virtual void          simulate( double dt );

    virtual bool          operator == ( const Visualizer* v ) const;


  protected:
    SceneObject           *_obj;


  private:
    void                  _init();
  };



} // END namespace GMlib


#endif // __gmVISUALIZER_H__
