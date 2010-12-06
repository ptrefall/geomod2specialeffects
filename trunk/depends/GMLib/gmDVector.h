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



/*! \file gmDVector.h
 *
 *  Interface for the Dynamic Vector class.
 *
 *  \date   2008-07-17
 *
 *  \todo
 *  - The invariants (stats) for DVector are: \n
 *    if no allocation: pt  = a, \n
 *    if allocation:	  pt != a. \n
 *    NB! There might be more memory allocated than used, \n
 *    but there is no knowledge about the real size!! \n
 *    To clean up there is the function: resetDim(int d)
 */


#ifndef __gmDVECTOR_H__
#define __gmDVECTOR_H__



// GMlib includes
#include "gmArray.h"


namespace GMlib {


  /*! \class DVector<T>
   *  \brief Interface for the Dynamic Vector class.
   *
   *  Interface for the Dynamic Vector class.
   *  DVector (Dynamic Vector) is a container class which can
   *	dynamic change dimention. together with DMatrix a lot
   *	of standard vector/matrix operations are available.
   */
  template <typename T>
  class DVector {
  public:
    DVector( int i=0 );
    DVector( int i, T val );
    DVector( int i, const T p[] );
    DVector( const DVector<T>& v );
    ~DVector();

    void		      append(T val, int i=1);
    void		      append(const DVector<T>& v);
    void		      clear(T v = T(0));
    int           getDim() const;
    T			        getLength() const;
    T*            getPtr() const;
    DVector<T>&   getReversed() const;
    DVector<T>&   getSubVector(int start, int end) const;
    T&			      getSum() const;
    T&			      getSum(int start, int end) const;
    void		      increaseDim(int i, T val=T(0), bool at_end=true);
    void		      putFirst(T val, int i=1);
    void		      putFirst(const DVector<T>& v);
    void		      resetDim(int i);
    void		      setDim(int i);
    Array<T>&	    toArray() const;

    bool		      operator<(const DVector<T>& m) const;
    DVector<T>&   operator=(const DVector<T>& v);
    DVector<T>&   operator=(T p[]);

    // The += -= %= + - % operators NB!!!! assume the dimension to be equal
    // NB!! this operators are not doubling the dimension!!
    //-----------------------------------------------------------------
    DVector<T>&   operator+=(const DVector<T>&);
    DVector<T>&   operator-=(const DVector<T>&);
    DVector<T>	  operator+( const DVector<T>&) const;
    DVector<T>	  operator-( const DVector<T>&) const;

    // The scalingoperator, there is also a non-member scaling operator with oposit order!!
    //-------------------------------------------------------------------------------------
    DVector<T>&	  operator*=(double d);
    DVector<T>	  operator*(double d) const;
    DVector<T>&	  operator/=(double d);
    DVector<T>	  operator/(double d) const;

    T&            operator[](int i);
    const T&	    operator()(int i) const;


  private:
    int           _n;
    T*            _p;
    T	            _init[4];

    void          _cpy( const DVector<T>& v );
    void          _cpy( const T p[] );

  };



  //***************************************************
  //******   Scaling operators (opposit order)  *******
  //***************************************************


  template <typename T>
  inline
  DVector<T> operator*(const double d, DVector<T> p) {
    return p*=d;
  }


  #ifdef GM_STREAM

  // *****************************
  // IOSTREAM overloaded operators

  template <typename T_Stream, typename T>
  T_Stream& operator << ( T_Stream& out, const DVector<T>& v ) {

    out << v.getDim() << GMseparator::Group;

    for( int i = 0; i < v.getDim(); i++ )
      out << v(i) << GMseparator::Element;

    return out;
  }


  template<typename T_Stream, typename T>
  T_Stream& operator >> ( T_Stream& in, DVector<T>& v ) {

    static Separator gs(GMseparator::Group);
    static Separator es(GMseparator::Element);
    int a;

    in >> a >> gs;

    v.setDim(a);

    for( int i = 0; i < v.getDim(); i++ )
      in >> v[i] >> es;

    return in;
  }

  #endif

  //********************************************************
  // The multiplication operators between two DVectors
  //********************************************************

  template<typename T, typename K>
  inline
  T operator*(const DVector<K>& m, const DVector<T>& v)
  {
  #ifdef DEBUG
    if (m.dim() != v.getDim())
      cerr << "Dimension error, dim1=" << m.getDim() << " ,dim2=" << v.getDim() << endl;
  #endif
    T r(0.0);
    for(int i=0;i<m.getDim();i++) r += m(i)*v(i);
    return r;
  }

  template<typename T, typename K>
  inline
  K operator^(const DVector<K>& m, const DVector<T>& v)
  {
  #ifdef DEBUG
    if (m.dim() != v.getDim())
      cerr << "Dimension error, dim1=" << m.getDim() << " ,dim2=" << v.getDim() << endl;
  #endif
    K r(0.0);
    for(int i=0;i<m.getDim();i++) r += m(i)*v(i);
    return r;
  }


} // END namespace GMlib


// Include implementations
#include "gmDVector.c"




#endif // __gmDVECTOR_H__
