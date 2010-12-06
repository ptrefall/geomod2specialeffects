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



/*! \file gmAngle.c
 *  \brief Inline Angle class implementations
 *
 *  Inline implementations of the Angle class.
 *
 *  \date   2008-08-03
 */



namespace GMlib {



  /*! Angle::Angle( double r = 0.0 )
   *  \brief  Default Constructor (Radian)
   *
   *  Default initialize angle to 0.0.
   *
   *  \param  r Value of the angle in radian
   */
  inline
  Angle::Angle( double r ) {

    _angle = r;
  }


  /*! Angle::Angle( int d )
   *  \brief  Default Constructor (Degrees)
   *
   *  Initialize incomming degrees as radian. Conversion between degrees
   *  and radian is defined as Radian = Degrees * PI / 180.
   *
   *  \param  d Value of the angle in degrees
   */
  inline
  Angle::Angle( int d ) {

    _angle = d * M_PI_180;
  }


  /*! Angle::Angle( const Angle &a )
   *  \brief  Default Copy Constructor
   *
   *  Copy constructor.
   *
   *  \param  a Angle object
   */
  inline
  Angle::Angle( const Angle &a ) {

    _angle = a._angle;
  }


  /*! int Angle::getDegree() const
   *  \brief  Return the angle (Degrees)
   *
   *  Return the angle in degrees. Conversion between radian and degrees
   *  is defined as Degrees = Radian * 180 / PI.
   *
   *  \return The angle in degrees
   */
  inline
  int Angle::getDeg() const {

    return int(_angle * M_180_PI);
  }


  /*! double Angle::getRadian() const
   *  \brief  Return the angle (Radian)
   *
   *  Return the angle in radian.
   *
   *  \return The angle in radian
   */
  inline
  double Angle::getRad() const {

    return _angle;
  }


  /*! double Angle::translate( double lb = 0.0 )
   *  \brief  Translate periodic
   *
   *  This function translate current angle to a choosen period
   *  and also ensure that the angle is inside the choosen period.
   *  Default period is [0, 2Pi].
   *
   *  \param  b Lower boundary of the choosen period
   *  \return The angle of the new period
   */
  inline
  double Angle::translate( double b ) {

    double tmpAngle = _angle;

    // If current angle (tmpAngle) is lower than LowerBondary (b),
    // then translate current angle forward with 2Pi until it
    // is higher than the bondary
    while( tmpAngle < b ) { tmpAngle += M_2PI; }

    // Change to UpperBondary
    b += M_2PI;

    // If current angle (tmpAngle) is higher than UpperBondary (b),
    // then translate current angle backward with 2Pi until it
    // is lower than the bondary
    while( tmpAngle > b ) { tmpAngle -= M_2PI; }

    return tmpAngle;
  }


  /*! Angle& Angle::operator = ( double r )
   *  \brief  Initialize current angle (Radian)
   *
   *  Initialize current the angle.
   *
   *  \param  r Value of the angle in radian
   *  \return The reference of the Angle object
   */
  inline
  Angle& Angle::operator = ( double r ) {

    _angle = r;
    return (*this);
  }


  /*! Angle& Angle::operator = ( int d )
   *  \brief  Initialize current angle (Degrees)
   *
   *  Convert the degrees value into radian and
   *  then initialize the angle.
   *
   *  \param  d Value of the angle in degrees
   *  \return The reference of the Angle object
   */
  inline
  Angle& Angle::operator = ( int d ) {

    _angle = d * M_PI_180;
    return (*this);
  }


  /*! Angle& Angle::operator = ( Angle a )
   *  \brief  Initialize current angle
   *
   *  Initialize current angle to incomming Angle.
   *
   *  \param  a Angle object
   *  \return The reference of the Angle object
   */
  inline
  Angle& Angle::operator = ( Angle a ) {

    _angle = a._angle;
    return (*this);
  }


  /*! Angle& Angle::operator += ( const Angle &a)
   *  \brief  Add to current angle
   *
   *  Add to current angle.
   *
   *  \param a Angle object
   *  \return The reference of the Angle object
   */
  inline
  Angle& Angle::operator += ( const Angle &a) {

    _angle += a._angle;
    return (*this);
  }


  /*! Angle& Angle::operator -= ( const Angle &a )
   *  \brief  Substract current angle from the new angle
   *
   *  Substract current angle from the new angle.
   *
   *  \param  a Angle object
   *  \return The reference of the Angle object
   */
  inline
  Angle& Angle::operator -= ( const Angle &a ) {

    _angle -= a._angle;
    return (*this);
  }


  /*! Angle Angle::operator - () const
   *  \brief  Return negative of current angle
   *
   *  Return the negative of current angle.
   *
   *  \return Copy of the Angle object
   */
  inline
  Angle Angle::operator - () const {

    return Angle(-_angle);
  }


  /*! Angle Angle::operator + ( Angle a ) const
   *  \brief  Add Angle object with current angle
   *
   *  Add Angle object with current angle.
   *
   *  \param  a Angle object
   *  \return Copy of the Angle object
   */
  inline
  Angle Angle::operator + ( Angle a ) const {

    a += (*this);
    return a;
  }


  /*! Angle Angle::operator - ( Angle a ) const
   *  \brief  Substract Angle object from current angle
   *
   *  Substract Angle object from current angle.
   *
   *  \param  a Angle object
   *  \return Copy of the Angle object
   */
  inline
  Angle Angle::operator - ( Angle a ) const {

    a -= (*this);
    return -a;
  }


