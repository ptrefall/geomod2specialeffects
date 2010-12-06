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



/*! \file gmGLMatrix.c
 *  \brief Inline GLMatrix class implementations
 *
 *  Inline implementation of the GLMatrix class.
 *  (previously located in: <gmOpenGL_GLMatrix.c>)
 *
 *  \date   2010-04-14 (2008-08-03)
 */



namespace GMlib {



  /*! GLMatrix::GLMatrix()
   *  \brief Pending Documentation
   *
   *  Default constructor
   */
  inline
  GLMatrix::GLMatrix() {
    _cpy();
  }


  /*! GLMatrix::GLMatrix( float* m )
   *  \brief Pending Documentation
   *
   *  Standard constructor
   */
  inline
  GLMatrix::GLMatrix( float* m ) {
    if(m)	_cpy(m);
    else	_cpy();
  }


  /*! GLMatrix::GLMatrix(const GL_Matrix& m)
   *  \brief Pending Documentation
   *
   *  Copy constructor
   */
  inline
  GLMatrix::GLMatrix( const GLMatrix& m ) {
    _cpy( m.getPtr() );
  }


  /*! GLMatrix::GLMatrix(Angle a, const UnitVector<float,3>& r)
   *  \brief Pending Documentation
   *
   *  Rotation constructor 1
   */
  inline
  GLMatrix::GLMatrix( Angle a, const UnitVector<float,3>& r ) {

    Vector3D<float> x,y,z,kx,ky,kz;
    float sina = (float)sin(a.getRad()), cosa=(float)cos(a.getRad());
    _makeOrtho(r,x,y,z);

    kx[0] = x(0);	kx[1] = x(1)*cosa-x(2)*sina;	kx[2] = x(1)*sina+x(2)*cosa;
    ky[0] = y(0);	ky[1] = y(1)*cosa-y(2)*sina;	ky[2] = y(1)*sina+y(2)*cosa;
    kz[0] = z(0);	kz[1] = z(1)*cosa-z(2)*sina;	kz[2] = z(1)*sina+z(2)*cosa;

    _matrix[0] = x*kx;	_matrix[4] = x*ky;	_matrix[8] = x*kz;	_matrix[12] = 0.0;
    _matrix[1] = y*kx;	_matrix[5] = y*ky;	_matrix[9] = y*kz;	_matrix[13] = 0.0;
    _matrix[2] = z*kx;	_matrix[6] = z*ky;	_matrix[10]= z*kz;	_matrix[14] = 0.0;
    _matrix[3] = 0.0;	  _matrix[7] = 0.0;	  _matrix[11]= 0.0;	  _matrix[15] = 1.0;
  }


  /*! GLMatrix::GLMatrix(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d)
   *  \brief Pending Documentation
   *
   *  Rotation constructor 2
   */
  inline
  GLMatrix::GLMatrix(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d) {

    Vector3D<float> x,y,z,kx,ky,kz,r;
    float sina = (float)sin(a.getRad()), cosa=(float)cos(a.getRad());
    _makeOrtho(d,x,y,z);
    float sp = x(1)*p(0)+y(1)*p(1)+z(1)*p(2), up = x(2)*p(0)+y(2)*p(1)+z(2)*p(2);

    kx[0] = x(0);	kx[1] = x(1)*cosa-x(2)*sina;	kx[2] = x(1)*sina+x(2)*cosa;
    ky[0] = y(0);	ky[1] = y(1)*cosa-y(2)*sina;	ky[2] = y(1)*sina+y(2)*cosa;
    kz[0] = z(0);	kz[1] = z(1)*cosa-z(2)*sina;	kz[2] = z(1)*sina+z(2)*cosa;
    r[0]  = d*p;	r[1]  = sp*cosa-up*sina;		r[2]  = sp*sina+up*cosa;

    _matrix[0] = x*kx;	_matrix[4] = x*ky;	_matrix[8] = x*kz;	_matrix[12] = p(0)-x*r;
    _matrix[1] = y*kx;	_matrix[5] = y*ky;	_matrix[9] = y*kz;	_matrix[13] = p(1)-y*r;
    _matrix[2] = z*kx;	_matrix[6] = z*ky;	_matrix[10]= z*kz;	_matrix[14] = p(2)-z*r;
    _matrix[3] = 0.0; 	_matrix[7] = 0.0;	  _matrix[11]= 0.0;	  _matrix[15] = 1.0;
  }


