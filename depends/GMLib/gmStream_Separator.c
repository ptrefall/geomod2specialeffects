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



/*! \file gmStream_Separator.c
 *  \brief Inline Separator class implementations.
 *
 *  Inline implementations of the Separator class.
 *
 *  \date   2008-08-03
 */




namespace GMlib {



  /*! Separator(char s, bool b)
   *  \brief  Default Constructor
   *
   *  Initialize _separator and _binary before creating the constructor.
   */
  inline
  Separator::Separator( char s, bool b ) : _binary(b), _separator(s) { }


  /*! Separator( const Separator &s )
   *  \brief  Default Copy Constructor
   *
   *  Initialize _separator and _binary before creating the constructor.
   */
  inline
  Separator::Separator( const Separator &s ) : _binary(s._binary), _separator(s._separator) { }


  /*! bool Separator::getBinary() const
   *  \brief  Get value of binary
   *
   *  \return TRUE/FALSE
   */
  inline
  bool Separator::getBinary() const {

    return _binary;
  }


  /*! char Separator::getSeparator() const
   *  \brief  Get value of separator
   *
   *  \return Char which indicated the separation value
   */
  inline
  char Separator::getSeparator() const {

    return _separator;
  }


  /*! void Separator::setBinary( bool b )
   *  \brief  Set the value of binary
   */
  inline
  void Separator::setBinary( bool b  ) {

    _binary = b;
  }


  /*! void Separator::setSeparator( char s )
   *  \brief  Set the value of separator
   */
  inline
  void Separator::setSeparator( char s ) {

    _separator = s;
  }

}
