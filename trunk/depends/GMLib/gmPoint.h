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



/*! \file gmPoint.h
 *
 *  Interface classes for the Point/Vector/UnitVector/Arrow/ScalarPoint/Sphere/Box classes
 *
 *  \date   2008-06-17
 */

#ifndef __gmPOINT_H__
#define __gmPOINT_H__


// System Includes
#include <memory.h>

// GMlib includes
#include "gmStaticProc.h"
#include "gmAngle.h"
#include "gmStream.h"


namespace GMlib {


  template <typename T, int n>
  class Point;

  template <typename T, int n>
  class Vector;

  template <typename T, int n>
  class UnitVector;

  template <typename T, int n>
  class Arrow;

  template <typename T, int n>
  class ScalarPoint;

  template <typename T, int n>
  class Sphere;

  template <typename T, int n>
  class Box;

  template <typename T, int n, int m>
  class M_I_;






  /*! \class  Point gmPoint.h <gmPoint>
   *  \brief  The Static Point Class
   *
   *  A template Point, the Point is static i.e. the dimentions
   *  can not be change. The template type must be clean, i.e. is not allocating
   *  memory and without any virtual functions
   *
   *  The point is only using n values, but it is acting as it is in homogenious
   *  coordinates. The (n+1).nt element, which is not there, is actually implicite 1
   */
  template <typename T, int n>
  class Point {
  public:
    Point();
    Point( T t );
    Point( const T *t );
    Point( const Point<T, n> &p );

    Angle                 getAngle(Point<T,n> p) const;
    T                     getLength() const;
    int                   getMaxIndex() const;
    int                   getMaxAbsIndex() const;
    T*                    getPtr() const;
    void                  setTestType( int t, const Point<T,n>& p, const Vector<T,n>& v = T(0) );

    Point<T, n>&          operator =  ( const T t );
    Point<T, n>&          operator =  ( const T *t );
    Point<T, n>&          operator =  ( const Point<T, n> &p );
    Point<T, n>&          operator += ( const Point<T, n> &p );
    Point<T, n>&          operator -= ( const Point<T, n> &p );
    Point<T, n>&          operator -  () const;
    Point<T, n>&          operator +  ( const Point<T, n> &p ) const;
    Point<T, n>&          operator -  ( const Point<T, n> &p ) const;
    T                     operator *  ( const Point<T,n>& p) const;
    T&		                operator [] ( int i);
    T const&              operator () ( int i) const;

    // Scaling
    Point<T, n>&          operator *= ( double d );
    Point<T, n>           operator *  ( double d ) const;
    Point<T, n>&          operator %= ( const Point<T, n> &p );
    Point<T, n>&          operator %  ( const Point<T, n> &p ) const;

    // Scaling: inverse
    Point<T, n>&          operator /= ( double d );
    Point<T, n>          operator /  ( double d ) const;

    // Boolean on equality
    bool                  operator == ( const Point<T, n> &p ) const;
    bool                  operator != ( const Point<T, n> &pt ) const; // caling operator == ()

    // Boolean on sorting
    bool                  operator <  ( const Point<T, n> &v ) const;
    bool                  operator >  ( const Point<T, n> &v ) const;
    bool                  operator <= ( const Point<T, n> &v ) const;
    bool                  operator >= ( const Point<T, n> &v ) const;

    // Casting
    template <typename G, int m>
    operator Point<G,m>& () const;

    Point<float,n>&       toFloat() const;
    Point<double,n>       toDouble() const;



  protected:
    T                     _pt[n];

    void                  _cpy( const Point<T, n> &v );
    void                  _cpy( const T p[n] );
    void                  _cpy( const T &d );

  private:

    static Arrow<T, n>    *_arrow;    // Used for < and sorting see setTestType()
    static int			      _sortType;

  }; // END class Point











  /*! \var static Arrow<T, n> *Point<T, n>::_arrow
   * \brief  Used for < and sorting. See setTestType()
   */

  /*! \var static int _type; */

  /*! Point<T, n>& operator * ( double d, const Point<T, n> &p)
   *  \brief Multiply a double with a Point<T, n>
   *
   *  Multiply a double with a Point<T, n>.
   *  This function overloads the * operator of the double.
   *
   *  \param[in] d The double
   *  \param[in] p The Point<T,n>
   */
  template <typename T, int n>
  inline
  Point<T, n> operator * ( double d, const Point<T, n> &p ) {
    return p*d;
  }

