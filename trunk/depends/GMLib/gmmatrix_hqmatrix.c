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



/*! \file gmMatrix_HqMatrix.c
 *
 *  File Description
 *
 *  \date   2008-07-14
 */

namespace GMlib {


  /*! HqMatrix<T, n>::HqMatrix():SqMatrix<T,n+1>()
   *  \brief The default constructor
   *
   *  The constructer gives an I-matrix
   */
  template <typename T, int n>
  inline
  HqMatrix<T, n>::HqMatrix():SqMatrix<T,n+1>()				{}


  /*! HqMatrix<T, n>::HqMatrix(bool i):SqMatrix<T,n+1>(i)
   *  \brief The fast constructor
   *
   *  The constructer gives random contents, there will be no initializing
   */
  template <typename T, int n>
  inline
  HqMatrix<T, n>::HqMatrix(bool i):SqMatrix<T,n+1>(i)			{}


  /*! HqMatrix<T, n>::HqMatrix(const Matrix<T,n+1,n+1>& v):SqMatrix<T,n+1>(v)
   *  \brief The copy constructor
   *
   *  The constructer gives a copy of the input (homogenious) matrix
   */
  template <typename T, int n>
  inline
  HqMatrix<T, n>::HqMatrix(const Matrix<T,n+1,n+1>& v):SqMatrix<T,n+1>(v)	{}


  /*! HqMatrix<T, n>::HqMatrix(const Matrix<T,n+1,n+1>& v, bool trans):SqMatrix<T,n+1>(v,trans)
   *  \brief The transpose copy constructor
   *
   *  The constructer gives a transposed copy of the input (homogenious) matrix if "trans" is true.
   */
  template <typename T, int n>
  inline
  HqMatrix<T, n>::HqMatrix(const Matrix<T,n+1,n+1>& v, bool trans):SqMatrix<T,n+1>(v,trans)	{}


  /*! HqMatrix<T, n>::HqMatrix(const Matrix<T,n,n>& v, bool trans=false):SqMatrix<T,n+1>(false)
   *  \brief The  copy or transpose copy constructor from a sub matrix.
   *
   *  The constructer gives a copy (or transposed copy if "trans" is true) of the
   *  input matrix in the upper left corner.
   *  The rightmost and lowermost vectors are set to 0 exept
   *  for the right lower corner value that is 1.
   */
  template <typename T, int n>
  inline
  HqMatrix<T, n>::HqMatrix( const Matrix<T,n,n>& v, bool trans) : SqMatrix<T,n+1>(trans)	{}


  /*! HqMatrix<T, n>::HqMatrix(const Vector<T,n>& d)
   *  \brief The translation constructor
   *
   *  The constructer gives an homogenious translation matrix.
   */
  template <typename T, int n>
  inline
  HqMatrix<T, n>::HqMatrix( const Vector<T,n>& d  ){

    GM_Static2_<T,n,n+1>::eq2( d.getPtr(), this->getPtr()+n );
  }


  /*! HqMatrix<T, n>::HqMatrix(Angle a,  int x, int y)
   *  \brief The clean rotation constructor
   *
   *  The constructer gives a clean rotation matrix rotating in one
   *  of the main planes (x,y) around origin,
   *  i.e. the default (0,1) - is the xy-plane. Remark the for example (0,1) and (1,0)
   *  is rotation in opposit direction.
   */
  template <typename T, int n>
  inline
  HqMatrix<T, n>::HqMatrix(Angle a,  int x, int y){

    T sina = T(sin(a.getRad())), cosa = T(cos(a.getRad()));
    (*this)[x][x]=cosa; (*this)[y][x]=-sina; (*this)[x][y]=sina; (*this)[y][y]=cosa;
  }


  /*! HqMatrix<T, n>::HqMatrix(Angle a, const Vector<T,n>& u, const Vector<T,n>& v)
   *  \brief The clean general rotation constructor
   *
   *  The constructer gives a rotation matrix rotating in the plane
   *  spanned by the two vectors u and v, but located in origin.
   */
  template <typename T, int n>
  inline
  HqMatrix<T, n>::HqMatrix(Angle a, const Vector<T,n>& u, const Vector<T,n>& v){
    makeOrtho(u, v, *this);
    Matrix<T,n+1,n+1> x(*this);
    rotateXY(a);
    basisChange(x);
  }


