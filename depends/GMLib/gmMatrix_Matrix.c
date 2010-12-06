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



/*! \file gmMatrix_Matrix.c
 *
 *  File Description
 *
 *  \date   2008-07-09
 */

namespace GMlib {


  template <typename T, int n, int m>
  Vector<T,n>	Matrix<T,n,m>::_c;

  template <typename T, int n, int m>
  M_I_<T,n,m>	Matrix<T,n,m>::_I;


  /*! const Vector<T,n>& Matrix<T,n,m>::col(int j)const
   *  \brief  col
   *
   *  Detailed description of
   *  the function
   */
  template <typename T, int n, int m>
  inline
  const Vector<T,n>& Matrix<T,n,m>::getStatCol(int j)const {

    GM_Static2_<T,n,m>::eq1(_c.getPtr(),getPtr()+j); return _c;
  }


  /*! const Vector<T,m>& Matrix<T,n,m>::row(int i)const
   *  \brief  row
   *
   *  Detailed description of
   *  the function
   */
  template <typename T, int n, int m>
  inline
  const Vector<T,m>& Matrix<T,n,m>::getStatRow(int i)const {

    return (*this)(i);
  }


  /*! void Matrix<T,n,m>::cpy()
   *  \brief  cpy
   *
   *  Detailed description of
   *  the function
   */
  template <typename T, int n, int m>
  inline
  void Matrix<T,n,m>::cpy() {

    memcpy(getPtr(),_I.getPtr(),sizeof(Matrix<T,n,m>));
  }


  /*! void Matrix<T,n,m>::cpy(const T* v)
   *  \brief  cpy
   *
   *  Detailed description of
   *  the function
   */
  template <typename T, int n, int m>
  inline
  void Matrix<T,n,m>::cpy(const T* v) {

    memcpy(getPtr(), v, sizeof(Matrix<T,n,m>));
  }


  /*! void Matrix<T,n,m>::cpy(const Vector<Vector<T,m>,n>& v)
   *  \brief  cpy
   *
   *  Detailed description of
   *  the function
   */
  template <typename T, int n, int m>
  inline
  void Matrix<T,n,m>::cpy(const Vector<Vector<T,m>,n>& v)	{

    memcpy(getPtr(), v.getPtr(),sizeof(Matrix<T,n,m>));
  }


  /*! void Matrix<T,n,m>::cpy_t(const T* v)
   *  \brief  cpy
   *
   *  Detailed description of
   *  the function
   */
  template <typename T, int n, int m>
  inline
  void Matrix<T,n,m>::cpy_t(const T* v) {

    GM_Static_P_<T,n,m>::eq_t(getPtrP(),v);
  }


  /*! void Matrix<T,n,m>::cpy_t(const Vector<Vector<T,n>,m>& v)
   *  \brief  cpy
   *
   *  Detailed description of
   *  the function
   */
  template <typename T, int n, int m>
  inline
  void Matrix<T,n,m>::cpy_t(const Vector<Vector<T,n>,m>& v)	{

    GM_Static_P_<T,n,m>::eq_t( getPtrP(), (T*)v.getPtr() );
  }


  /*!void Matrix<T,n,m>::cpy_r(const Point<T,m>& p,int i)
   *  \brief  cpy
   *
   *  Detailed description of
   *  the function
   */
  template <typename T, int n, int m>
  inline
  void Matrix<T,n,m>::cpy_r(const Point<T,m>& p,int i) {

    (*this)[i] = p;
  }


  /*! void Matrix<T,n,m>::cpy_c(const Point<T,n>& p,int j)
   *  \brief  cpy
   *
   *  Detailed description of
   *  the function
   */
  template <typename T, int n, int m>
  inline
  void Matrix<T,n,m>::cpy_c(const Point<T,n>& p,int j) {

    GM_Static2_<T,n,m>::eq2(p.getPtr(),getPtr()+j);
  }



