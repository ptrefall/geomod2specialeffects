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



/*! \file gmAngle.h
 *
 *  Interface for the Angle class.
 *
 *  \date   2008-06-17
 */

#ifndef __gmANGLE_H__
#define __gmANGLE_H__


// System includes
#include <cmath>


namespace GMlib {


/*! \def  POS_TOLERANCE
 *  Tolerance of the position : 1e-6
 */
#ifndef POS_TOLERANCE
#define POS_TOLERANCE     1e-6
#endif


/*! \def  ANGLE_TOERLANCE
 *  Tolerance of the angle : 1e-3
 */
#ifndef ANGLE_TOLERANCE
#define ANGLE_TOLERANCE		1e-3
#endif


/*! \def  M_E
 *  Value of the exponent : 2.71828182845904523536
 */
#ifndef M_E
#define M_E               2.71828182845904523536
#endif


/*! \def  M_LOG2E
 *  Binary logarithm of the exponent : 1.44269504088896340736
 */
#ifndef M_LOG2E
#define M_LOG2E           1.44269504088896340736
#endif


/*! \def  M_LOG10E
 *  Decimal logarithm of the exponent : 0.434294481903251827651
 */
#ifndef M_LOG10E
#define M_LOG10E          0.434294481903251827651
#endif


/*! \def  M_LN2
 *  : 0.693147180559945309417
 */
#ifndef M_LN2
#define M_LN2             0.693147180559945309417
#endif


/*! \def  M_LN10
 *  : 2.30258509299404568402
 */
#ifndef M_LN10
#define M_LN10            2.30258509299404568402
#endif


/*! \def  M_PI
 *  Value of Pi : 3.14159265358979323846
 */
#ifndef M_PI
#define M_PI              3.14159265358979323846
#endif


/*! \def  M_2PI
 *  Value of 2Pi : 6.28318530717958647692
 */
#ifndef M_2PI
#define M_2PI             6.28318530717958647692
#endif


/*! \def  M_2PI_3
 *  Value of 2Pi / 3 : 2.094395102393195492308
 */
#ifndef M_2PI_3
#define M_2PI_3           2.094395102393195492308
#endif


/*! \def  M_PI_2
 *  Value of Pi / 2 : 1.57079632679489661923
 */
#ifndef M_PI_2
#define M_PI_2            1.57079632679489661923
#endif


/*! \def  M_PI_4
 *  Value of Pi / 4 : 0.785398163397448309616
 */
#ifndef M_PI_4
#define M_PI_4            0.785398163397448309616
#endif


/*! \def  M_PI_180
 *  Value of Pi / 180 : 0.0174532925199432957692
 */
#ifndef M_PI_180
#define M_PI_180	        0.0174532925199432957692
#endif


/*! \def  M_1_PI
 *  Value of 1 / Pi : 0.318309886183790671538
 */
#ifndef M_1_PI
#define M_1_PI            0.318309886183790671538
#endif


/*! \def  M_2_PI
 *  Value of 2 / Pi : 0.636619772367581343076
 */
#ifndef M_2_PI
#define M_2_PI            0.636619772367581343076
#endif


/*! \def  M_180_PI
 *  Value of 180 / Pi : 57.29577951308232087679
 */
#ifndef M_180_PI
#define M_180_PI	        57.29577951308232087679
#endif


/*! \def  M_1_SQRTPI
 *  Value of 1 / Squart(Pi) : 0.564189583547756286948
 */
#ifndef M_1_SQRTPI
#define M_1_SQRTPI        0.564189583547756286948
#endif


/*! \def  M_2_SQRTPI
 *  Value of 2 / Suqart(Pi) : 1.12837916709551257390
 */
#ifndef M_2_SQRTPI
#define M_2_SQRTPI        1.12837916709551257390
#endif


/*! \def  M_SQRT2
 *  Value of Squart(2) : 1.41421356237309504880
 */
#ifndef M_SQRT2
#define M_SQRT2           1.41421356237309504880
#endif


/*! \def  M_SQRT1_2
 *  Value of Squart(1/2) : 0.707106781186547524401
 */
#ifndef M_SQRT1_2
#define M_SQRT1_2         0.707106781186547524401
#endif


/*! \def  NULL
 *  Value of NULL : 0
 */
#ifndef NULL
#define NULL              0
#endif


  /*! \class  Angle gmAngle.h <gmAngle>
   *  \brief  Pending Documentation
   *
   *  Pending Documentation
   *
   *  Testing Examples:
   */
  class Angle {
  public:
    Angle( double r = 0.0 );
    Angle( int d );
    Angle( const Angle &a );

    int       getDeg() const;
    double    getRad() const;
    double    translate( double b = 0.0 );

    Angle&    operator =  ( double r );
    Angle&    operator =  ( int d );
    Angle&    operator =  ( Angle a );

    // Additions and substractions
    Angle&    operator += ( const Angle& a );
    Angle&    operator -= ( const Angle& a );
    Angle     operator -  () const;
    Angle     operator +  ( Angle a ) const;
    Angle     operator -  ( Angle a ) const;
    Angle     operator +  ( double r ) const;
    Angle     operator -  ( double r ) const;
    Angle     operator +  ( int d ) const;
    Angle     operator -  ( int d ) const;

    // Scaling
    Angle&    operator *= ( double r );
    Angle     operator *  ( double r ) const;

    // Invers scaling
    Angle&    operator /= ( double r );
    Angle     operator /  ( double r ) const;

    // Boolean on equality
    bool      operator == ( const Angle &a ) const;
    bool      operator != ( const Angle &a ) const;

    // Booleand on sorting
    bool      operator <  ( const Angle &a ) const;
    bool      operator >  ( const Angle &a ) const;
    bool      operator <= ( const Angle &a ) const;
    bool      operator >= ( const Angle &a ) const;


              operator double ();
              operator int ();


    /*! Angle Angle::operator * ( double r, Angle a )
     *  \brief  Multiply Angel object with the new angle (Radian)
     *
     *  Multiply Angle object with the new angle in radian.
     *
     *  \param  r Value of the angle in radian
     *  \param  a Angle object
     *  \return Copy of the Angle object
     */
    friend
    Angle     operator * ( double r, Angle a ) {

      a *= r;
      return a;
    }


  private:
    double      _angle;

  }; // END Angle

} // END namespace GMlib

// Include inline Angle class implementations
#include "gmAngle.c"



namespace GMlib {

  #ifdef GM_STREAM

    /*! T_Stream& operator << ( T_Stream &out, const Angle &a )
     *  \brief
     *
     *
     *
     *  \return T_Stream
     */
    template <typename T_Stream>
    T_Stream& operator << ( T_Stream &out, const Angle &a ) {

      out << a.getRad();
      return out;
    }



    /*! T_Stream& operator >> ( T_Stream &in, Angle &a )
     *  \brief
     *
     *
     *
     *  \return T_Stream
     */
    template <typename T_Stream>
    T_Stream& operator >> ( T_Stream &in, Angle &a ) {

      double tmp;

      in >> tmp;
      a = tmp;

      return in;
    }

  #endif

} // END namespace GMlib




#endif // __gmANGLE_H__

