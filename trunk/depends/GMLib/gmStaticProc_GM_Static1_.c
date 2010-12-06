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



/*! \file gmStaticProc_GM_Static1_.c
 *  gmStaticProc GM_Static1_ implementations
 *
 *  \date   2008-07-03
 */


namespace GMlib {



  ///////////////////////////////////////////
  // template <typename T, typename G, int n>
  // class GM_Static1_<T, G, n>::

  /*! void GM_Static1_<T, G, n>::eq(T *a, G* b)
   *  \brief a =  b  set equal
   *
   *  Pending Documentation
   */
  template <typename T, typename G, int n>
  inline
  void GM_Static1_<T, G, n>::eq(T *a, G* b) {
    (*a) = (T)(*b);
    GM_Static1_<T,G,n-1>::eq(a+1,b+1);
  }




  ////////////////////////////////////
  // template <typename T, typename G>
  // class GM_Static1_<T, G, 1>::

  /*! void GM_Static1_<T, G, 1>::eq(T *a, G* b)
   *  \brief a =  b  set equal b
   *
   *  Pending Documentation
   */
  template<typename T, typename G>
  void GM_Static1_<T, G, 1>::eq(T *a, G* b) {
    (*a) = (T)(*b);
  }

}
