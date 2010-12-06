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



/*! \file gmStaticProc_GM_Std_.c
 *  gmStaticProc GM_Std_ implementations
 *
 *  \date   2008-07-04
 */


namespace GMlib {



  ///////////////////////////////
  // template <typename T, int n>
  // class GM_Std_<T, n>::


  /*! void GM_Std_<T, n>::b_min_d_c( T *a, T* b, T* c, const T& d)
   *  \brief a = b - d*c,    a,b,c is n-dim vector, and d is scalar
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void GM_Std_<T, n>::b_min_d_c( T *a, T* b, T* c, const T& d) {
    (*a) = (*b) - d*(*c);
    GM_Std_<T,n-1>::b_min_d_c(a+1,b+1,c+1,d);
  }

  /*! void GM_Std_<T, n>::orto(T *a, T* b, T* c)
   *  \brief a = b - <b,c> c , where |c| = 1, and all are n-dim vectors
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void GM_Std_<T, n>::orto(T *a, T* b, T* c) {
    T d = GM_Static_<T,n>::dpr(b,c);
    GM_Std_<T,n>::b_min_d_c(a,b,c,d);
  }

  /*! void GM_Std_<T, n>::ortoNormal(T *a, T* b, T* c)
   *  \brief The same as abow, but normalizing the result 'a' after \see void GM_Std_<T, n>::orto(T *a, T* b, T* c)
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void GM_Std_<T, n>::ortoNormal(T *a, T* b, T* c) {
    GM_Std_<T,n>::orto(a,b,c);
    T d = GM_Static_<T,n>::dpr(a,a);
    GM_Static_<T,n>::sc(a,sqrt(1/d));
  }






  ////////////////////////
  // template <typename T>
  // class GM_Std_<T, 1>::

  /*! void GM_Std_<T, 1>b_min_d_c(T *a, T* b, T* c, const T& d)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T>
  inline
  void GM_Std_<T, 1>::b_min_d_c(T *a, T* b, T* c, const T& d) {
    (*a) = (*b) - d*(*c);
  }

}
