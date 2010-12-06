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



/*! \file gmMatrix_SqMatrix.c
 *
 *  File Description
 *
 *  \date   2008-07-14
 */


namespace GMlib {


  /*! SqMatrix<T, n>::nSqMatrix(): Matrix<T,n,n>()
   *  \brief The default constructor
   *
   *  The constructer gives an I-matrix
   */
  template <typename T, int n>
  inline
  SqMatrix<T, n>::SqMatrix() : Matrix<T,n,n>() {
  }


  /*! SqMatrix<T, n>::SqMatrix(bool i): Matrix<T,n,n>(i)
   *  \brief The fast constructor
   *
   *  The constructer gives random contents, there will be no initializing
   */
  template <typename T, int n>
  inline
  SqMatrix<T, n>::SqMatrix(bool i): Matrix<T,n,n>(i) {
  }


  /*! SqMatrix<T, n>::SqMatrix(const Point<T,n>& r, const Point<T,n>& c): Matrix<T,n,n>(r,c)
   *  \brief The tensor (outer) product constructor
   *
   *  The constructer gives an tensor (outer) product of the two vectors that is the parameters
   */
  template <typename T, int n>
  inline
  SqMatrix<T, n>::SqMatrix(const Point<T,n>& r, const Point<T,n>& c): Matrix<T,n,n>(r,c) {
  }


  /*! SqMatrix<T, n>::SqMatrix(const Vector<Vector<T,n>,n>& m): Matrix<T,n,n>(m)
   *  \brief The copy constructor
   *
   *  The constructer gives a copy of the input Vector<Vector> i.e. matrix
   */
  template <typename T, int n>
  inline
  SqMatrix<T, n>::SqMatrix(const Vector<Vector<T,n>,n>& m): Matrix<T,n,n>(m) {
  }


  /*! SqMatrix<T, n>::SqMatrix(const Vector<Vector<T,n>,n>& m, bool trans): Matrix<T,n,n>(m,trans)
   *  \brief The transpose copy constructor
   *
   *  The constructer gives a transposed copy of the input matrix if "trans" is true.
   */
  template <typename T, int n>
  inline
  SqMatrix<T, n>::SqMatrix(const Vector<Vector<T,n>,n>& m, bool trans): Matrix<T,n,n>(m,trans) {
  }


  /*! SqMatrix<T, n>::SqMatrix(Angle a, const Vector<T,n>& u, const Vector<T,n>& v)
   *  \brief The copy or transpose constructor
   *
   *  If true, the constructer gives a transpoded copy of the input
   *  classical vector, i.e. matrix, else it only makes a
   *  matrix copy of the classical vactor.
   *
   *  Make a rotation matrix in the plane span by vectors u and v.
   */
  template <typename T, int n>
  inline
  SqMatrix<T, n>::SqMatrix(Angle a, const Vector<T,n>& u, const Vector<T,n>& v){
    makeOrtho(u, v, *this);
    Matrix<T,n,n> x(*this);
    rotateXY(a);
    basisChange(x);
  }


  /*! SqMatrix<T, n>::SqMatrix(const T* m, bool trans): Matrix<T,n,n>(m,trans)
   *  \brief The rotation constructor
   *
   *  The constructer gives a rotation matrix rotating in one
   *  of the main planes (x,y),
   *  i.e. the default (0,1) - is the xy-plane. Remark the for example (0,1) and (1,0)
   *  is rotation in opposit direction.
   */
  template <typename T, int n>
  inline
  SqMatrix<T, n>::SqMatrix(const T* m, bool trans): Matrix<T,n,n>(m,trans) {}


  /*! SqMatrix<T, n>::SqMatrix(Angle a, int x = 0, int y=1)
   *  \brief The general rotation constructor
   *
   *  The constructer gives a rotation matrix rotating in the plane
   *  spanned by the two vectors u and v.
   *
   *  Make a rotation matrix in one of the main planes (x,y) (0,1)-is xy-plane.
   *  Remark the for example (0,1) and (1,0) is rotation in opposit direction.
   */
  template <typename T, int n>
  inline
  SqMatrix<T, n>::SqMatrix(Angle a, int x, int y) {
    T sina = T(sin(a.getRad())), cosa = T(cos(a.getRad()));
    (*this)[x][x]=cosa; (*this)[y][x]=-sina; (*this)[x][y]=sina; (*this)[y][y]=cosa;
  }