  /*! HqMatrix<T, n>::HqMatrix(Angle a, const Vector<T,n>& u, const Vector<T,n>& v, const Point<T,n>& p)
   *  \brief The general rotation constructor
   *
   *  The constructer gives a rotation matrix rotating in the plane
   *  spanned by the two vectors u and v and that is located in the point p.
   */
  template <typename T, int n>
  inline
  HqMatrix<T, n>::HqMatrix(Angle a, const Vector<T,n>& u, const Vector<T,n>& v, const Point<T,n>& p) {

    Vector<T,n> r;
    T sina = (T)sin(a.getRad());
    T cosa = (T)cos(a.getRad());
    makeOrtho(u, v, *this);
    SqMatrix<T,n+1> x(*this);
    GM_Static_<T,n>::rot_xy( this->getPtr(), this->getPtr()+(n+1), sina, cosa);
    basisChange(x);

    T x0 = GM_Static_<T,n>::dpr(p.getPtr(),x.getPtr());
    T x1 = GM_Static_<T,n>::dpr(p.getPtr(),x[1].getPtr());
    r[0] = (x0*cosa-x1*sina);
    r[1] = (x0*sina+x1*cosa);
    GM_Static_P_<T,n-2,n>::hq_2x(r.getPtr()+2,x[2].getPtr(),p);
    GM_Static_P_<T,n,n>::hq_3x(this->getPtr()+n,x.getPtr(),r,p.getPtr());
  }





  /*! Matrix<T,n+1,n+1>& HqMatrix<T, n>::setTranspose(const Matrix<T,n+1,n+1>& v)
   *  \brief
   *
   *
   */
  template <typename T, int n>
  inline
  Matrix<T,n+1,n+1>& HqMatrix<T, n>::setTranspose(const Matrix<T,n+1,n+1>& v) {
    cpy_t(v); return(*this);
  }





  /*! void HqMatrix<T, n>::rotateXY(Angle a, int x=0, int y=1)
   *  \brief Add a rotation to this matrix: (*this) = SqMatrix<T,n>(a,x,y)* (*this)
   *
   *  Add a rotation to this matrix: (*this) = SqMatrix<T,n>(a,x,y)* (*this)
   */
  template <typename T, int n>
  inline
  void HqMatrix<T, n>::rotateXY(Angle a, int x , int y ) {

    GM_Static_<T,n>::rot_xy(this->getPtr()+x*(n+1),this->getPtr()+y*(n+1), T(sin(a.getRad())), T(cos(a.getRad())));
  }


  /*! void HqMatrix<T, n>::rotate(Angle a, const Vector<T,n>& u, const Vector<T,n>& v)
   *  \brief Add a rotation to this matrix: (*this) = SqMatrix<T,n>(a,u,v)* (*this)
   *
   *  Add a rotation to this matrix: (*this) = SqMatrix<T,n>(a,u,v)* (*this)
   */
  template <typename T, int n>
  inline
  void HqMatrix<T, n>::rotate(Angle a, const Vector<T,n>& u, const Vector<T,n>& v){
    HqMatrix<T,n> x(a,u,v);
    *this = *this * x;
  }


  /*! HqMatrix<T, n>::rotate(Angle a, const Vector<T,n>& u, const Vector<T,n>& v, const Point<T,n>& p)
   *  \brief Add a rotation to this matrix: (*this) = SqMatrix<T,n>(a,u,v)* (*this)
   *
   *  Add a rotation to this matrix: (*this) = SqMatrix<T,n>(a,u,v)* (*this)
   */
  template <typename T, int n>
  inline
  void HqMatrix<T, n>::rotate(Angle a, const Vector<T,n>& u, const Vector<T,n>& v, const Point<T,n>& p){
    HqMatrix<T,n> x(a,u,v,p);
    *this = *this * x;
  }


  /*! void HqMatrix<T, n>::rotateGlobal(Angle a, const Vector<T,n>& u, const Vector<T,n>& v)
   *  \brief Add a rotation to this matrix: (*this) = SqMatrix<T,n>(a,u,v)* (*this)
   *
   *  Add a rotation to this matrix: (*this) = SqMatrix<T,n>(a,u,v)* (*this)
   */
  template <typename T, int n>
  inline
  void HqMatrix<T, n>::rotateGlobal(Angle a, const Vector<T,n>& u, const Vector<T,n>& v){
    HqMatrix<T,n> x(a,u,v);
    reverseMult( x );
  }


  /*! HqMatrix<T, n>::rotateGlobal(Angle a, const Vector<T,n>& u, const Vector<T,n>& v, const Point<T,n>& p)
   *  \brief Add a rotation to this matrix: (*this) = SqMatrix<T,n>(a,u,v)* (*this)
   *
   *  Add a rotation to this matrix: (*this) = SqMatrix<T,n>(a,u,v)* (*this)
   */
  template <typename T, int n>
  inline
  void HqMatrix<T, n>::rotateGlobal(Angle a, const Vector<T,n>& u, const Vector<T,n>& v, const Point<T,n>& p){
    HqMatrix<T,n> x(a,u,v,p);
    reverseMult( x );
  }