  /*! Angle Angle::operator + ( double r ) const
   *  \brief  Add to current angle (Radian)
   *
   *  Add to current angle in radian.
   *
   *  \param  r Value of the angle in radian
   *  \return Copy of the Angle object
   */
  inline
  Angle Angle::operator + ( double r ) const {

    return (*this) + Angle(r);
  }


  /*! Angle Angle::operator - ( double r ) const
   *  \brief  Substract current angle from the new angle (Radian)
   *
   *  Substract current angle from the new angle in radian.
   *
   *  \param  r Value of the angle in radian
   *  \return Copy of the Angle object
   */
  inline
  Angle Angle::operator - ( double r ) const {

    return (*this) - Angle(r);
  }


  /*! Angle Angle::operator + ( int d ) const
   *  \brief  Add to current angle (Degrees)
   *
   *  Add to current angle in degrees.
   *
   *  \param  d Value of the angle in degrees
   *  \return Copy of the Angle object
   */
  inline
  Angle Angle::operator + ( int d ) const {

    return (*this) + Angle(d);
  }


  /*! Angle Angle::operator - ( int d ) const
   *  \brief  Substract current angle from the new angle (Degrees)
   *
   *  Substract current angle from the new angle in degrees.
   *
   *  \param  d Value of the angle in degrees
   *  \return Copy of the Angle object
   */
  inline
  Angle Angle::operator - ( int d ) const {

    return (*this) - Angle(d);
  }


  /*! Angle& Angle::operator *= ( double r )
   *  \brief  Multiply current angle with the new angle (Radian)
   *
   *  Multiply current angle with the new angle in radian.
   *
   *  \param  r Value of the anlge in radian
   *  \return The reference of the Angle object
   */
  inline
  Angle& Angle::operator *= ( double r ) {

    _angle *= r;
    return (*this);
  }


  /*! Angle Angle::operator * ( double r ) const
   *  \brief  Multiply current angle with the new angle (Radian)
   *
   *  Multiply current angle with the new angle in radian.
   *
   *  \param  r Value of the angle in radian
   *  \return The reference of the Angle object
   */
  inline
  Angle Angle::operator * ( double r ) const {

    return Angle(_angle * r);
  }


  /*! Angle& Angle::operator /= ( double r )
   *  \brief  Divide current angle with the new angle (Radian)
   *
   *  Divide current angle with the new angle in radian.
   *
   *  \param  r Value of the angle in radian
   *  \return The reference of the Angle object
   */
  inline
  Angle& Angle::operator /= ( double r ) {

    r = 1 / r;
    (*this) *= r;
    return (*this);
  }


  /*! Angle Angle::operator / ( double r ) const
   *  \brief  Divide current angle with the new angle (Radian)
   *
   *  Divide current angle with the new angle in radian.
   *
   *  \param  r Value of the angle in radian
   *  \return Copy of the Angle object
   */
  inline
  Angle Angle::operator / ( double r ) const {

    r = 1 / r;
    return (*this) * r;
  }


  /*! bool Angle::operator == ( const Angle &a ) const
   *  \brief  Compare the angle
   *
   *  This function compares the angles by taking absolute difference
   *  between the angles and compares the result with a tolerance
   *  value. Return true if the result is lower than the tolerance.
   *
   *  \param  a Angle object
   *  \return TRUE if equal
   */
  inline
  bool Angle::operator == ( const Angle &a ) const {

    return std::fabs(_angle - a._angle) < ANGLE_TOLERANCE;
  }


  /*! bool Angle::operator != ( const Angle &a ) const
   *  \brief  Compare the angle
   *
   *  This function compares the angles.
   *
   *  \param  a Angle objec
   *  \return TRUE if not equal
   */
  inline
  bool Angle::operator != ( const Angle &a ) const {

    return !((*this) == a);
  }


  /*! bool Angle::operator < ( const Angle &a ) const
   *  \brief  Compare the angle
   *
   *  This function check if current angle is lower than
   *  the incomming angle.
   *
   *  \param  a Angle object
   *  \return TRUE if lower than incomming angle
   */
  inline
  bool Angle::operator < ( const Angle &a ) const {

    return _angle < a._angle;
  }


  /*! bool Angle::operator > ( const Angle &a ) const
   *  \brief  Compare the angle
   *
   *  This function check if current angle is greater than
   *  the incomming angle.
   *
   *  \param  a Angle object
   *  \return TRUE if greater than incomming angle
   */
  inline
  bool Angle::operator > ( const Angle &a ) const {

    return _angle > a._angle;
  }


  /*! bool Angle::operator <= ( const Angle &a ) const
   *  \brief  Compare the angle
   *
   *  This function check if current angle is lower or
   *  equals to the incomming angle.
   *
   *  \param  a Angle object
   *  \return TRUE if lower or euqals to the incomming angle
   */
  inline
  bool Angle::operator <= ( const Angle &a ) const {

    return !((*this) > a);
  }


  /*! bool Angle::operator >= ( const Angle &a ) const
   *  \brief  Compare the angle
   *
   *  This function check if current angle is greater or
   *  equals to the incomming angle.
   *
   *  \param  a Angle object
   *  \return TRUE if greater or equals to the incomming angle.
   */
  inline
  bool Angle::operator >= ( const Angle &a ) const {

    return !((*this) < a);
  }


  /*! Angle::operator double()
   *  \brief  Return the angle
   *
   *  Return the angle in radian, use the public funtion getRadian().
   *
   *  \return The angle in radian
   */
  inline
  Angle::operator double() {

    return getRad();
  }


  /*! Angle::operator int()
   *  \brief  Return the angle
   *
   *  Return the angle in degrees, use the public function getDegree().
   *
   *  \return The angle in degrees
   */
  inline
  Angle::operator int() {

    return getDeg();
  }

} // END namespace GMlib
