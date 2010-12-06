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



/*! \file gmVisualizer.c
 *  \brief Visualizer class function implementations
 *
 *  Implementation of the Visualizer class.
 *
 *  \date   2008-09-10
 */


// header
#include "gmVisualizer.h"

namespace GMlib {

  Visualizer::Visualizer() {}

  Visualizer::Visualizer( const Visualizer& ) {}

  Visualizer::~Visualizer() {}

  void Visualizer::_init() {

    _obj = 0x0;
  }

  std::string Visualizer::getIdentity() const {

    return "Visualizer Base";
  }

  void Visualizer::set( SceneObject* obj ) {

    _obj = obj;
  }

  void Visualizer::simulate( double /*dt*/ ) {}

  bool Visualizer::operator == ( const Visualizer* v ) const {

    if( this == v )
      return true;

    return false;
  }

}