  /*! Matrix<T,n,n> const& SqMatrix<T, n>::transpose()
   *  \brief
   *
   *
   */
  template <typename T, int n>
  inline
  Matrix<T,n,n> const& SqMatrix<T, n>::transpose() {
    GM_Static3_<T,n-1,n>::trn(( this->getPtrP()+1)->getPtr(), this->getPtr()+1);
    return(*this);
  }//Matrix<T,n,n> v(*this,true); *this = v; return(*this);}


  /*! Matrix<T,n,n> const& SqMatrix<T, n>::transposeMult(const Matrix<T,n,n>& m) const
   *  \brief Mutiplicate transpose of this matrix to matrix m: (*this) = T(*this) *  m
   *
   *  Mutiplicate transpose of this matrix to matrix m: (*this) = T(*this) *  m
   */
  template <typename T, int n>
  inline
  Matrix<T,n,n> const& SqMatrix<T, n>::transposeMult(const Matrix<T,n,n>& m) const {	// Not changing this: a = this->transpose * m
    static Matrix<T,n,n> r;
    GM_Static_P_<T,n,n>::mc_x(r.getPtr(), this->getPtr(),m.getPtr());
    return r;
  }


  /*! Matrix<T,n,n> const& SqMatrix<T, n>::reverseMult(const Matrix<T,n,n>& m)
   *  \brief Mutiplicate matrix m to this matrix in reverce order : (*this) = m * (*this)
   *
   *  Mutiplicate matrix m to this matrix in reverce order : (*this) = m * (*this)
   */
  template <typename T, int n>
  inline
  Matrix<T,n,n> const& SqMatrix<T, n>::reverseMult(const Matrix<T,n,n>& m) {		// Changing this ( is a kind of *= operator): *this = m * *this
    static Matrix<T,n,n> r;
    GM_Static_P2_<T,n,n,n>::mm_x(r.getPtrP(), m.getPtrP(), this->getPtr());
    return *this = r;
  }

  /*! void SqMatrix<T, n>::setDiagonal(const Point<T,n>& r)
   *  \brief
   *
   *
   */
  template <typename T, int n>
  inline
  void SqMatrix<T, n>::setDiagonal(const Point<T,n>& r) {
    cpy_d(r);
  }

  /*! Point<T,n> const&  SqMatrix<T, n>::getDiagonal(int i) const
   *  \brief
   *
   *
   */
  template <typename T, int n>
  inline
  Point<T,n> const&  SqMatrix<T, n>::getDiagonal(int i) const	{
    return getStatDiagonal(i);
  }


  /*! void SqMatrix<T, n>::invert()
   *  \brief The general inversion of a matrix using full pivoting.
   *
   *  The general inversion of a matrix using full pivoting.
   *  Ordinary LU-decomp used.
   */
  template <typename T, int n>
  inline
  void SqMatrix<T, n>::invert() {
    SqMatrix<T,n> a(*this);
    Vector<int,n> indx;
    Vector<double,n> vv;

    const double TINY=1.0e-20;
    int i,j,imax,k;
    double big,dum,sum,temp;

    double d=1.0;
    for (i=0;i<n;i++)
    {
      big=0.0;
      for (j=0;j<n;j++) if ((temp = std::fabs(a[i][j])) > big) big=temp;
    //	if (big == 0.0)  nrerror("Singular matrix in routine ludcmp");
      vv[i] = 1.0/big;
    }
    for (j=0;j<n;j++)
    {
      big=0.0;
      for (i=0;i<j;i++)
      {
        sum = a[i][j];
        for (k=0;k<i;k++) sum -= a[i][k]*a[k][j];
        a[i][j] = sum;
      }
      for (i=j;i<n;i++)
      {
        sum = a[i][j];
        for (k=0;k<j;k++) sum -= a[i][k]*a[k][j];
        a[i][j]=sum;
        if ((dum=vv[i]*std::fabs(sum)) >= big) { big=dum; imax=i; }
      }
      if (j != imax)
      {
        for (k=0;k<n;k++) a.swap(imax,k,j,k);
        d = -d;
        vv[imax]=vv[j];
      }
      indx[j] = imax;
      if (a[j][j] == 0.0) a[j][j] = TINY;
      if (j != n-1)
      {
        dum=1.0/(a[j][j]);
        for (i=j+1;i<n;i++) a[i][j] *= dum;
      }
    }									// LU-decomp. finished, stored in a[][]

    for(int cols=0; cols<n; cols++)		// LU-back subst. begins
    {
      int ii=0, ip;
      vv = T(0.0); vv[cols] = T(1.0);
      for (i=0;i<n;i++)
      {
        ip = indx[i];
        T sum = vv[ip];
        vv[ip] = vv[i];
        if (ii != 0)		 for (j=ii-1;j<i;j++) sum -= a[i][j]*vv[j];
        else if (sum != 0.0) ii = i+1;
        vv[i] = sum;
      }
      for (i=n-1;i>=0;i--)
      {
        T sum=vv[i];
        for (j=i+1;j<n;j++)  sum -= a[i][j]*vv[j];
        vv[i]=sum/a[i][i];
      }
      setCol(vv,cols);		// inverse stored in this, a and vv is disappearing?
    }									// LU-back subst. finished,
  }


