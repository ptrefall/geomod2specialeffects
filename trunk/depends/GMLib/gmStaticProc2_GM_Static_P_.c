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



/*! \file gmStaticProc2_GM_Static_P_.c
 *
 *  File Description
 *
 *  \date   2008-07-04
 */


namespace GMlib {



  ///////////////////////////////
  // template <typename T, int n, int m>
  // class GM_Static_P_<T,n,m>


  /*! void GM_Static_P_ <T,n,m>::mv_x(T *a, Point<T,m>* b, const Point<T,m>& c)
   *  \brief vec = mat x vec
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static_P_<T,n,m>::mv_x(T *a, Point<T,m>* b, const Point<T,m>& c) {

    (*a)=(*b)*c; GM_Static_P_<T,n-1,m>::mv_x(a+1,b+1,c);
  }


  /*! void GM_Static_P_ <T,n,m>::mv_xq(T *a, T* b, const Point<T,m>& c)
   *  \brief vec = HqMat x vec
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static_P_<T,n,m>::mv_xq(T *a, T* b, const Point<T,m>& c) {

    (*a) = GM_Static_<T,m>::dpr(b,c.getPtr()); GM_Static_P_<T,n-1,m>::mv_xq(a+1,b+m+1,c);
  }


  /*! void GM_Static_P_ <T,n,m>::mv_xqP(T *a, T* b, const Point<T,m>& c, T* d)
   *  \brief vec = HqMat x vec + h(homogen col)
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static_P_<T,n,m>::mv_xqP(T *a, T* b, const Point<T,m>& c, T* d) {

    (*a) = GM_Static_<T,m>::dpr(b,c.getPtr())+(*d); GM_Static_P_<T,n-1,m>::mv_xqP(a+1,b+m+1,c,d+m+1);
  }


  /*! void GM_Static_P_ <T,n,m>::eq_t(Point<T,m> *a, T *b)
   *  \brief a = b^T	matrix transposing
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static_P_<T,n,m>::eq_t(Point<T,m> *a, T *b) {

    GM_Static_P2_<T,n,m,n>::eq_t(a,b);
  }


  /*! void GM_Static_P_<T,n,m>::vv_ox(Point<T,m> *a, const Point<T,m> *b, T *c)
   *  \brief a = b x c tensor (outer) product
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static_P_<T,n,m>::vv_ox(Point<T,m> *a, const Point<T,m> *b, T *c) {

    GM_Static_<T,m>::sc_r(a->getPtr(),b->getPtr(),double(*c)); GM_Static_P_<T,n-1,m>::vv_ox(a+1,b,c+1);
  }


  /*! void GM_Static_P_<T,n,m>::cm_x(T *a, T* b, T* c)
   *  \brief vec = col x mat
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static_P_<T,n,m>::cm_x(T *a, T* b, T* c) {

    (*a) = GM_Static2_<T,m,m>::dpc(b,c); GM_Static_P_<T,n-1,m>::cm_x(a+1,b,c+1);
  }


  /*! void GM_Static_P_<T,n,m>::mc_x(T *a, T *b, T *c)
   *  \brief a = b(col)*c	matrix multiplication, but b is transposed
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static_P_<T,n,m>::mc_x(T *a, T *b, T *c) {

    GM_Static_P_<T,m,m>::cm_x(a,b,c); GM_Static_P_<T,n-1,m>::mc_x(a+m,b+1,c);
  }


  /*! void GM_Static_P_<T,n,m>::sc(Point<T,m>* a, T *b)
   *  \brief scaling of matrix (row by row)
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static_P_<T,n,m>::sc(Point<T,m>* a, T *b) {

    GM_Static_<T,m>::sc(a->getPtr(),(double)*b); return GM_Static_P_<T,n-1,m>::sc(a+1,b+1);
  }

  /*! void GM_Static_P_<T,n,m>::hq_2x(T *a, T* b, const Point<T,m>& c)
   *  \brief vec = HqMat x vec
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static_P_<T,n,m>::hq_2x(T *a, T* b, const Point<T,m>& c) {

    (*a) = GM_Static_<T,m>::dpr(b,c.getPtr()); GM_Static_P_<T,n-1,m>::hq_2x(a+1,b+m+1,c);
  }


  /*! void GM_Static_P_<T,n,m>::hq_3x(T *a, T* b, const Vector<T,m>& r, T* p)
   *  \brief col = vec - vec x HqMat
   *  Pending Documentation
   */
  template <typename T, int n, int m>
  inline
  void GM_Static_P_<T,n,m>::hq_3x(T *a, T* b, const Vector<T,m>& r, T* p) {

    (*a) = (*p) - GM_Static3_<T,m,m>::dpr(r.getPtr(),b); GM_Static_P_<T,n-1,m>::hq_3x(a+m+1,b+1,r,p+1);
  }