  #ifdef GM_STREAM
    /*! T_Stream &operator << ( T_Stream &out, const Point<T, n> &p )
     *  \brief Stream output operator
     *
     *  Stream output operator, taking a Point<T,n> as a second parameter.
     *
     *  \param out The output stream
     *  \param p The Point<T, n>
     *  \return The output stream
     */
    template <typename T_Stream, typename T, int n>
    inline
    T_Stream& operator << ( T_Stream &out, const Point<T, n> &p ) {
      for(int i = 0; i < n; i++)
        out << p(i) << GMseparator::Element;
      return out;
    }


    /*! T_Stream& operator << ( T_Stream &out, const Point<T, n> *p )
     *  \brief Stream output operator
     *
     *  Stream output operator, taking a Point<T,n> pointer as a second parameter.
     *
     *  \param[in, out] out The output stream
     *  \param[in] p The Point<T, n> pointer
     *  \return The output stream
     */
    template <typename T_Stream, typename T, int n>
    inline
    T_Stream& operator << ( T_Stream &out, const Point<T, n> *p ) {
      for(int i=0;i<n;i++) out << (*p)(i) << GMseparator::Element;
      return out;
    }


    /*! T_Stream& operator >> ( T_Stream &in, Point<T, n> &p )
     *  \brief Stream input operator
     *
     *  Stream input operator, taking a Point<T,n> as a second parameter.
     *
     *  \param[in, out] in The input stream
     *  \param[in] p The Point<T, n>
     *  \return The input stream
     */
    template <typename T_Stream, typename T, int n>
    inline
    T_Stream& operator >> ( T_Stream &in, Point<T, n> &p ) {
      Separator es(GMseparator::Element);
      for(int i=0;i<n;i++) in >> p[i] >> es;
      return in;
    }

    /*! T_Stream& operator >> ( T_Stream &in, Point<T, n> *p )
     *  \brief Stream input operator
     *
     *  Stream input operator, taking a Point<T,n> pointer as a second parameter.
     *
     *  \param[in, out] in The input stream
     *  \param[in] p The Point<T, n> pointer
     *  \return The input stream
     */
    template <typename T_Stream, typename T, int n>
    inline
    T_Stream& operator >> ( T_Stream &in, Point<T, n> *p ) {
      Separator es(GMseparator::Element);
      for(int i=0;i<n;i++) in >> (*p)[i] >> es;
      return in;
    }
  #endif




  /*! \class Vector gmPoint.h <gmPoint>
   *  \brief The Static Vector Class
   *
   *	A template Vector, the Vector is static i.e. the dimentions
   *	can not be change. The template type must be clean, i.e. is not allocating
   *	memory and without any virtual functions.
   *
   *	The vector is only using n values, but it is acting as it is in homogenious
   *	coordinates. The (n+1).nt element, which is not there, is actually implicite 0.
   */
  template <typename T, int n>
  class Vector : public Point<T, n> {
  public:
    Vector();
    Vector( T t );
    Vector( const T *t );
    Vector( const Point<T,n> &p );

    Point<T,n>      getNormalized();
    Vector<T,n>     getLinIndVec() const;
    void            normalize();
    void            setLength( T length );


  }; // END class Vector










  // ************
  // Type Casting

  /*! Vector<T, n>&   toVector( Point<T,n> &p )
   *  \brief Casts a Point<T,n> to a Vector<T,n>
   *
   *  Casts a Point<T,n> to a Vector<T,n>
   *
   *  \param[in] p The Point to be casted to Vector
   *  \return The casted vector
   */
  template <typename T, int n>
  Vector<T, n>&   toVector( Point<T,n> &p ) {
    return *((Vector<T,n>*)(&p));
  }




  /*! \class UnitVector gmPoint.h <gmPoint>
   *  \brief The Static UnitVector class
   *
   *	A template UnitVector, the UnitVector is static i.e. the dimentions
   *	can not be change. The template type must be clean, i.e. is not allocating
   *	memory and without any virtual functions.
   *
   *	The UnitVector has, as the name indicate, always length 1. Be aware the you do not
   *	initiate it by a zero vector or by zero constant. In that case it will produce an overflow.
   *
   *	The unit vector is only using n values, but it is acting as it is in homogenious
   *	coordinates. The (n+1).nt element (there is not there) is actually implicite 0
   */
  template <typename T, int n>
  class UnitVector : public Vector<T,n> {
  public:
    UnitVector( T t = 1 );
    UnitVector( const T t[n]);
    UnitVector( const Point<T, n>& p);
    UnitVector( const UnitVector<T,n>& uv);