  /*! void HqMatrix<T, n>::translate(const Vector<T,n> d)
   *  \brief Add a rotation to this matrix: (*this) = SqMatrix<T,n>(a,u,v)* (*this)
   *
   *  Add a rotation to this matrix: (*this) = SqMatrix<T,n>(a,u,v)* (*this)
   */
  template <typename T, int n>
  inline
  void HqMatrix<T, n>::translate(const Vector<T,n> d) {

    HqMatrix<T,n> m(d);
    (*this) = (*this)*m;
  }


  /*! void HqMatrix<T, n>::translateGlobal(const Vector<T,n> d)
   *  \brief Add a rotation to this matrix: (*this) = SqMatrix<T,n>(a,u,v)* (*this)
   *
   *  Add a rotation to this matrix: (*this) = SqMatrix<T,n>(a,u,v)* (*this)
   */
  template <typename T, int n>
  inline
  void HqMatrix<T, n>::translateGlobal(const Vector<T,n> d) {

    HqMatrix<T,n> m(d);
    reverseMult( m );
  }


  /*! void HqMatrix<T, n>::invert2()
   *  \brief Invert
   *
   *  overloaded and use only for orthonormal (n-1 x n-1) sub-matrices.
   *  Inverting this matrix using transposing the nxn upper-left submatrix)
   *  and making the right column equal - multiplication of the right column
   *  with the orginal sub-matrix
   *  NB!  ONLY ROTATION and TRANSLATION !!!!!!
   */
  template <typename T, int n>
  inline
  void HqMatrix<T, n>::invertOrthoNormal() {		// overloaded and use only for orthonormal (n-1 x n-1) sub-matrices (rotation matrices)

    T v[n];
    GM_Static3_<T,n,n>::eq1(v, this->getPtr()+n);
    GM_Static3_<T,n-1,n+1>::trn(this->getPtr()+n+1, this->getPtr()+1);
    GM_Static3_<T,n,n>::cm_x( this->getPtr()+n, this->getPtr(),v);
  }




  /*! Matrix<T,n+1,n+1>& HqMatrix<T, n>::operator=(const Matrix<T,n+1,n+1>& v)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  Matrix<T,n+1,n+1>& HqMatrix<T, n>::operator=(const Matrix<T,n+1,n+1>& v) {
    cpy(v);
    return(*this);
  }


  /*! Point<T,n>		HqMatrix<T, n>::operator*(const Point<T,n>& v)		const
   *  \brief p =  T * q, where p and q are points
   *
   *  Returning a point: p =  T * q, where p and q are points i R^n
   *  and T is this matrix.
   */
  template <typename T, int n>
  inline
  Point<T,n>		HqMatrix<T, n>::operator*(const Point<T,n>& p)		const {

    Point<T,n> r;
    GM_Static_P_<T,n,n>::mv_xqP(r.getPtr(), this->getPtr(), p, this->getPtr()+n);
    return r;
  }


  /*! Vector<T,n>		HqMatrix<T, n>::operator*(const Vector<T,n>& v)		const
   *  \brief u =  T * v, where u and v are vectors
   *
   *  Returning a vector: u =  T * v, where u and v are vectors i R^n
   *  and T is this matrix. NB!! u is not infected by translation.
   */
  template <typename T, int n>
  inline
  Vector<T,n>		HqMatrix<T, n>::operator*(const Vector<T,n>& v)		const {

    Vector<T,n> r;
    GM_Static_P_<T,n,n>::mv_xq(r.getPtr(), this->getPtr(), v);
    return r;
  }