  /*! Matrix<T,n,m>::Matrix()
   *  \brief  Default Constructor
   *
   *  The constructer gives an I-matrix
   */
  template <typename T, int n, int m>
  inline
  Matrix<T,n,m>::Matrix() {

    cpy();
  }


  /*! Matrix<T,n,m>::Matrix(bool i)
   *  \brief  The fast constructor
   *
   *  The constructer gives random contents, there will be no initializing
   */
  template <typename T, int n, int m>
  inline
  Matrix<T,n,m>::Matrix(bool i)	{
  }


  /*! Matrix<T,n,m>::Matrix(const Point<T,m>& r,const Point<T,n>& c)
   *  \brief constructor
   *
   *  The tensor (outer) product constructor
   *  The constructer gives an tensor (outer) product of the two
   *  vectors that is the parameters
   */
  template <typename T, int n, int m>
  inline
  Matrix<T,n,m>::Matrix(const Point<T,m>& r,const Point<T,n>& c) {

    GM_Static_P_<T,n,m>::vv_ox(getPtrP(), &r, c.getPtr());
  }


  /*! Matrix<T,n,m>::Matrix(const Vector<T,m>& u)
   *  \brief constructor
   *
   *  A constructor generating an orthonormal set of rows
   *	The constructer gives an arbitary orthonormal set of rows
   *	constructed from one vector that is the parameter
   */
  template <typename T, int n, int m>
  inline
  Matrix<T,n,m>::Matrix(const Vector<T,m>& u) {

    setOrtho(u);
  }


  /*! Matrix<T,n,m>::Matrix(const Vector<T,m>& u)
   *  \brief constructor
   *
   *  A constructor generating an orthonormal set of rows
   *	The constructer gives an arbitary orthonormal set of rows
   *	constructed from two vectors that is the parameters
   */
  template <typename T, int n, int m>
  inline
  Matrix<T,n,m>::Matrix(const Vector<T,m>& u, const Vector<T,m>& v)	{

    setOrtho(u,v);
  }


  /*! Matrix<T,n,m>::Matrix(const Vector<T,m>& u)
   *  \brief The copy constructor
   *
   *  The constructer gives a copy of the input Vector<Vector> i.e. matrix
   */
  template <typename T, int n, int m>
  inline
  Matrix<T,n,m>::Matrix( const Vector<Vector<T,m>,n>& v )	{

    cpy(v);
  }


  /*! Matrix<T,n,m>::Matrix(const Vector<T,m>& u)
   *  \brief The transpose copy constructor
   *
   *  The constructer gives a transpoded copy of the input Vector<Vector>, i.e. matrix
   */
  template <typename T, int n, int m>
  inline
  Matrix<T,n,m>::Matrix(const Vector<Vector<T,n>,m>& v, bool trans)	{

    if(trans) cpy_t(v); else (n == m?cpy(v):cpy_t(v));
  }


  /*! Matrix<T,n,m>::Matrix(const Vector<T,m>& u)
   *  \brief The transpose constructor
   *
   *  The constructer gives a transpoded copy of the input classical vector, i.e. matrix
   */
  template <typename T, int n, int m>
  inline
  Matrix<T,n,m>::Matrix(const T* v, bool trans)	{

    if(trans) cpy_t(v); else cpy(v);
  }


  /*! void Matrix<T,n,m>::reset()
   *  \brief Reset to "I-matrix"
   *
   *  The matrix is not nessesarly a square matrix
   *	but the biggest possible square submatrix is set to an I-matrix
   */
  template <typename T, int n, int m>
  inline
  void Matrix<T,n,m>::reset() {

    cpy();
  }


  /*! T* Matrix<T,n,m>::getPtr() const
   *  \brief Gives a T* pointer
   *
   *  The matrix can be treated as a classic n*m-dim array of T
   */
  template <typename T, int n, int m>
  inline
  T* Matrix<T,n,m>::getPtr() const	{

    return (T*)this;
  }