    Point<T, n>&    operator =  ( const T t );
    Point<T, n>&    operator =  ( const T t[n] );
    Point<T, n>&    operator =  ( const Point<T, n> &p );
    Point<T, n>&    operator =  ( const UnitVector<T, n>& uv );
    const T&        operator [] ( int i );
    Point<T, n>&    operator += ( const Point<T, n> &p );
    Point<T, n>&    operator -= ( const Point<T, n> &p );
    Point<T, n>&    operator %= ( const Point<T, n> &p );
    Point<T, n>&    operator *= ( const double d );
    Point<T, n>&    operator /= ( double d );

  }; // END class UnitVector


  #ifdef GM_STREAM
    /*! T_Stream& operator >> ( T_Stream& in, UnitVector<T, n>& v )
     *  \brief Brief description
     *
     *  Detailed Description
     */
    template <typename T_Stream, typename T, int n>
    inline
    T_Stream& operator >> ( T_Stream& in, UnitVector<T, n>& v ) {
      Point<T, n> p;
      in >> p;
      v = p;
      return in;
    }

    /*! T_Stream& operator >> (T_Stream& in, UnitVector<T,n>* v)
     *  \brief Brief description
     *
     *  Detailed Description
     */
    template <typename T_Stream, typename T, int n>
    inline
    T_Stream& operator >> (T_Stream& in, UnitVector<T,n>* v) {
      Point<T,n> p;
      in >> p;
      (*v) = p;
      return in;
    }
  #endif








  /*! \class Arrow gmPoint.h <gmPoint>
   *  \brief The Static Arrow class
   *
   *	A template Arrow, the Arrow is static i.e. the dimentions
   *	can not be change. The template type must be clean, i.e. is not allocating
   *	memory and without any virtual functions.
   *
   *	The Arrow is a Point and a conected Vector.
   */
  template <typename T, int n>
  class Arrow : public Point<T,n> {
  public:
    Arrow();
    Arrow(const Point<T,n> &p);
    Arrow(const Point<T,n> &p, const Vector<T,n> &v );
    Arrow(const Arrow<T,n> &a);

    const Vector<T, n>&   getDir() const;
    const Point<T, n>&    getPos() const;
    void                  setDir( const Vector<T, n> &v );
    void                  setPos( const Point<T, n> &p );

    Arrow<T,n>&           operator =  ( const Arrow<T, n> &a );
    Arrow<T,n>&           operator += ( const Point<T, n> &p );
    Arrow<T,n>&           operator -= ( const Point<T, n> &p );
    Arrow<T,n>            operator +  ( const Point<T, n> &p ) const;
    Arrow<T,n>            operator -  ( const Point<T, n> &p ) const;
    Arrow<T,n>&           operator += ( const Vector<T, n> &v );
    Arrow<T,n>&           operator -= ( const Vector<T, n> &v );
    Arrow<T,n>            operator +  ( const Vector<T, n> &v ) const;
    Arrow<T,n>            operator -  ( const Vector<T, n> &v ) const;
    Arrow<T,n>            operator -  () const;

    template <typename G, int m>
    operator Arrow<G, m>& () const;

    Arrow<float, n>&      toFloat() const;
    Arrow<double, n>&     toDouble() const;


  protected:
    Vector<T, n>          _dir;

  }; // END class Arrow



  // *****************************
  // IOSTREAM overloaded operators

  #ifdef GM_STREAM

  /*! T_Stream &operator<<(T_Stream &out, const Arrow<T,n> &a)
   *  \brief Brief description
   *
   *  Detailed Description
   */
  template <typename T_Stream,typename T, int n>
  T_Stream &operator << ( T_Stream &out, const Arrow<T,n> &a ) {

    out << a.getPos() << GMseparator::Element << a.getDir();
    return out;
  }


  /*! T_Stream& operator<<(T_Stream &out, const Arrow<T,n> *a)
   *  \brief Brief Description
   *
   *  Detailed Description
   */
  template <typename T_Stream,typename T, int n>
  T_Stream& operator << ( T_Stream &out, const Arrow<T,n> *a ) {

    out << a->getPos() << GMseparator::Element << a->getDir();
    return out;
  }


