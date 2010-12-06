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



/*! \file gmSArray.h
 *
 *  Interface for the SArray class (Sortable Array).
 *
 *  \date   2008-07-09
 */

#ifndef __gmSARRAY_H__
#define __gmSARRAY_H__

// GMlib includes
#include "gmArray.h"


namespace GMlib {


  /*! \class  SArray gmSArray.h <SArray>
   *  \brief  This is a Sortable Array class
   *
   *  This is a Sortable Array class.
   */
  template <typename T>
  class SArray : public Array<T> {
  public:
    // All implemented constructor calls the default constructor of Array
    SArray( int n = 6 );            // Call Array(n)
    SArray( int n, T t);            // Call Array(n,t)
    SArray( int n, const T* p );    // Call Array(n,p)
    SArray( const Array<T>& ar );   // Call Array(ar)
    SArray( const ArrayT<T>& ar );  // Call Array(ar)
    SArray( const SArray<T>& ar );  // Call Array(ar)

    void          clear(); // Call Array<T>::clear()
    void          insertAlways( const T& t, bool first = false );
    Array<int>    getSortedIndex();
    bool          removeIndex( int index );
    void          setSorted( bool sort = true );
    void          sort();
    void          sortD();

    SArray<T>& operator  = ( const Array<T>& ar );  // Call Array<T>::operator=
    SArray<T>& operator  = ( const ArrayT<T>& ar ); // Call Array<T>::operator=
    SArray<T>& operator  = ( const SArray<T>& ar ); // Call Array<T>::operator=


  private:
    bool    _sorted;


  }; // END SArray

} // END namespace


// Including template definition file.
#include "gmSArray.c"

#endif // __gmARRAYS_H__


