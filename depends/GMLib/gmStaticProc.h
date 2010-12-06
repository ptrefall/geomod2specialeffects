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



/*! \file gmStaticProc.h
 *
 *  interface for the Static meta programming
 *  to roll out the code usen in:
 *  Point, Vector, UnitVector, Arrow, Scalarfield, Sphere,
 *  Matrix SqMatrix, HqMatrix classes.
 *
 *  \date   2008-07-02
 */


#ifndef __gmSTATICPROC_H__
#define __gmSTATICPROC_H__



/////////////////////////////////////////
// For Point and Vectors ( 1 dimentional)

namespace GMlib {

  /*! \class  GM_Static_ gmStaticProc.h <gmStaticProc>
   *  \brief  For Point and Vectors ( 1 dimentional)
   *
   *  For Point and Vectors ( 1 dimentional)
   *  [Implementations located in gmStaticProc_GM_Static_.c]
   */
  template <typename T, int n>
  class GM_Static_ {
  public:
    static T	    dpr(T *a, T *b);                                // a*b innerproduct
    static T	    dprm(T *a, T *b);                               // -a*b innerproduct

    static void   eq(T *a, const T& b);                           // a =  b  set equal
    static void   eqm(T *a, T* b);	                              // a = -b

    static void   sc(T *a, double b);                             // a *= b  scale
    static void   sc_r(T *a, T *b, double c);                     // a = b*c scale

    static void   peq(T *a, T *b);	                              // a += b
    static void   meq(T *a, T *b);	                              // a -= b
    static void   xeq(T *a, T* b);                                // a %= b

    static void   eq_p(T *a, T* b, T*c);                          // a = b + c
    static void   eq_m(T *a, T* b, T*c);                          // a = b - c
    static void   eq_x(T *a, T* b, T*c);                          // a = b % c

    static void   rot_xy(T *a, T *b, const T& sa, const T& ca);

    static void   decomp(T *a, T *b, const T& c);                 // a -= c*b
    static void   normalizeHq(T *a, T *b, const T& c);

    static int    maxIndex(T *a);
    static void   maxIdx(T *a, int& i);

  }; // END class GM_Static_

  /* See documentation for main class. This is a terminator */
  template <typename T>
  class GM_Static_<T, 1> {
  public:
    static T	    dpr(T *a, T *b);                                // a*b innerproduct
    static T	    dprm(T *a, T *b);			                          // a*b innerproduct

    static void   eq(T *a, const T& b);                           // a =  b  set equal
    static void   eqm(T *a, T* b);                                // a = -b

    static void   sc(T *a, double b);                             // a *= b  scale a with b
    static void   sc_r(T *a, T *b, double c);                     // a = b*c scale b with c and put into a

    static void   peq(T *a, T *b);                                // a += b
    static void   meq(T *a, T *b);                                // a -= b
    static void   xeq(T *a, T* b);                                // a %= b

    static void   eq_p(T *a, T* b, T*c);                          // a = b + c
    static void   eq_m(T *a, T* b, T*c);                          // a = b - c
    static void   eq_x(T *a, T* b, T*c);                          // a = b % c

    static void   rot_xy(T *a, T *b, const T& sa, const T& ca);

    static void   decomp(T *a, T *b, const T& c);                 // a -= c*b

    static void   maxIdx(T *a, int& i);

  }; // END class GM_Static_<T, 1> "Terminator"










  /*! \class  GM_Static1_ gmStaticProc.h <gmStaticProc>
   *  \brief  Pending Documentation
   *
   *  For Point and Vectors ( 1 dimentional)
   *  [Implementations located in gmStaticProc_GM_Static1_.c]
   */
  template <typename T, typename G, int n>
  class GM_Static1_ {
  public:
    static void eq(T *a, G* b);   // a =  b  set equal

  }; // END class GM_Static1_


  /* See Documentation for main class, this is the terminator */
  template <typename T, typename G>
  class GM_Static1_<T,G,1> {
  public:
    static void eq(T *a, G* b);    // a =  b  set equal

  }; // END class GM_Static1_<T, G, 1> "Terminator"

} // END namespace GMlib



// Include gmPoint for future use
#include "gmPoint.h"

namespace GMlib {

  ///////////////////////////////////////////////////////////
  // For Vectors in Matrices ( column-vectors, using strides)

  /*! \class GM_Static2_ gmStaticProc.h <gmStaticProc>
   *  \brief Pending Documentation
   *
   *  For Vectors in Matrices ( column-vectors, using strides)
   *  [Implementations located in gmStaticProc_GM_Static2_.c]
   */
  template <typename T, int n, int m>
  class GM_Static2_ {
  public:
    static T	    dpr(T *a, T *b);              // a*b innerproduct (row x column) (n x m)
    static T	    dpc(T *a, T *b);              // a*b innerproduct (column x column) (n x m)