  /*! GLMatrix::GLMatrix(const Vector<float,3>& tr)
   *  \brief Pending Documentation
   *
   *  Translate constructor
   */
  inline
  GLMatrix::GLMatrix(const Vector<float,3>& tr) {

    _cpy();
    memcpy((_matrix+12), tr.getPtr(), 12);

    //matrix[12] = s(0);	matrix[13] = s(1);	matrix[14] = s(2); }
  }


  /*! void GLMatrix::basisChangeCam(const Vector<float,3>& x, const Vector<float,3>& y, const Vector<float,3>& z, const Vector<float,3>& p)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void GLMatrix::basisChangeCam(const Vector<float,3>& x, const Vector<float,3>& y,
    const Vector<float,3>& z, const Vector<float,3>& p) {

    _matrix[0] = -x(0);	_matrix[4] = -x(1);	_matrix[8] = -x(2);	_matrix[12] =  x*p;
    _matrix[1] =  y(0);	_matrix[5] =  y(1);	_matrix[9] =  y(2);	_matrix[13] =-(y*p);
    _matrix[2] = -z(0);	_matrix[6] = -z(1);	_matrix[10]= -z(2);	_matrix[14] =  z*p;
    _matrix[3] =   0.0;	_matrix[7] =   0.0;	_matrix[11]=   0.0;	_matrix[15] =  1.0;
  }


  /*! void GLMatrix::basisChange(const Vector<float,3>& x, const Vector<float,3>& y, const Vector<float,3>& z, const Vector<float,3>& p)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void GLMatrix::basisChange(const Vector<float,3>& x, const Vector<float,3>& y,
    const Vector<float,3>& z, const Vector<float,3>& p) {

    memcpy(_matrix,x.getPtr(),12);
    memcpy(_matrix+4,y.getPtr(),12);
    memcpy(_matrix+8,z.getPtr(),12);
    memcpy(_matrix+12,p.getPtr(),12);

    _matrix[3] =  0.0;	_matrix[7] =  0.0;	_matrix[11]=  0.0;	_matrix[15] =  1.0;
  }


  /*! void GLMatrix::basisChangeInv(const Vector<float,3>& x, const Vector<float,3>& y, const Vector<float,3>& z, const Vector<float,3>& p)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void GLMatrix::basisChangeInv(const Vector<float,3>& x, const Vector<float,3>& y,
    const Vector<float,3>& z, const Vector<float,3>& p) {

    _matrix[0] = x(0);	_matrix[4] = x(1);	_matrix[8] = x(2);	_matrix[12] = -(x*p);
    _matrix[1] = y(0);	_matrix[5] = y(1);	_matrix[9] = y(2);	_matrix[13] = -(y*p);
    _matrix[2] = z(0);	_matrix[6] = z(1);	_matrix[10]= z(2);	_matrix[14] = -(z*p);
    _matrix[3] =  0.0;	_matrix[7] =  0.0;	_matrix[11]=  0.0;	_matrix[15] =    1.0;
  }


  /*! const float&  GLMatrix::get(int i,int j) const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  const float&  GLMatrix::get(int i,int j) const {

    return _matrix[(i<<2)+j];
  }


  /*! void GLMatrix::get( GLenum p )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void GLMatrix::get( GLenum p ) {

    glGetFloatv( p, _matrix );
  }


  /*! GLMatrix& GLMatrix::getInverse() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  GLMatrix& GLMatrix::getInverse() const {

    static GLMatrix m;
    m = *this;
    m.invert();
    return m;
  }


  /*! GLMatrix& GLMatrix::getInverseOrtho()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  GLMatrix& GLMatrix::getInverseOrtho() const {

    static GLMatrix m;
    m = *this;
    m.invertOrtho();
    return m;
  }


  /*! float* GLMatrix::getPtr() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  float* GLMatrix::getPtr() const {

    return (float*)(_matrix);
  }


  /*! void GLMatrix::invert()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void GLMatrix::invert() {

    double m[16];
    double a[16];
    int i;
    for (i=0;i<16;i++) m[i] = (double)_matrix[i];
    m[1]  /= m[0];		m[2] /= m[0];		m[3] /= m[0];		a[0] = 1.0/m[0];
    m[5]  -= m[4]*m[1]; m[6]  -= m[4]*m[2]; m[7]  -= m[4]*m[3]; a[4] = -m[4]*a[0];
    m[6]  /= m[5];		m[7] /= m[5];		a[4] /= m[5];		a[5] = 1.0/m[5];
    m[9]  -= m[8]*m[1]; m[10] -= m[8]*m[2]; m[11] -= m[8]*m[3]; a[8] = -m[8]*a[0];
    m[10] -= m[9]*m[6]; m[11] -= m[9]*m[7]; a[8]  -= m[9]*a[4]; a[9] = -m[9]*a[5];
    m[11] /= m[10];		a[8] /= m[10];		a[9] /= m[10];		a[10] = 1.0/m[10];
    m[13] -= m[12]*m[1];m[14] -= m[12]*m[2];m[15] -= m[12]*m[3];a[12] = -m[12]*a[0];
    m[14] -= m[13]*m[6];m[15] -= m[13]*m[7];a[12] -= m[13]*a[4];a[13] = -m[13]*a[5];
    m[15] -=m[14]*m[11];a[12] -= m[14]*a[8];a[13] -= m[14]*a[9];a[14] = -m[14]*a[10];
    a[12] /= m[15];		a[13] /= m[15];		a[14] /= m[15];		a[15] = 1.0/m[15];
    a[8] -= m[11]*a[12];a[9] -= m[11]*a[13];a[10]-= m[11]*a[14];a[11]= -m[11]*a[15];
    a[4] -= m[7] *a[12];a[5] -= m[7] *a[13];a[6] = -m[7]*a[14]; a[7] = -m[7]*a[15];
    a[0] -= m[3] *a[12];a[1] = -m[3] *a[13];a[2] = -m[3]*a[14]; a[3] = -m[3]*a[15];
    a[4] -= m[6] *a[8]; a[5] -= m[6] *a[9]; a[6] -= m[6]*a[10]; a[7] -= m[6]*a[11];
    a[0] -= m[2] *a[8]; a[1] -= m[2] *a[9]; a[2] -= m[2]*a[10]; a[3] -= m[2]*a[11];
    a[0] -= m[1] *a[4]; a[1] -= m[1] *a[5]; a[2] -= m[1]*a[6];	a[3] -= m[1]*a[7];
    for (i=0;i<16;i++) _matrix[i] = (float)a[i];
  }


  /*! void GLMatrix::invertOrtho()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void GLMatrix::invertOrtho() {

    float m12 = _matrix[12];
    float m13 = _matrix[13];
    float m14 = _matrix[14];
    std::swap( _matrix[1], _matrix[4] );
    std::swap( _matrix[2], _matrix[8] );
    std::swap( _matrix[6], _matrix[9] );
    _matrix[12] =  -_matrix[0]*m12 - _matrix[4]*m13 - _matrix[8]*m14;
    _matrix[13] =  -_matrix[1]*m12 - _matrix[5]*m13 - _matrix[9]*m14;
    _matrix[14] =  -_matrix[2]*m12 - _matrix[6]*m13 - _matrix[10]*m14;
  }


  /*! void GLMatrix::mult() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void GLMatrix::mult() const {

    glMultMatrixf(_matrix);
  }


  /*! GLMatrix& GLMatrix::multRev(const GLMatrix& m)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  GLMatrix& GLMatrix::multRev(const GLMatrix& m) {

    GLMatrix mat= *this;
    _mult(mat,m);
    return *this;
  }


  /*! void GLMatrix::put() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void GLMatrix::put() const {

    glLoadMatrixf(_matrix);
  }


  /*! void GLMatrix::reset()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void GLMatrix::reset() {

    _cpy();
  }


  /*! void GLMatrix::rotate(Angle a, const UnitVector<float,3>& d)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void GLMatrix::rotate(Angle a, const UnitVector<float,3>& d) {

    GLMatrix m(a,d);
    (*this) *= m;
  }


  /*! void GLMatrix::rotate(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void GLMatrix::rotate(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d) {

    GLMatrix m(a,p,d);
    (*this) *= m;
  }


  /*! void GLMatrix::rotateGlobal(Angle a, const Vector<float,3>& s)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void GLMatrix::rotateGlobal(Angle a, const Vector<float,3>& s) {

    GLMatrix m(a,s);
    multRev(m);
  }


  /*! void GLMatrix::rotateGlobal(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void GLMatrix::rotateGlobal(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d) {

    GLMatrix m(a,p,d);
    multRev(m);
  }


  /*! void GLMatrix::roundoff(int i=1000)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void GLMatrix::roundoff(int i) {

    _matrix[0]+=i;   _matrix[0]-=i;
    _matrix[1]+=i;   _matrix[1]-=i;
    _matrix[2]+=i;   _matrix[2]-=i;
    _matrix[3]+=i;   _matrix[3]-=i;
    _matrix[4]+=i;   _matrix[4]-=i;
    _matrix[5]+=i;   _matrix[5]-=i;
    _matrix[6]+=i;   _matrix[6]-=i;
    _matrix[7]+=i;   _matrix[7]-=i;
    _matrix[8]+=i;   _matrix[8]-=i;
    _matrix[9]+=i;   _matrix[9]-=i;
    _matrix[10]+=i;  _matrix[10]-=i;
    _matrix[11]+=i;  _matrix[11]-=i;
    _matrix[12]+=i;  _matrix[12]-=i;
    _matrix[13]+=i;  _matrix[13]-=i;
    _matrix[14]+=i;  _matrix[14]-=i;
    _matrix[15]+=i;  _matrix[15]-=i;
  }


  /*! void GLMatrix::scale(const Point<float,3>& s)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void GLMatrix::scale(const Point<float,3>& s) {

    GLMatrix m;
    m._matrix[0] = s(0);	m._matrix[5] = s(1);	m._matrix[10] = s(2);
    (*this) *= m;
  }


  /*! void GLMatrix::scaleGlobal(const Point<float,3>& s)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void GLMatrix::scaleGlobal(const Point<float,3>& s) {

    GLMatrix m;
    m._matrix[0] = s(0);	m._matrix[5] = s(1);	m._matrix[10] = s(2);
    multRev(m);
  }


  /*! void GLMatrix::translate(const Point<float,3>& s)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void GLMatrix::translate(const Point<float,3>& s) {

    GLMatrix m(s);
    (*this) *= m;
  }


  /*! void GLMatrix::translateGlobal(const Point<float,3>& s)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void GLMatrix::translateGlobal(const Point<float,3>& s) {

    GLMatrix m(s);
    multRev(m);
  }


  /*! GLMatrix::GLMatrix& operator=( float* m )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  GLMatrix& GLMatrix::operator=( float* m ) {
    _cpy(m); return *this;
  }


  /*! GLMatrix::GLMatrix& operator=(const GLMatrix& m)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  GLMatrix& GLMatrix::operator=(const GLMatrix& m) {
    _cpy(m.getPtr()); return *this;
  }


  /*! float&  GLMatrix::operator()(int i,int j)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  float& GLMatrix::operator()(int i,int j) {

    return _matrix[(i<<2)+j];
  }


  /*! GLMatrix& GLMatrix::operator *= (const GLMatrix& m )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  GLMatrix& GLMatrix::operator *= (const GLMatrix& m ) {

    GLMatrix mat= *this;
    _mult(m,mat);
    return *this;
  }


  /*! GLMatrix GLMatrix::operator *(GLMatrix& m)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  GLMatrix GLMatrix::operator *(GLMatrix& m) {

    GLMatrix mat;
    mat._mult(m,*this);
    return mat;
  }


  /*! bool GLMatrix::operator < ( const GLMatrix& m ) const
   *  \brief Pending Documentation
   *
   *  DUMMY
   */
  inline
  bool GLMatrix::operator < ( const GLMatrix& /*matrix*/ ) const {
    return true;
  }