  /*! Point<T,m>* Matrix<T,n,m>::getPtrP() const
   *  \brief Gives a Point<T,m>* pointer
   *
   *  The matrix can be treated as a classic n-dim of
   *  Point<T,n> *
   */
  template <typename T, int n, int m>
  inline
  Point<T,m>* Matrix<T,n,m>::getPtrP() const	{

    return (Point<T,m>*)this;
  }


  /*! Matrix<T,n,m>&	Matrix<T,n,m>::operator=(const Vector<Vector<T,m>,n>& m)
   *  \brief The operator = m
   *
   *  The operator =, i.e. it makes a copy of m. It also retur a referens to itself
   *  that is to use a=b=m.
   */
  template <typename T, int n, int m>
  inline
  Matrix<T,n,m>&	Matrix<T,n,m>::operator=(const Vector<Vector<T,m>,n>& mat)	{

    cpy(mat);   return(*this);
  }


  /*! Matrix<T,n,m>&	Matrix<T,n,m>::setTranspose(const Vector<Vector<T,m>,n>& m)
   *  \brief Set this matrix equal the transposed of matrix m
   *
   *  Set this matrix equal the transposed of matrix m
   *	Transpose this matrix. It also retur a referens to itself
   *	that is tu usa a=b=c.
   */
  template <typename T, int n, int m>
  inline
  Matrix<T,n,m>&	Matrix<T,n,m>::setTranspose(const Vector<Vector<T,m>,n>& mat) {

    cpy_t(mat); return(*this);
  }


  /*! Matrix<T,n,m>	Matrix<T,n,m>::transposed() const
   *  \brief Makes a transposed copy
   *
   *  It does not change itself.
   *  \return Returns a transposed copy
   */
  template <typename T, int n, int m>
  inline
  Matrix<T,m,n>	Matrix<T,n,m>::getTransposed() const	{

    return Matrix<T,m,n>(*this,true);
  }



  /*! void Matrix<T,n,m>::setCol(const Point<T,m>& c, int i)
   *  \brief  setCol
   *
   *  Put vector c at column number i
   *	Column number i is set equal to vector c, it makes a transposed copy.
   */
  template <typename T, int n, int m>
  inline
  void Matrix<T,n,m>::setCol(const Point<T,m>& c, int i) {

    cpy_c(c,i);
  }


  /*! void Matrix<T,n,m>::setRow(const Point<T,n>& r, int j)
   *  \brief  setRow
   *
   *  Put vector r at row number j
   *	Row number j is set equal to vector r, it makes a copy.
   */
  template <typename T, int n, int m>
  inline
  void Matrix<T,n,m>::setRow(const Point<T,n>& r, int j) {

    cpy_r(r,j);
  }



  /*! void Matrix<T,n,m>::initCol(int i, int j)
   *  \brief  initCol
   *
   *  Initiate column number i
   *	Column number i is initated to zero at all elements except for
   *	element number j that is set to 1.
   */
  template <typename T, int n, int m>
  inline
  void Matrix<T,n,m>::initCol(int i, int j)	{

    GM_Static2_<T,n,m>::eq3(this+i, _I+j);
  }




  /*! void Matrix<T,n,m>::initRow(int i, int j)
   *  \brief  initRow
   *
   *  Initiate row number i
   *	Row number i is initated to zero at all elements except for
   *	element number j that is set to 1.
   */
  template <typename T, int n, int m>
  inline
  void Matrix<T,n,m>::initRow(int i, int j)	{

    memcpy((*this)[i].getPtr(), _I.getPtr()+j*m, sizeof(Vector<T,m>));
  }



  /*! void Matrix<T,n,m>::initRow(int i, int j)
   *  \brief  getCol
   *
   *  Returns column number i
   *	Column number i is returned, but is set to a constant
   *	so it is not possible to change.
   */
  template <typename T, int n, int m>
  inline
  Point<T,n>const& Matrix<T,n,m>::getCol(int i) const	{

    return getStatCol(i);
  }



