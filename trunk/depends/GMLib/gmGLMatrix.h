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



/*! \file gmGLMatrix.h
 *
 *  GLMatrix class definitions
 *  (previously located in <gmOpenGL.h>
 *
 *  \date   2010-04-14 (2008-08-03)
 */


#ifndef __GMGLMATRIX_H__
#define __GMGLMATRIX_H__

// local
#include "gmPoint.h"
#include "gmOpenGL.h"


namespace GMlib {


  /*! \var _I
   *  \brief The Identity Matrix
   *
   */
  static float _I[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};


  /*! \class GLMatrix
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  class GLMatrix {
  public:
    GLMatrix();
    GLMatrix(float* m);
    GLMatrix(const GLMatrix& m);
    GLMatrix(Angle a, const UnitVector<float,3>& r);
    GLMatrix(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d);
    GLMatrix(const Vector<float,3>& tr);

    void                basisChangeCam(
                          const Vector<float,3>& x,
                          const Vector<float,3>& y,
                          const Vector<float,3>& z,
                          const Vector<float,3>& p);

    void                basisChange(
                          const Vector<float,3>& x,
                          const Vector<float,3>& y,
                          const Vector<float,3>& z,
                          const Vector<float,3>& p);

    void                basisChangeInv(
                          const Vector<float,3>& x,
                          const Vector<float,3>& y,
                          const Vector<float,3>& z,
                          const Vector<float,3>& p);

    const float&        get(int i,int j) const;
    void                get(GLenum p);
    GLMatrix&           getInverse() const;
    GLMatrix&           getInverseOrtho() const;
    float*              getPtr() const;
    void                invert();
    void                invertOrtho();
    void                mult() const;
    GLMatrix&           multRev(const GLMatrix& m);
    void                put() const;
    void                reset();
    void                rotate( Angle a, const UnitVector<float,3>& d);
    void                rotate( Angle a, const Point<float,3>& p,const UnitVector<float,3>& d);
    void                rotateGlobal( Angle a, const Vector<float,3>& s);
    void                rotateGlobal( Angle a, const Point<float,3>& p,const UnitVector<float,3>& d);
    void                roundoff(int i=1000);
    void                scale( const Point<float,3>& s);
    void                scaleGlobal( const Point<float,3>& s);
    void                translate( const Point<float,3>& s);
    void                translateGlobal( const Point<float,3>& s);

    GLMatrix&           operator =  (float* m);
    GLMatrix&           operator =  (const GLMatrix& m);
    float&              operator () (int i,int j);
    GLMatrix&           operator *= (const GLMatrix& m);
    GLMatrix            operator *  (GLMatrix& m);
    Point<float,3>      operator *  (const Point<float,3>& p) const;
    Vector<float,3>     operator *  (const Vector<float,3>& p) const;
    Arrow<float,3>      operator *  (const Arrow<float,3>& b) const;
    Box<float,3>        operator *  (const Box<float,3>& b) const;
    Sphere<float,3>     operator *  (const Sphere<float,3>& b) const;
    bool                operator <  (const GLMatrix& m) const;


  private:
    float               _matrix[16];

    void                _cpy();
    void                _cpy( const float* m);
    void                _makeOrtho( const UnitVector<float,3>& d, Vector3D<float>& x, Vector3D<float>& y, Vector3D<float>& z);
    void                _mult( const GLMatrix& m1,const GLMatrix& m2);
    void                _mult2( GLMatrix& m1,const GLMatrix& m2) const;







  public:


    friend
    Point<float,3>& operator*=(Point<float,3>& p, const GLMatrix& m) {
      p = m*p;
      return p;
    }

    friend
    Vector<float,3>& operator*=(Vector<float,3>& p, const GLMatrix& m) {
      p = m*p;
      return p;
    }

    friend
    UnitVector<float,3>& operator*=(UnitVector<float,3>& p, const GLMatrix& m) {
      p = m * p;
      return p;
    }

    friend
    Arrow<float,3>& operator*=(Arrow<float,3>& p, const GLMatrix& m) {
      p = m*p; return p;
    }

    friend
    Box<float,3>& operator*=(Box<float,3>& p, const GLMatrix& m) {
      p = m*p; return p;
    }

    friend
    Sphere<float,3>& operator*=(Sphere<float,3>& p, const GLMatrix& m) {
      p = m*p; return p;
    }


    // *****************************
    // IOSTREAM overloaded operators

    #ifdef GM_STREAM

    template<class T_Stream>
    friend T_Stream& operator<<(T_Stream& out, const GLMatrix& mm) {

      float* m = mm.getPtr();
      out << m[0] << GMseparator::Element << m[4] << GMseparator::Element << m[8] << GMseparator::Element << m[12] << GMseparator::Group;
      out << m[1] << GMseparator::Element << m[5] << GMseparator::Element << m[9] << GMseparator::Element << m[13] << GMseparator::Group;
      out << m[2] << GMseparator::Element << m[6] << GMseparator::Element << m[10]<< GMseparator::Element << m[14] << GMseparator::Group;
      out << m[3] << GMseparator::Element << m[7] << GMseparator::Element << m[11]<< GMseparator::Element << m[15] << GMseparator::Group;
      return out;
    }


    template<class T_Stream>
    friend T_Stream& operator>>(T_Stream& in, GLMatrix& mm) {

      float* m = mm.getPtr();
      static Separator es(GMseparator::Element);
      static Separator gs(GMseparator::Group);

      in >> m[0] >> es >> m[4] >> es >> m[8] >> es >> m[12] >> gs;
      in >> m[1] >> es >> m[5] >> es >> m[9] >> es >> m[13] >> gs;
      in >> m[2] >> es >> m[6] >> es >> m[10]>> es >> m[14] >> gs;
      in >> m[3] >> es >> m[7] >> es >> m[11]>> es >> m[15] >> gs;
      return in;
    }


  private:
    istream& _printIn( istream& in );
    ostream& _printOut( ostream& out ) const;


  public:
    friend
    ostream& operator << ( ostream& out, const GLMatrix& v ) {

      return v._printOut( out );
    }

    friend
    ostream& operator << ( ostream& out, const GLMatrix* v ) {

      return v->_printOut( out );
    }

    friend
    istream& operator >> ( istream& in, GLMatrix& v ) {

      return v._printIn (in );
    }

    friend
    istream& operator >> ( istream& in, GLMatrix* v ) {

      return v->_printIn( in );
    }

    void print( char prompt[] = "GLMatrix", ostream & out = std::cout ) const;

    #endif

  }; // END class GLMatrix

} // END namespace GMlib

// Include inline GLMatrix implementations
#include "gmGLMatrix.c"


#endif // __GMGLMATRIX_H__
