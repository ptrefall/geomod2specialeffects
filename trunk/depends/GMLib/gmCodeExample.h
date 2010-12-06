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



/*! \file gmCodeExample.h
 *  \brief This is a gmCodeExample class
 *
 *  This is a gmCodeExample class, used to test the GMlib classes
 *  and to make examples of the GMlib classes.
 *
 *  \date   2008-07-09
 */

#ifndef __gmCODEEXAMPLE_H__
#define __gmCODEEXAMPLE_H__

#define GMLIB_NAME "GMlib"
#define GMLIB_DESC "A Geometric Modeling Library"


#include <string>

namespace GMlib{


  /*! \class  CodeExample gmCodeExample.h <gmCodeExample>
   *  \brief  This is a CodeExample class
   *
   *  This is a CodeExample class.
   *  A class for automatic output of headers and footers of
   *  examples created for GMlib,
   */
  class CodeExample {
  public:
    CodeExample( bool testClass = false );

    void      printHeader() const;
    void      printFooter() const;

    void      setClassName( const std::string& comp );
    void      setComponent( const std::string& comp );
    void      setDescription( const std::string& desc );
    void      setNumber( int num );
    void      setPrintDelimiter( const std::string& del );
    void      setSubComponent( const std::string& comp );

    //static    print( int lvl, const std::string &str );

  private:
    std::string   _class;
    std::string   _component;
    std::string   _delimiter;
    std::string   _description;
    int           _number;
    std::string   _sub_component;
    bool          _test_class;


     //void     textFormat( int lvl, string str ) const;
  }; //CodeExample


} // END namespace GMlib


#endif // __gmCODEEXAMPLE_H__