  /*! Point<T,m>const& Matrix<T,n,m>::getRow(int j) const
   *  \brief  getRow
   *
   *  Returns Row number j
   *	Row number j is returned, but is set to a constant
   *	so it is not possible to change.
   */
  template <typename T, int n, int m>
  inline
  Point<T,m>const& Matrix<T,n,m>::getRow(int j) const	{

    return getStatRow(j);
  }



  /*! void Matrix<T,n,m>::scale(const Point<T,n>& s)
   *  \brief  scale
   *
   *  Scaling the matrix row by row
   *  Row number i is scaled with s[i].
   */
  template <typename T, int n, int m>
  inline
  void Matrix<T,n,m>::scale(const Point<T,n>& s) {

    GM_Static_P_<T,n,m>::sc(getPtrP(),s.getPtr());
  }




  /*! Matrix<T,n,m>& Matrix<T,n,m>::operator+=(const Matrix<T,n,m>& m)
   *  \brief  scale
   *
   *  K = T += M
   *  This matrix (T) is updated by summing with matrix M, it is also
   *  possible to do: K = T += M, where K is another matrix,
   *  and which gives K = T and T = old T + M.
   */
  template <typename T, int n, int m>
  inline
  Matrix<T,n,m>& Matrix<T,n,m>::operator+=(const Matrix<T,n,m>& mat) {

    return reinterpret_cast<Matrix<T,n,m>&>(Vector<Vector<T,m>,n>::operator +=(mat));
  }





  /*! Matrix<T,n,m>& Matrix<T,n,m>::operator-=(const Matrix<T,n,m>& m)
   *  \brief  scale
   *
   *  K = T -= M
   *  This matrix (T) is updated by subtract with matrix M, it is also
   *	possible to do: K = T -= M, where K is another matrix,
   *	and which gives K = T and T = old T - M.
   */
  template <typename T, int n, int m>
  inline
  Matrix<T,n,m>& Matrix<T,n,m>::operator-=(const Matrix<T,n,m>& mat) {

    return reinterpret_cast<Matrix<T,n,m>&>(Vector<Vector<T,m>,n>::operator -=(mat));
  }



  /*! void Matrix<T,n,m>::scale(const Point<T,n>& s)
   *  \brief  scale
   *
   *  K = T + M
   *  Summing this matrix (T) and matrix M, this matrix is not changed. It is
   *  to do: K = T + M, where K is another matrix.
   */
  template <typename T, int n, int m>
  inline
  Matrix<T,n,m>& Matrix<T,n,m>::operator+(const Matrix<T,n,m>& mat) const	{

    return reinterpret_cast<Matrix<T,n,m>&>(Vector<Vector<T,m>,n>::operator +(mat));
  }



  /*! Matrix<T,n,m>& Matrix<T,n,m>::operator-(const Matrix<T,n,m>& m) const
   *  \brief  scale
   *
   *  K = T - M
   *	Subtract matrix M from this matrix (T), this matrix is not changed. It is
   *	to do: K = T - M, where K is another matrix.
   */
  template <typename T, int n, int m>
  inline
  Matrix<T,n,m>& Matrix<T,n,m>::operator-(const Matrix<T,n,m>& mat) const	{

    return reinterpret_cast<Matrix<T,n,m>&>(Vector<Vector<T,m>,n>::operator -(mat));
  }



  /*! Matrix<T,n,m>& Matrix<T,n,m>::operator-() const
   *  \brief  operator -
   *
   *  K = -T
   *	Returning this matrix (T) with changed sign. NB, this matrix is not changed. It is
   *	to do: K = -T, where K is another matrix.
   */
  template <typename T, int n, int m>
  inline
  Matrix<T,n,m>& Matrix<T,n,m>::operator-() const	{

    return reinterpret_cast<Matrix<T,n,m>&>(Vector<Vector<T,m>,n>::operator -());
  }



