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



/*! \file gmArrayT.h
 *
 *  Interface for the Array Tiny class.
 *
 *  \date   2008-07-09
 */

#ifndef __gmARRAYT_H__
#define __gmARRAYT_H__

#include <stddef.h>
#include <iostream>


namespace GMlib {


  /*! \class  ArrayT gmArrayT.h <gmArrayT>
   *  \brief  This is Array Tiny class
   *
   *  This is Array Tiny class.
   */
  template <typename T>
  class ArrayT {
  public:
    ArrayT( int size = 0);
    ArrayT( const ArrayT<T>& ar );
    ArrayT( const Array<T>& ar );
    ArrayT( int size, const T* pt, bool copy = true);
    ~ArrayT();

    T&        back();
    void      clear();
    bool		  empty() const;
    bool      exist( const T& t ) const;
    T&        front();
    T&        getBack();                    // Alias: back()
    T&        getFront();                   // Alias: front()
    int       getIndex( const T& t ) const; // Alias: index()
    int       getMaxSize() const;           // Alias: max_size()
    int       getSize() const;              // Alias: size()
    int       index( const T& t ) const;
    bool      insert( const T& t, bool first = false );
    bool      insert( const ArrayT<T>& ar, bool first = false );
    void      insertAlways( const T& t, bool first = false );
    void      insertAlways( const ArrayT<T>& ar, bool first = false );
    void      insertBack( const T& t );
    void      insertBack( const ArrayT<T>& ar);
    void      insertFront( const T& t );
    void      insertFront( const ArrayT<T>& ar );
    bool      isEmpty() const;                    // Alias: empty()
    bool      isExisting( const T& t ) const;     // Alias: exist()
    void      makeUnique();
    int       max_size() const;
    void      pop_back();                         // Alias: removeBack()
    void      pop_front();                        // Alias: removeFront()
    void      push_back( const T& t );            // Alias: insertBack(const T&)
    void      push_back( const ArrayT<T>& ar );   // Alias: insertBack(const ArrayT<T>&)
    void      push_front( const T& t );           // Alias: insertFront(const T&)
    void      push_front( const ArrayT<T>& ar );  // Alias: insertFront(const ArrayT<T>&)
    bool      remove( const T& t );
    bool      removeBack();
    bool      removeFront();
    bool      removeIndex( int index );
    void      resetSize();
    void      resize( int size );
    void      reverse();
    void      setMaxSize( int size );
    void      setSize( int size );
    int       size() const;
    void      strip();
    void      swap( int i, int j );

    static
    void      setIncr( int i );

    T&          operator [] ( int j );
    const T&    operator () ( int j ) const;

    ArrayT<T>&  operator =  ( const ArrayT<T>& ar );

    void        operator += ( const T& t );
    void        operator += ( const ArrayT<T>& ar );

    bool        operator == ( const ArrayT<T>& ar ) const;
    bool        operator != ( const ArrayT<T>& ar ) const;


  private:
    short         _no_elements;
    short         _max_elements;
    T             *_ptr;
    static int    _size_incr;



  // *****************************
  // IOSTREAM overloaded operators

  #ifdef GM_STREAM

  private:
    ostream& _printOut( ostream& out ) const;
    istream& _printIn( istream& in ) ;


  public:
    friend
    ostream& operator << ( ostream& out, const ArrayT<T>& ar ) {

      return ar._printOut( out );
    }

    friend
    istream& operator >> ( istream& in, ArrayT<T>& ar ) {

      return ar._printIn( in );
    }

    void print( char prompt[] = "ArrayT<T>", ostream& out = std::cout ) const;

  #endif

  }; // END ArrayT

} // END namespace


// Including template definition file.
#include "gmArrayT.c"

#endif // __gmARRAYT_H__