  ///////////////////////////////
  //  template <class T,int m>
  //  class GM_Static_P_<T,1,m>


  /*! void GM_Static_P_<T,n,m>::hq_3x(T *a, T* b, const Vector<T,m>& r, T* p)
   *  \brief
   *  Pending Documentation
   */
  template <typename T,int m>
  inline
  void GM_Static_P_<T,1,m>::mv_x(T *a, Point<T,m>* b, const Point<T,m>& c) {

     (*a)=(*b)*c;
  }


  /*! void GM_Static_P_<T,1,m>::mv_xq(T *a, T* b, const Point<T,m>& c)
   *  \brief
   *  Pending Documentation
   */
  template <typename T,int m>
  inline
  void GM_Static_P_<T,1,m>::mv_xq(T *a, T* b, const Point<T,m>& c) {

    (*a) = GM_Static_<T,m>::dpr(b,c.getPtr());
  }


  /*! void GM_Static_P_<T,1,m>::mv_xqP(T *a, T* b, const Point<T,m>& c, T* d)
   *  \brief
   *  Pending Documentation
   */
  template <typename T,int m>
  inline
  void GM_Static_P_<T,1,m>::mv_xqP(T *a, T* b, const Point<T,m>& c, T* d) {

    (*a) = GM_Static_<T,m>::dpr(b,c.getPtr())+(*d);
  }


  /*! void GM_Static_P_<T,1,m>::vv_ox(Point<T,m> *a, const Point<T,m> *b, T *c)
   *  \brief
   *  Pending Documentation
   */
  template <typename T,int m>
  inline
  void GM_Static_P_<T,1,m>::vv_ox(Point<T,m> *a, const Point<T,m> *b, T *c) {

    GM_Static_<T,m>::sc_r(a->getPtr(),b->getPtr(),double(*c));
  }

  /*! void GM_Static_P_<T,1,m>::cm_x(T *a, T* b, T* c)
   *  \brief
   *  Pending Documentation
   */
  template <typename T,int m>
  inline
  void GM_Static_P_<T,1,m>::cm_x(T *a, T* b, T* c) {

    (*a) = GM_Static2_<T,m,m>::dpc(b,c);
  }

  /*! void GM_Static_P_<T,1,m>::mc_x(T *a, T *b, T *c)
   *  \brief
   *  Pending Documentation
   */
  template <typename T,int m>
  inline
  void GM_Static_P_<T,1,m>::mc_x(T *a, T *b, T *c) {

    GM_Static_P_<T,m,m>::cm_x(a,b,c);
  }

  /*! void GM_Static_P_<T,1,m>::sc(Point<T,m>* a, T *b)
   *  \brief
   *  Pending Documentation
   */
  template <typename T,int m>
  inline
  void GM_Static_P_<T,1,m>::sc(Point<T,m>* a, T *b) {

    GM_Static_<T,m>::sc(a->getPtr(),(double)*b);
  }

  /*! void GM_Static_P_<T,1,m>::hq_2x(T *a, T* b, const Point<T,m>& c)
   *  \brief
   *  Pending Documentation
   */
  template <typename T,int m>
  inline
  void GM_Static_P_<T,1,m>::hq_2x(T *a, T* b, const Point<T,m>& c) {

    (*a) = GM_Static_<T,m>::dpr(b,c.getPtr());
  }

  /*! void GM_Static_P_<T,1,m>::hq_3x(T *a, T* b, const Vector<T,m>& r, T* p)
   *  \brief
   *  Pending Documentation
   */
  template <typename T,int m>
  inline
  void GM_Static_P_<T,1,m>::hq_3x(T *a, T* b, const Vector<T,m>& r, T* p) {

    (*a) = (*p) - GM_Static3_<T,m,m>::dpr(r.getPtr(),b);
  }
}