  /*! void GLMatrix::_cpy()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void GLMatrix::_cpy() {

    //for (i=0; i<16; i++) matrix[i] = _I[i];
    memcpy(_matrix,_I,64);
  }


  /*! void GLMatrix::_cpy(const float* m)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void GLMatrix::_cpy(const float* m) {

    //for (i=0; i<16; i++) matrix[i] = m[i];
    memcpy(_matrix,m,64);
  }


  /*! void GLMatrix::_makeOrtho(const UnitVector<float,3>& d, Vector3D<float>& x, Vector3D<float>& y, Vector3D<float>& z)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void GLMatrix::_makeOrtho(const UnitVector<float,3>& d, Vector3D<float>& x, Vector3D<float>& y, Vector3D<float>& z) {

    double d0=std::fabs(d(0)),d1=std::fabs(d(1)),d2=std::fabs(d(2));
    if (d0 > d1)
    {
      if(d2 > d1)		// d(1) er minst
      { z[0] = d(2); z[2] = -d(0); z[1] = 0.0f; }
      else			// d(2) er minst
      { z[0] = d(1); z[1] = -d(0); z[2] = 0.0f; }
    }
    else // d(1) > d(0)
    {
      if(d2 > d0)		// d(0) er minst
      { z[1] = d(2); z[2] = -d(1); z[0] = 0.0f; }
      else			// d(2) er minst
      { z[0] = d(1); z[1] = -d(0); z[2] = 0.0f; }
    }
    z/=z.getLength();
    y = z^d;
    x[0] = d(0); x[1] = y(0); x[2] = z(0);
    y[0] = d(1); z[0] = d(2);
    std::swap(z[1],y[2]);
  }


  /*! void GLMatrix::_mult(const GLMatrix& m1,const GLMatrix& m2)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void GLMatrix::_mult(const GLMatrix& m1,const GLMatrix& m2) {
    int i,j,k;
    for(i=0;i<4;i++)
      for(j=0;j<4;j++)
        for((*this)(i,j)=0,k=0;k<4;k++)
          (*this)(i,j) += m1.get(i,k)*m2.get(k,j);
  }


  /*! void GLMatrix::_mult2(GLMatrix& m1,const GLMatrix& m2)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void GLMatrix::_mult2(GLMatrix& m1,const GLMatrix& m2) const {
    int i,j,k;
    for(i=0;i<4;i++)
      for(j=0;j<4;j++)
        for(m1(i,j)=0,k=0;k<4;k++)
          m1(i,j) += this->get(i,k)*m2.get(k,j);
  }


  // *****************************
  // IOSTREAM overloaded operators

  #ifdef GM_STREAM

  inline
  istream& GLMatrix::_printIn( istream& in ) {

    in >> _matrix[0] >> _matrix[4] >> _matrix[8] >> _matrix[12]
       >> _matrix[1] >> _matrix[5] >> _matrix[9] >> _matrix[13]
       >> _matrix[2] >> _matrix[6] >> _matrix[10]>> _matrix[14]
       >> _matrix[3] >> _matrix[7] >> _matrix[11]>> _matrix[15];
    return in;
  }


  inline
  ostream& GLMatrix::_printOut( ostream& out ) const {

    out << _matrix[0] << "  " << _matrix[4] << "  " << _matrix[8] << "  " << _matrix[12] << "\n";
    out << _matrix[1] << "  " << _matrix[5] << "  " << _matrix[9] << "  " << _matrix[13] << "\n";
    out << _matrix[2] << "  " << _matrix[6] << "  " << _matrix[10]<< "  " << _matrix[14] << "\n";
    out << _matrix[3] << "  " << _matrix[7] << "  " << _matrix[11]<< "  " << _matrix[15] << "\n";
    return out;
  }


  inline
  void GLMatrix::print( char prompt[], ostream & out ) const {

    out << prompt << ": " << (*this) << "\n";
  }

  #endif


} // END namespace GMlib