  /*! T_Stream& operator>>(T_Stream &in, Arrow<T,n> &a)
   *  \brief Brief Description
   *
   *  Detailed Description
   */
  template <typename T_Stream,typename T, int n>
  T_Stream& operator >> ( T_Stream &in, Arrow<T,n> &a ) {

    Separator es(GMseparator::Element);
    Point<T,n>  pt;
    Vector<T,n> dir;

    in >> pt >> es >> dir;
    a.setPos(pt);
    a.setDir(dir);

    return in;
  }


  /*! T_Stream& operator>>(T_Stream &in, Arrow<T,n> *a)
   *  \brief Brief Description
   *
   *  Detailed Description
   */
  template <typename T_Stream,typename T, int n>
  T_Stream& operator >> ( T_Stream &in, Arrow<T,n> *a ) {

    Separator es(GMseparator::Element);
    Point<T,n>  pt;
    Vector<T,n> dir;

    in >> pt >> es >> dir;
    a->setPos(pt);
    a->setDir(dir);

    return in;
  }

  #endif







  /*! \class ScalarPoint gmPoint.h <gmPoint>
   *  \brief The Static ScalarPoint class
   *	A template ScalarPoint, the ScalarPoint is static i.e. the dimentions
   *	can not be change. The template type must be clean, i.e. is not allocating
   *	memory and without any virtual functions.
   *
   *	The ScalarPoint is a Point and a conected scalar value.
   */
  template <typename T, int n>
  class ScalarPoint {
  public:
    ScalarPoint();
    ScalarPoint( const Point<T, n>& p, T v = T(0) );
    ScalarPoint( const ScalarPoint<T, n>& s );

    Point<T, n>	          getPos() const;
    T*                    getPtr() const;
    T			                getValue() const;
    void                  reset( const Point<T, n>& p , T v = T(0) );
    void                  reset();
    void                  resetValue( T t );
    void                  resetPos( const Point<T, n>& p );

    ScalarPoint<T, n>&    operator += ( const Point<T, n>& p );
    ScalarPoint<T, n>     operator +  ( const Point<T, n>& p ) const;
    ScalarPoint<T, n>&    operator += ( T p );
    ScalarPoint<T, n>     operator +  ( T p ) const;
    ScalarPoint<T, n>&    operator += ( const ScalarPoint<T, n>& p );
    ScalarPoint<T, n>     operator +  ( const ScalarPoint<T, n>& p ) const;
    ScalarPoint<T, n>&    operator *= ( double d );
    ScalarPoint<T, n>     operator *  ( double d ) const;

    ScalarPoint<T, n>&    operator /= ( double d );
    ScalarPoint<T, n>     operator /  ( double d ) const;

    ScalarPoint<T, n>&    operator %= ( const Point<T, n>& p );
    ScalarPoint<T, n>     operator %  ( const Point<T, n>& p ) const;
/*
    friend
    ScalarPoint<T, n>     operator *  ( double d, ScalarPoint<T, n> p ) { p*=d; return p; }
*/
  protected:
    Point<T, n>	          _pos;
    T			                _value;

  }; // END class ScalarPoint




  #ifdef GM_STREAM

    /*! T_Stream &operator<<(T_Stream& os, const ScalarPoint<T,n>& s)
     *  \brief Brief Description
     *
     *  Detailed Description
     */
    template <typename T_Stream, typename T, int n>
    inline
    T_Stream &operator<<(T_Stream& os, const ScalarPoint<T,n>& s) {
      os << s.getPos() << GMseparator::Element << s.getValue();
      return os;
    }

    /*! T_Stream &operator<<(T_Stream& os, const ScalarPoint<T,n>* s)
     *  \brief Brief Description
     *
     *  Detailed Description
     */
    template <typename T_Stream, typename T, int n>
    inline
    T_Stream &operator<<(T_Stream& os, const ScalarPoint<T,n>* s) {
      os << s->getPos() << GMseparator::Element << s->getValue();
      return os;
    }

    /*! T_Stream &operator>>(T_Stream& is, ScalarPoint<T,n>& s)
     *  \brief Brief Description
     *
     *  Detailed Description
     */
    template <typename T_Stream, typename T, int n>
    inline
    T_Stream &operator >> ( T_Stream& is, ScalarPoint<T, n>& s ) {
      Separator es(GMseparator::Element);
      Point<T,n> p1;
      T v;
      is >> p1 >> es >> v;
      s.reset(p1,v);
      return is;
    }