  /*! Point<T,n>&  Matrix<T,n,m>::operator*(const Point<T,m>& v) const
   *  \brief  operator *
   *
   *  p =  T * q
   *	Returning a point: p =  T * q, where p is a point in R^n and q is a point i R^m
   *	and T is this matrix.
   */
  template <typename T, int n, int m>
  inline
  Point<T,n>&  Matrix<T,n,m>::operator*(const Point<T,m>& v) const {

    GM_Static_P_<T,n,m>::mv_x(_c.getPtr(),getPtrP(),v); return _c;
  }



  /*! Matrix<T,n,m>& Matrix<T,n,m>::operator*=(const double d)
   *  \brief  operator *=
   *
   *  K = T *= d
   *	Scaling this matrix, T *= d. It is also returning a referens to itself
   *			so we can do the following: K = T *= d.
   */
  template <typename T, int n, int m>
  inline
  Matrix<T,n,m>& Matrix<T,n,m>::operator*=(const double d) {

    return reinterpret_cast<Matrix<T,n,m>&>(Vector<Vector<T,m>,n>::operator *=(d));
  }


  /*! Matrix<T,n,m>& Matrix<T,n,m>::operator*(const double d) const
   *  \brief  operator *
   *
   *	K = T * d
   *  Returns a scaled matrix, K = T * d. NB, this matrix (T) is not scaled.
   */
  template <typename T, int n, int m>
  inline
  Matrix<T,n,m>& Matrix<T,n,m>::operator*(const double d) const	{

    return reinterpret_cast<Matrix<T,n,m>&>(Vector<Vector<T,m>,n>::operator *(d));
  }



  /*! Matrix<T,n,m>& Matrix<T,n,m>::operator/=(double d)
   *  \brief  operator /=
   *
   *	T /= d is equal T *= 1/d
   *  Scaling this matrix, T /= d. It is also returning a referens to itself
   *  so we can do the following: K = T /= d.
   */
  template <typename T, int n, int m>
  inline
  Matrix<T,n,m>& Matrix<T,n,m>::operator/=(double d) {

    return reinterpret_cast<Matrix<T,n,m>&>(Vector<Vector<T,m>,n>::operator /=(d));
  }



  /*! Matrix<T,n,m>& Matrix<T,n,m>::operator/(double d) const
   *  \brief  operator /
   *
   *	K = T/d is equal to K = T * 1/d
   *  Returns a scaled matrix, K = T/d. NB, this matrix (T) is not scaled.
   */
  template <typename T, int n, int m>
  inline
  Matrix<T,n,m>& Matrix<T,n,m>::operator/(double d) const {

    return reinterpret_cast<Matrix<T,n,m>&>(Vector<Vector<T,m>,n>::operator /(d));
  }



  /*! void Matrix<T,n,m>::swap(int i,int j)
   *  \brief  swap
   *
   *	Exchange two elements in this matrix, m[i][j] is swapped with  m[j][i]
   *	m[i][j] is swapped with  m[j][i], that is a diagonal swap.
   */
  template <typename T, int n, int m>
  inline
  void Matrix<T,n,m>::swap(int i,int j)	{

    T tmp = (*this)[i][j]; (*this)[i][j] = (*this)[j][i]; (*this)[j][i] = tmp;
  }



  /*! void Matrix<T,n,m>::swap(int i,int j,int a,int b)
   *  \brief  swap
   *
   *	Exchange two elements in this matrix, m[i][j] is swapped with  m[a][b]
   *	m[i][j] is swapped with  m[a][b], that is a general swap.
   *  Also the previous diagonal swap(i,j) is equal to the general swap(i,j,j,i)
   */
  template <typename T, int n, int m>
  inline
  void Matrix<T,n,m>::swap(int i,int j,int a,int b)	{

    T tmp = (*this)[i][j]; (*this)[i][j] = (*this)[a][b]; (*this)[a][b] = tmp;
  }







