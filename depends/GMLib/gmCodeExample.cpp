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



/*! \file gmCodeExample.cpp
 *
 *  Implementations of the gmCodeExample class.
 *
 *  \date   2008-07-09
 */

#include <iostream>
#include <iomanip>

#include "gmCodeExample.h"
namespace GMlib {


  CodeExample::CodeExample( bool testClass ) {

    _class          = "";
    _component      = "";
    _delimiter      = "\n";
    _description    = "";
    _number         = 0;
    _sub_component  = "";
    _test_class     = testClass;
  }


  void CodeExample::printHeader() const {

    std::cout << std::endl;
    std::cout << "*" << std::endl;
    std::cout << "* " << GMLIB_NAME << " (" << GMLIB_DESC << ") ";

    if(_test_class) {
      std::cout << "TESTING" << std::endl;

    } else {
      std::cout << "EXAMPLE" << std::endl;
    }

    std::cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << std::endl;

    if(_component != "") {
      std::cout << "* Component:         " << _component << std::endl;
    }

    if(_component != "" && _sub_component != "") {
      std::cout << "* Sub Component:     " << _sub_component << std::endl;
    }

    std::cout << "* Number:            " << std::setw(3) << std::setfill( '0' ) << _number << std::endl;
    std::cout << "* Class:             " << _class << std::endl;
    std::cout << "*" << std::endl;
    std::cout << "* Description:       " << _description << std::endl;
    std::cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << std::endl;
    std::cout << std::endl;
  }


  void CodeExample::printFooter() const {

    std::cout << std::endl;
    std::cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *" << std::endl;
    std::cout << "*" << std::endl;
  }


  void CodeExample::setClassName( const std::string& name ) {

    _class = name;
  }


  void CodeExample::setComponent( const std::string& comp ) {

    _component = comp;
  }


  void CodeExample::setDescription( const std::string& desc ) {

    _description = desc;
  }


  void CodeExample::setNumber( int num ) {

    _number = num;
  }


  void CodeExample::setPrintDelimiter( const std::string &del ) {

    _delimiter = del;
  }


  void CodeExample::setSubComponent( const std::string& comp ) {

    _sub_component = comp;
  }

}