    /*! T_Stream &operator>>(T_Stream& is, ScalarPoint<T,n>* s)
     *  \brief Brief Description
     *
     *  Detailed Description
     */
    template <typename T_Stream, typename T, int n>
    inline
    T_Stream &operator>>(T_Stream& is, ScalarPoint<T,n>* s) {
      Separator es(GMseparator::Element);
      Point<T,n> p1;
      T v;
      is >> p1 >> es >> v;
      s->reset(p1,v);
      return is;
    }

  #endif






  /*! \class Sphere gmPoint.h <gmPoint>
   *  \brief The Static Sphere class
   *	A template Sphere, the Sphere is static i.e. the dimentions
   *	can not be change. The template type must be clean, i.e. is not allocating
   *	memory and without any virtual functions.
   *
   *	The Sphere is a centre Point and a conected scalar value, radius.
   *	It also inclue a boolean telling if the Sphere is valid or not.
   */
  template <typename T, int n>
  class Sphere : public ScalarPoint<T, n> {
  public:
    Sphere( bool sphere = false );
    Sphere( const Point<T, n>& p, T v = T(0) );
    Sphere( const ScalarPoint<T, n>& s );
    Sphere( const Sphere<T, n>& s );

    T	              getRadius() const;
    bool            isValid() const;
    bool            isIntersecting(const Sphere<T,n>& p) const;
    void            resetPos( const Point<T, n>& p );
    void            resetRadius( T t );
    void            reset();

    Sphere<T, n>&   operator += ( const Point<T, n>& p );
    Sphere<T, n>    operator +  ( const Point<T, n>& p ) const;
    Sphere<T, n>&   operator += ( const Sphere<T, n>& p );
    Sphere<T, n>    operator +  ( const Sphere<T, n>& p ) const;


  private:
    bool _valid;

  }; // END class Sphere










  #ifdef GM_STREAM

    /*! T_Stream &operator<<(T_Stream& os, const Sphere<T,n>& s)
     *  \brief Brief Description
     *
     *  Detailed Description
     */
    template <typename T_Stream, typename T, int n>
    inline
    T_Stream &operator<<(T_Stream& os, const Sphere<T,n>& s) {
      if(s.valid())
        os << ScalarPoint<T,n>::s;
      else
        os << ScalarPoint<T,n>(Point<T,n>(),T(-1));
      return os;
    }

    /*! T_Stream &operator<<(T_Stream& os, const Sphere<T,n>* s)
     *  \brief Brief Description
     *
     *  Detailed Description
     */
    template <typename T_Stream, typename T, int n>
    inline
    T_Stream &operator<<(T_Stream& os, const Sphere<T,n>* s) {
      if(s.isValid())
        os << reinterpret_cast< ScalarPoint<T,n> >( (*s) );
      else
        os << ScalarPoint<T,n>(Point<T,n>(),T(-1));

      return os;
    }

    /*! T_Stream &operator>>(T_Stream& is, Sphere<T,n>& s)
     *  \brief Brief Description
     *
     *  Detailed Description
     */
    template <typename T_Stream, typename T, int n>
    inline
    T_Stream &operator>>(T_Stream& is, Sphere<T,n>& s) {
      ScalarPoint<T,n> ss;
      is >> ss;
      if(ss.getValue()<0)
        s.reset();
      else
        s = Sphere<T,n>(ss);
      return is;
    }

    /*! T_Stream &operator>>(T_Stream& is, Sphere<T,n>* s)
     *  \brief Brief Description
     *
     *  Detailed Description
     */
    template <typename T_Stream, typename T, int n>
    inline
    T_Stream &operator>>(T_Stream& is, Sphere<T,n>* s) {
      ScalarPoint<T,n> ss;
      is >> ss;
      if(ss.getValue()<0)
        (*s).reset();
      else
        (*s) = Sphere<T,n>(ss);
      return is;
    }

  #endif








  /*! \class Box gmPoint.h <gmPoint>
   *  \brief The Static Box class
   *	A template Box, the Box is static i.e. the dimentions
   *	can not be change. The template type must be clean, i.e. is not allocating
   *	memory and without any virtual functions.
   *
   *	The Box is described by a minimum Point and a maximum Point (the diaginal).
   */
  template <typename T, int n>
  class Box {
  public:
    Box();
    Box( const Point<T, n>& p );
    Box( const Box<T, n>& b );
    Box( const Point<T, n>& p1, const Point<T, n>& p2 );
    Box( const Point<T, n>& p1, const Point<T, n>& p2, const Point<T,n>& p3 );