  /*! ScalarPoint<T,n> HqMatrix<T, n>::operator*(const ScalarPoint<T,n>& v)const
   *  \brief  Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  ScalarPoint<T,n> HqMatrix<T, n>::operator*(const ScalarPoint<T,n>& p) const {

    ScalarPoint<T,n> r;
//    GM_Static_P_<T,n,n>::mv_xq(r.getPtr(), this->getPtr(), p.getPos());
    GM_Static_P_<T,n,n>::mv_xqP(r.getPtr(), this->getPtr(), p.getPos(), this->getPtr()+n);
    return r;
  }


  /*! Sphere<T,n>		HqMatrix<T, n>::operator*(const Sphere<T,n>& v)		const
   *  \brief  Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  Sphere<T,n>		HqMatrix<T, n>::operator*(const Sphere<T,n>& s)		const{

    Sphere<T,n> r( s.isValid() );
    if( s.isValid()) {

      // Position
      GM_Static_P_<T,n,n>::mv_xqP(r.getPtr(), this->getPtr(), s.getPos(), this->getPtr()+n);

      // Radius
      Vector<T,n> v(T(0));
      v[0]= s.getRadius();
      v = (*this) * v;
      r.resetRadius( v.getLength() );
    }

    return r;
  }


  /*! Arrow<T,n>		HqMatrix<T, n>::operator*(const Arrow<T,n>& v)		const
   *  \brief  Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  Arrow<T,n>		HqMatrix<T, n>::operator*(const Arrow<T,n>& a)		const{

    Arrow<T,n> r;
    GM_Static_P_<T,n,n>::mv_xqP(r.getPtr(),  this->getPtr(), a.getPos(), this->getPtr()+n);
    GM_Static_P_<T,n,n>::mv_xq(r.getPtr()+n, this->getPtr(), a.getDir());
    return r;
  }

  /*! Box<T,n>		HqMatrix<T, n>::operator*(const Box<T,n>& v)		const
   *  \brief  Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  Box<T,n>		HqMatrix<T, n>::operator*(const Box<T,n>& b)		const {

    Box<T,n> r;
    GM_Static_P_<T,n,n>::mv_xqP(r.getPtr(),   this->getPtr(), b.getPtr(),   this->getPtr()+n);
    GM_Static_P_<T,n,n>::mv_xqP(r.getPtr()+n, this->getPtr(), b.getPtr()+n, this->getPtr()+n);
    return r;
  }


  /*! Matrix<T,n+1,n+1>const&	HqMatrix<T, n>::operator*(const HqMatrix<T,n>& v)	const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  Matrix<T,n+1,n+1>	HqMatrix<T, n>::operator*(const HqMatrix<T,n>& v)	const {

    return (*reinterpret_cast<Matrix<T,n+1,n+1>const*>(this)) *
      (reinterpret_cast<const Matrix<T,n+1,n+1>&>(v));
  }





  // **************************
  // Protected Member Functions


  /*! void HqMatrix<T, n>::hq_cpy(const Matrix<T,n,n>& v)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void HqMatrix<T, n>::hq_cpy(const Matrix<T,n,n>& v) {

    memcpy( this->getPtr(), v.getPtr(), sizeof(Matrix<T,n,n>) );
  }


  /*! void HqMatrix<T, n>::hq_cpy_t(const Matrix<T,n,n>& v)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void HqMatrix<T, n>::hq_cpy_t(const Matrix<T,n,n>& v) {

    GM_Static_P_<T,n,n>::eq_t( this->getPtrP(), v.getPtr() );
  }


  /*! void HqMatrix<T, n>::hq_cpy_r(const Point<T,n>& p,int i)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void HqMatrix<T, n>::hq_cpy_r(const Point<T,n>& p,int i) {

    memcpy((*this)[i].getPtr(),p.getPtr(),sizeof(Point<T,n>));
  }


  /*! void HqMatrix<T, n>::hq_cpy_c(const Point<T,n>& p,int j)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void HqMatrix<T, n>::hq_cpy_c(const Point<T,n>& p,int j) {

    GM_Static3_<T,n,n>::eq2(p.getPtr(),this->getPtr()+j);
  }


  /*! void HqMatrix<T, n>::makeOrtho(const Vector<T,n>& u, const Vector<T,n>& v, Matrix<T,n+1,n+1>& x)
   *  \brief To make an orthonormal set of basis-vectors using vector u and vector v as a start.
   *
   *  To make an orthonormal set of basis-vectors using vector u and vector v as a start.
   */
  template <typename T, int n>
  inline
  void HqMatrix<T, n>::makeOrtho(const Vector<T,n>& u, const Vector<T,n>& v, Matrix<T,n+1,n+1>& x) {

    int i,j,k,ku,kv;
    GM_Static_<T,n>::sc_r(x.getPtr(), u.getPtr(), (1/u.getLength()));
    x[0][n]=T(0);
    GM_Std_<T,n>::ortoNormal(x[1].getPtr(),v.getPtr(), x.getPtr());
    x[1][n]=T(0);
    ku = u.getMaxAbsIndex();
    kv = x[1].getMaxAbsIndex();

    for(k=0,i=2; i<n; i++,k++)
    {
      if(k==ku) k++;
      if(k==kv)
      {
        k++;
        if(k==ku) k++;
      }
      x.initRow(i, k);
    }

    for(i=2;i<n;i++)
    {
      for(j=0; j<i; j++)
      {
        T tmp = GM_Static_<T,n>::dpr(x[i].getPtr(),x[j].getPtr());
        GM_Static_<T,n>::decomp(x[i].getPtr(),x[j].getPtr(),tmp);
      }
      x[i].normalize();
    }
    x.initRow(n,n);
  }

}