  /*! void SqMatrix<T, n>::invert2()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void SqMatrix<T, n>::invertOrthoNormal() {
    transpose();
  }	// Use only for orthonormal matrices (rotation matrices)


  /*! void SqMatrix<T, n>::rotateXY(Angle a, int x=0, int y=1)
   *  \brief Add a rotation to this matrix: (*this) = SqMatrix<T,n>(a,x,y)* (*this)
   *
   *  Add a rotation to this matrix: (*this) = SqMatrix<T,n>(a,x,y)* (*this)
   */
  template <typename T, int n>
  inline
  void SqMatrix<T, n>::rotateXY(Angle a, int x, int y) {
    GM_Static_<T,n>::rot_xy(this->getPtr()+x*n,this->getPtr()+y*n, T(sin(a.getRad())), T(cos(a.getRad())));
  }


  /*! void SqMatrix<T, n>::rotation(Angle a, const Vector<T,n>& u, const Vector<T,n>& v)
   *  \brief Add a rotation to this matrix: (*this) = SqMatrix<T,n>(a,u,v)* (*this)
   *
   *  Add a rotation to this matrix: (*this) = SqMatrix<T,n>(a,u,v)* (*this)
   */
  template <typename T, int n>
  inline
  void SqMatrix<T, n>::rotate(Angle a, const Vector<T,n>& u, const Vector<T,n>& v) {
    Matrix<T,n,n> x;
    makeOrtho(u,v,x);
    basisChangeInv(x);
    rotateXY(a);
    basisChange(x);
  }


  /*! void SqMatrix<T, n>::basisChange(const Matrix<T,n,n>& x)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void SqMatrix<T, n>::basisChange(const Matrix<T,n,n>& x)	{
    (*this) = transposeMult(x);
  }


  /*! void SqMatrix<T, n>::basisChangeInv(const Matrix<T,n,n>& x)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void SqMatrix<T, n>::basisChangeInv(const Matrix<T,n,n>& x)	{
    (*this) = x*(*this);
  }



  // **************************
  // Protected Member Functions


  /*! const Point<T,n>& SqMatrix<T, n>::getStatDiagonal(int i) const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  const Point<T,n>& SqMatrix<T, n>::getStatDiagonal(int i) const {

      GM_Static3_<T,n,n>::eq1( this->_c.getPtr(), this->getPtr() );
      return this->_c;
  }


  /*! void  SqMatrix<T, n>::cpy_d(const Point<T,n>& p)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void  SqMatrix<T, n>::cpy_d(const Point<T,n>& p) {

    GM_Static3_<T,n,n>::eq2( p.getPtr(), this->getPtr() );
  }


  /*! void SqMatrix<T, n>::makeOrtho(const Vector<T,n>& u, const Vector<T,n>& v, Matrix<T,n,n>& x)
   *  \brief To make an orthonormal set of basis-vectors
   *
   *  To make an orthonormal set of basis-vectors using
   *  vector u and vector v as a start.
   */
  template <typename T, int n>
  void SqMatrix<T, n>::makeOrtho(const Vector<T,n>& u, const Vector<T,n>& v, Matrix<T,n,n>& x) {
    int i,j,k,ku,kv;
    GM_Static_<T,n>::sc_r(x.getPtr(), u.getPtr(), (1/u.getLength()));
    GM_Std_<T,n>::ortoNormal(x[1].getPtr(), v.getPtr(), x.getPtr());
    ku = u.getMaxAbsIndex();
    kv = x[1].getMaxAbsIndex();

    for(k=0,i=2;i<n;i++,k++)
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
  }

}
