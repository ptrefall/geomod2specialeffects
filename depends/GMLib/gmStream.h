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



/*! \file gmStream.h
 *
 *  Interface for the Separator class.
 *
 *  \date   2008-07-02
 */

#ifndef __gmSTREAM_H__
#define __gmSTREAM_H__

// Define GM_STREAM and open for GMlibs template stream operators
//#define GM_STREAM

namespace GMlib {


  /*! \class  Separator gmStream.h <gmStream>
   *  \brief  Interface for the Separator class.
   *
   *  Separator is a class containing a character defining
   *  the read/write separation between elements/objects etc.
   *
   *  FOR FURTHER DEVELOPMENT !!
   *  The invariant (stats) for Separator is:
   *  _binary is default false.
   */
  class Separator {
  public:
    Separator(char s = ' ', bool b = false);
    Separator( const Separator &s );

    bool            getBinary() const;
    char            getSeparator() const;

    void            setBinary(bool b);
    void            setSeparator(char s);


  private:
    bool            _binary;      // If true, don't send the Separator to the stream
    unsigned int    _separator;


  }; // END Separator

  // Predefinitions of the basic separators used throughout the code
  namespace GMseparator {

    extern Separator Element;
    extern Separator Object;
    extern Separator Group;
  }


  // *****************************
  // IOSTREAM overloaded operators

  #ifdef GM_STREAM

  /*! T_Stream& operator << ( T_Stream &out, const Separator &s)
   *  \brief
   *
   *  If Separator's flag for a binary stream has been set
   *  then nothing will be sendt to the stream. The stram
   *  will alsp be left untouch if the Separator is '' <- nothing.
   *
   *  \return T_Stream
   */
  template< typename T_Stream >
  T_Stream& operator << ( T_Stream &out, const Separator &s ) {

    if( !s.getBinary())
      out << s.getSeparator();
    return out;
  }


  /*! T_Stream& operator >> ( T_Stream &in, Separator &s )
   *  \brief
   *
   *  If Separator's flag for a binary stream has been set
   *  then nothing will be retrieved from the stream.
   *
   *  \return T_Stream
   */
  template< typename T_Stream >
  T_Stream& operator >> ( T_Stream &in, Separator &s ) {

    if( s.getBinary() )
      return in;

    if( s.getSeparator() != ' ' && s.getSeparator() != '\t' && s.getSeparator() != '\n') {

      unsigned int tmp;

      in >> tmp;
      s.setSeparator(tmp);
    }
    return in;
  }
  #endif


} // END namespace

// Include inline Seperator class implementations
#include "gmStream_Separator.c"



#endif // __gmSTREAM_H__