    static void   eq1(T *a, T *b);              // a = b  a-vector in n x m  matrix, b-column in m x n matrix
    static void   eq2(T *a, T *b);              // b = a  a-vector in n x m  matrix, b-column in m x n matrix
    static void   eq3(T *a, T *b);              // a = b  a-column in n x m  matrix, b-column in n x m matrix

    static void   sc(T *a, double b);           // a *= b scale column vector
    static void   decomp(T *a, T* b);
    static void   decomp1(T *a, T* b, T& c);

  }; // END class GM_Static2_


  /* See documentation for the main class, this is a terminator */
  template <typename T, int m>
  class GM_Static2_<T, 1, m> {
  public:
    static T	dpr(T *a, T *b);	              // a*b innerproduct (row x column) (n x m)
    static T	dpc(T *a, T *b);                // a*b innerproduct (column x column) (n x m)

    static void eq1(T *a, T *b);		          // a = b  a-vector in n x m  matrix, b-column in transposed matrix
    static void eq2(T *a, T *b);              // b = a  a-vector in n x m  matrix, b-column in transposed matrix
    static void eq3(T *a, T *b);              // b = a  a-column in n x m  matrix, b-column in n x m matrix

    static void sc(T *a, double b);           // a *= b scale column vector

    static void decomp1(T *a, T* b, T& c);
  }; // END class GM_Static2_<T, 1, m> "Terminator"












  /////////////////////////////////////////////////////////////////////
  // For Diagonals in Matrices or homogenius matrix (using strides m+1)


  /*! \class GM_Static3_ gmStaticProc.h <gmStaticProc>
   *  \brief Pending Documentation
   *
   *  For Diagonals in Matrices or homogenius matrix (using strides m+1)
   *  [Implementations located in gmStaticProc_GM_Static3_.c]
   */
  template <typename T, int n, int m>
  class GM_Static3_ {
  public:
    static T	    dpr(T *a, T *b);              // a*b innerproduct (row x column) (n x m)

    static void   eq1(T *a, T *b);              // a = b  a-vector, b-diagonal in matrix
    static void   eq2(T *a, T *b);              // b = a  a-vector, b-diagonal in matrix
    static void   eq3(T *a, T *b);              // b = -a  a-vector, b-diagonal in matrix

    static void   sc(T *a, double b);	          // a *= b scale column vector

    static void   swp(T* a, T* b);	            // swap colomn a and line b
    static void   trn(T* a, T* b);              // swap colomn a and line b

    static void   cm_x(T *a, T* b, T* c);	      // col = -mat x vec

    static void   decomp(T *a, T* b);
    static void   decomp1(T *a, T* b, T& c);

  }; // END class GM_Static3_


  /* See documentation for main class, this is a terminatro */
  template <typename T, int m>
  class GM_Static3_<T, 1, m> {
  public:
    static T	    dpr(T *a, T *b);	            // a*b innerproduct (row x column) (n x m)

    static void   eq1(T *a, T *b);              // a = b  a-vector, b-diagonal in matrix
    static void   eq2(T *a, T *b);              // b = a  a-vector, b-diagonal in matrix
    static void   eq3(T *a, T *b);              // b = a  a-vector, b-diagonal in matrix

    static void   sc(T *a, double b);           // a *= b scale column vector

    static void   swp(T* a, T* b);              // swap colomn a and line b
    static void   trn(T* a, T* b);              // swap colomn a and line b

    static void   cm_x(T *a, T* b, T* c);	      // col = -mat x vec

    static void   decomp1(T *a, T* b, T& c);
  }; // END class GM_Static3_<T, 1, m> "Terminator"













  /*! \class GM_Std_ gmStaticProc.h <gmStaticProc>
   *  \brief Pending Documentation
   *
   *  For Diagonals in Matrices or homogenius matrix (using strides m+1)
   *  [Implementations located in gmStaticProc_GM_Std_.c]
   */
  template <typename T, int n>
  class GM_Std_ {
  public:
    static void b_min_d_c(T *a, T* b, T* c, const T& d);    // a = b - d*c,    a,b,c is n-dim vector, and d is scalar
    static void orto(T *a, T* b, T* c);                     // a = b - <b,c> c , where |c| = 1, and all are n-dim vectors
    static void ortoNormal(T *a, T* b, T* c);               // The same as abow, but normalizing the result 'a' after
  }; // END class GM_Std_


  /* See documentation for Main class, this is the terminator */
  template <typename T>
  class GM_Std_<T,1> {
  public:
    static void b_min_d_c(T *a, T* b, T* c, const T& d);
  }; // END class GM_Std_<T, 1> "Terminator"

} // END namespace GMlib



// Include GM_Static_ class implementations
#include "gmStaticProc_GM_Static_.c"

// Include GM_Static1_ class implementations
#include "gmStaticProc_GM_Static1_.c"

// Include GM_Static2_ class implementations
#include "gmStaticProc_GM_Static2_.c"

// Include GM_Static3_ class implementations
#include "gmStaticProc_GM_Static3_.c"

// Include GM_Std_ class implementations
#include "gmStaticProc_GM_Std_.c"






#endif   // __gmStaticProc_H__