  /*! Matrix<T,n,n> Matrix<T,n,m>::getMultTrans()
   *  \brief Matrix member multiplication: (*this) * (*this)T
   *
   *  Matrix member multiplication: (*this) * (*this)T
   *
   *  \return Matrix Multiplied with the transposed of itself
   */
  template <typename T, int n, int m>
  inline
  Matrix<T,n,n> Matrix<T,n,m>::getMultTrans() {

    Matrix<T,n,n> r;
    GM_Static_P2_<T,n,m,n>::mm_xT(r.getPtrP(),getPtrP(),getPtr());
    return r;
  }


  /*! Matrix<T,m,m> Matrix<T,n,m>::getTransMult()
   *  \brief Matrix member multiplication: (*this)T * (*this)
   *
   *  Matrix member multiplication: (*this)T * (*this)
   *
   *  \return The transposed matrix multiplied with itself
   */
  template <typename T, int n, int m>
  inline
  Matrix<T,m,m> Matrix<T,n,m>::getTransMult() {

    Matrix<T,m,m> r;
    GM_Static_P2_<T,m,n,m>::mm_xTT(r.getPtrP(),getPtr(),getPtr());
    return r;
  }


  /*! void Matrix<T,n,m>::setOrtho(const Vector<T,m>& u)
   *  \brief Set the matrix orthonormal using a Vector
   *
   *  Make an orthonormal set of basis-vectors using one vector u  as a start.
   *
   *  \param[in] u The start Vector
   */
  template <class T, int n, int m>
  void Matrix<T,n,m>::setOrtho(const Vector<T,m>& u) {

    int i, j, k, ku = u.getMaxAbsIndex();

    GM_Static_<T,m>::sc_r(getPtr(), u.getPtr(), (1/u.getLength()));

    for(k=0,i=1;i<n;i++,k++)
    {
      if(k==ku) k++;
      initRow(i, k);
    }

    for(i=1;i<n;i++)
    {
      for(j=0; j<i; j++)
      {
        T tmp = GM_Static_<T,m>::dpr((*this)[i].getPtr(),(*this)[j].getPtr());
        GM_Static_<T,m>::decomp((*this)[i].getPtr(),(*this)[j].getPtr(),tmp);
      }
      (*this)[i].normalize();
    }
  }


  /*! void Matrix<T,n,m>::makeMeOrtho(const Vector<T,m>& u, const Vector<T,m>& v)
   *  \brief Set the matrix orthonormal using two Vector
   *
   *  Make an orthonormal set of basis-vectors using two vectors u  and v as a start.
   *
   *  \param[in] u The first start Vector
   *  \param[in] v The second start Vector
   */
  template <class T, int n, int m>
  void Matrix<T,n,m>::setOrtho(const Vector<T,m>& u, const Vector<T,m>& v) {

    int i, j, k, ku, kv;

    GM_Static_<T,m>::sc_r(getPtr(), u.getPtr(), (1/u.getLength()));
    GM_Std_<T,m>::ortoNormal((*this)[1].getPtr(), v.getPtr(), getPtr());
    ku = (*this)[0].getMaxAbsIndex();
    kv = (*this)[1].getMaxAbsIndex();


    for(k=0,i=2;i<n;i++,k++)
    {
      if(k==ku) k++;
      if(k==kv)
      {
        k++;
        if(k==ku) k++;
      }
      initRow(i, k);
    }

    for(i=2;i<n;i++)
    {
      for(j=0; j<i; j++)
      {
        T tmp = GM_Static_<T,m>::dpr((*this)[i].getPtr(),(*this)[j].getPtr());
        GM_Static_<T,m>::decomp((*this)[i].getPtr(),(*this)[j].getPtr(),tmp);
      }
      (*this)[i].normalize();
    }
  }

}