    Point<T, n>	    getPointMin() const;
    Point<T, n>	    getPointMax() const;
    Point<T, n>	    getPointCenter() const;
    Vector<T, n>    getPointDelta() const;
    T*              getPtr() const;

    T&		          getValueAt( int i, int j );
    T			          getValueMin( int i ) const;
    T			          getValueMax( int i ) const;
    T			          getValueCenter( int i ) const;
    T			          getValueDelta( int i ) const;
    void		        insert( const Point<T, n>& );
    void		        insert( const Box<T, n>& );
    bool		        isIntersecting( const Box<T,n>& b ) const;
    bool		        isSurrounding( const Point<T,n>& p ) const;
    bool		        isSurrounding( const Box<T,n>& b )  const;
    void		        reset();  // Default value for void reset( const Point<T, n>& p ); // got overload error
    void		        reset( const Point<T, n>& p );

    Box<T,n>&       operator += ( const Point<T, n>& p );
    Box<T,n>	      operator +  ( const Point<T, n>& p );
    Box<T,n>&	      operator += ( const Box<T, n>& b );
    Box<T,n>	      operator +  ( const Box<T, n>& b );



  private:
    Point<T, n>     _min;
    Point<T, n>     _max;

  }; // END class Box










  #ifdef GM_STREAM

    /*! T_Stream &operator<<(T_Stream& os, const Box<T,n>& b)
     *  \brief Brief Description
     *
     *  Detailed Description
     */
    template<typename T_Stream, typename T, int n>
    T_Stream &operator<<(T_Stream& os, const Box<T,n>& b) {
      os << b.getPointMin() << GMseparator::Element << b.getPointMax();
      return os;
    }

    /*! T_Stream &operator<<(T_Stream& os, const Box<T,n>* b)
     *  \brief Brief Description
     *
     *  Detailed Description
     */
    template<typename T_Stream, typename T, int n>
    T_Stream &operator<<(T_Stream& os, const Box<T,n>* b) {
      os << b->getPointMin() << GMseparator::Element << b->getPointMax();
      return os;
    }

    /*! T_Stream &operator>>(T_Stream& is, Box<T,n>& b)
     *  \brief Brief Description
     *
     *  Detailed Description
     */
    template<typename T_Stream, typename T, int n>
    T_Stream &operator>>(T_Stream& is, Box<T,n>& b) {
      Separator es(GMseparator::Element);
      Point<T,n> p1,p2;
      is >> p1 >> es >> p2;
      b.reset(p1);
      b.insert(p2);
      return is;
    }

    /*! T_Stream &operator>>(T_Stream& is, Box<T,n>* b)
     *  \brief Brief Description
     *
     *  Detailed Description
     */
    template<typename T_Stream, typename T, int n>
    T_Stream &operator>>(T_Stream& is, Box<T,n>* b) {
      Separator es(GMseparator::Element);
      Point<T,n> p1,p2;
      is >> p1 >> es >> p2;
      b->reset(p1);
      b->insert(p2);
      return is;
    }

  #endif





  //*********************************************************
  //********  The init of I-matrix and SubSpace  ************
  //************   NOT FOR EXTERNAL USE !!!!!!   ************
  //*********************************************************
  /*! \class M_I_ gmPoint.h <gmPoint>
   *  \brief The init of I-matrix and SubSpace
   *
   *	NOT FOR EXTERNAL USE !!!!!!
   */
  template <typename T, int n, int m>
  class M_I_ {
  public:
    M_I_();
    T* getPtr() const;

  private:
    T	_p[n*m];
  }; // END class M_I_

} // END namespace GMlib




// Include Point class implementations
#include "gmPoint_Point.c"

// Include Vector class implementations
#include "gmPoint_Vector.c"

// Include UnitVector class implementations
#include "gmPoint_UnitVector.c"

// Include Arrow class implementations
#include "gmPoint_Arrow.c"

// Include ScalarPoint class implementations
#include "gmPoint_ScalarPoint.c"

// Include Sphere class implementations
#include "gmPoint_Sphere.c"

// Include Box class implementations
#include "gmPoint_Box.c"

// Include M_I_ class implementations
#include "gmPoint_M_I_.c"







#endif // __gmPOINT_H__
