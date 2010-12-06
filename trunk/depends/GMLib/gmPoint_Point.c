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



/*! \file gmPoint_Point.c
 *  \brief Implementations for the Point class
 *  Implementations for the Point class
 *
 *  \date   2008-06-17
 */


namespace GMlib {



  template <typename T, int n>
  Arrow<T, n>* Point<T, n>::_arrow = new Arrow<T, n>();

  template <typename T, int n>
  int Point<T, n>::_sortType = 1;



  /*! Point::Point()
   *  \brief  Default Constructor
   *
   *  Default constructor
   *  Takes no paramters, and will not initalize any values.
   *  This has been done intentionaly, to speedup creation of matrices.
   *  If point should be used by itself, use one of the other constructors.
   *  \see Point( T t )
   *  \see Point( const T *t )
   */
  template <typename T, int n>
  inline
  Point<T, n>::Point() {
    // SHOULD NOT INITIALIZE ANYTHING
    // Intentinonal speed enhancement.
  }


  /*! Point::Point( const Point<T, n> &p )
   *  \brief  Default Copy Constructor
   *
   *  Default copy constructor
   *
   *  \param p The Point object to be copied.
   */
  template <typename T, int n>
  inline
  Point<T, n>::Point( const Point<T, n> &p ) {
    _cpy(p);
  }


  /*! Point::Point( T t )
   *  \brief  Constructuer taking an init value
   *
   *  Initializing each component of the point to the init value
   *
   * \param t An initial value
   */
  template <typename T, int n>
  inline
  Point<T, n>::Point( T t ) {
    _cpy(t);
  }


  /*! Point::Point( const T *t )
   *  \brief  Constructuer taking an array of n T values.
   *
   *  This constructor has been created to make the point class
   *  compatible with other librarys and generel datasets.
   *  The constructor presupposes that the input array has n T values.
   *
   * \param t A const T pointer of n values.
   */
  template <typename T, int n>
  inline
  Point<T, n>::Point( const T *t ) {
    _cpy(t);
  }


  /*! Angle Point<T, n>::getAngle( Point<T, n> v ) const
   *  \brief Returns the angle between two points
   *
   *  Returns the angle between two vectors
   *  Has been moved down into the point class from the vector class,
   *  for convenience.
   *
   *  \param v The point to which the angle should be calculated.
   *  \return The angle between this point and the given point.
   */
  template <typename T, int n>
  Angle Point<T, n>::getAngle( Point<T, n> v ) const {

     Point<T, n> u = (*this);
     u /= u.getLength();
     v /= v.getLength();
     double ang = u*v;
     if (ang > 1.0) ang = 1.0;
     else if (ang < -1.0) ang = -1.0;
     ang = acos(ang);
     if (n ==2)
     {
        double orient = u[0]*v[1]-u[1]*v[0];
        if (orient >= 0.0) 	return Angle(ang);
        else 		            return Angle(2*M_PI - ang);
     }
     else                     return Angle(ang);
  }


  /*! T Point<T, n>::getLength() const
   *  \brief Returns the length of the point (vector)
   *
   *  Returns the length of the point (vector)
   *  Has been moved down into the point class from the vector class for convenience.
   *
   *  \return The length of the point (vector)
   */
  template <typename T, int n>
  inline
  T Point<T, n>::getLength() const {
    return T( sqrt( double( (*this) * (*this) ) ) );
  }


  /*! int Point<T, n>::getMaxIndex() const
   *  \brief Returns the index of the first point element with the max value.
   *
   *  Returns the index of the first point element with the max value.
   *  Dependent on the > (greater then) operator
   *
   *  \return The index of the first max value
   */
  template <typename T, int n>
  inline
  int Point<T, n>::getMaxIndex() const {
    // return GM_Static_<T,n>::maxIndex(pt);
    int j=0;
    for(int i=1; i<n; i++)
      if( _pt[i] > _pt[j] ) j = i;
    return j;
  }


  /*! int Point<T, n>::getMaxAbsIndex() const
   *  \brief Returns the index of the first point element with the max absolute value.
   *
   *  Returns the index of the first point element with the max absolute value.
   *  Dependent on the > (greater then) operator.
   *
   *  \return The index of the first max absolute value.
   */
  template <typename T, int n>
  inline
  int Point<T, n>::getMaxAbsIndex() const {
    // return GM_Static_<T,n>::maxIndex(pt);
    int j=0;
    for(int i=1; i<n; i++)
      if( std::fabs( _pt[i] ) > std::fabs( _pt[j] ) ) j = i;
    return j;
  }


  /*! T* Point<T, n>::getPtr() const
   *  \brief Returns a pointer to the point element dataset.
   *
   *  Returns a pointer to the point element dataset.
   *
   *  \return The pointer to the point element dataset.
   */
  template <typename T, int n>
  inline
  T* Point<T, n>::getPtr() const {
    return (T*)this;
  }


  /*! void Point<T, n>::setTestType( int t, const Point<T, n> &p, const Vector<T, n> &v )
   *  \brief Set how a point should be sorted in accordance to other points.
   *
   *  Set how a point should be sorted in accordance to other points.
   *  When set to type 1 the point will be sorted as closest to a point.
   *  When set to type 2 the point will be sorted as closes to a directional vector.
   *  When set to type 3 the point will be sorted as closes to a radar vector rotating 360 degreas from the offset point and vector.
   *
   *  \param[in] t The sorting type/method
   *  \param[in] p The point to sort after
   *  \param[in] v A complementary directional vector, when sorting according to degreas (radar)
   */
  template <typename T, int n>
  inline
  void Point<T, n>::setTestType( int t, const Point<T, n> &p, const Vector<T, n> &v ) {

    _sortType = t;
    if (t==1)
      _arrow->setPos(p);
    else if (t==2)
      _arrow->setDir(p);
    else if (t==3){
      _arrow->setPos(p);
      _arrow->setDir(v);
    }
    else {
      // Use a debug error message
    }
  }


  template <typename T, int n>
  inline
  Point<T, n>& Point<T, n>::operator = ( const T t ) {
    _cpy(t);
    return (*this);
  }


  template <typename T, int n>
  inline
  Point<T, n>& Point<T, n>::operator = ( const T *t ) {
    _cpy(t);
    return (*this);
  }


  template <typename T, int n>
  inline
  Point<T, n>& Point<T, n>::operator = ( const Point<T, n>& p) {
    _cpy(p);
    return (*this);
  }


  template <typename T, int n>
  inline
  Point<T, n>& Point<T, n>::operator += ( const Point<T, n>& p ) {
    GM_Static_<T, n>::peq( getPtr(), p.getPtr() );
    return *this;
  }


  template <typename T, int n>
  inline
  Point<T, n>& Point<T, n>::operator -= ( const Point<T, n>& p ) {
    GM_Static_<T, n>::meq( getPtr(), p.getPtr() );
    return *this;
  }


  template <typename T, int n>
  inline
  Point<T, n>& Point<T, n>::operator - () const {
    static Point<T, n> r;
    GM_Static_<T, n>::eqm( r.getPtr(), getPtr());
    return r;
  }


  template <typename T, int n>
  inline
  Point<T, n>& Point<T, n>::operator + ( const Point<T, n> &p ) const {
    static Point<T, n> r;
    GM_Static_<T, n>::eq_p( r.getPtr(), getPtr(), p.getPtr());
    return r;
  }


  template <typename T, int n>
  inline
  Point<T, n>& Point<T, n>::operator - ( const Point<T, n> &p ) const {
    static Point<T, n> r;
    GM_Static_<T, n>::eq_m( r.getPtr(), getPtr(), p.getPtr() );
    return r;
  }

  // Inner product
  template <typename T, int n>
  inline
  T Point<T, n>::operator * ( const Point<T, n> &p ) const {
    return GM_Static_<T, n>::dpr( getPtr(), p.getPtr() );
  }

  template <typename T, int n>
  inline
  T& Point<T, n>::operator [] ( int i) {
    return _pt[i];   //return given element.
  }

  template <typename T, int n>
  inline
  T const& Point<T, n>::operator () ( int i) const {
    return _pt[i]; //return copy.
  }


  template <typename T, int n>
  inline
  Point<T, n>& Point<T, n>::operator *= ( double d ) {
    GM_Static_<T, n>::sc( getPtr(), d );
    return *this;
  }


  template <typename T, int n>
  inline
  Point<T, n> Point<T, n>::operator * ( double d ) const {
  //  static Point<T, n> r;
    Point<T, n> r;
    GM_Static_<T, n>::sc_r( r.getPtr(), getPtr(), d);
    return r;
  }

  template <typename T, int n>
  inline
  Point<T, n>& Point<T, n>::operator %= ( const Point<T, n> &p ) {
    GM_Static_<T, n>::xeq( getPtr(), p.getPtr());
    return *this;
  }

  template <typename T, int n>
  inline
  Point<T, n>& Point<T, n>::operator % ( const Point<T, n> &p ) const {
    static Point<T, n> r;
    GM_Static_<T, n>::eq_x( r.getPtr(), getPtr(), p.getPtr());
    return r;
  }

  template <typename T, int n>
  inline
  Point<T, n>& Point<T, n>::operator /= ( double d ) {
    d = 1/d;
    return (*this)*=d;
  }

  template <typename T, int n>
  inline
  Point<T, n> Point<T, n>::operator /  ( double d ) const {
    d = 1/d;
    return (*this)*d;
  }



  template <typename T, int n>
  inline
  bool Point<T, n>::operator == ( const Point<T, n> &p ) const {
    Point<T,n> d=(*this)-p;
    return bool((d*d)<POS_TOLERANCE);
  }


  template <typename T, int n>
  inline
  bool Point<T, n>::operator != ( const Point<T, n> &pt ) const {
    return !((*this) == pt);
  }

  template <typename T, int n>
  inline
  bool Point<T, n>::operator <  ( const Point<T, n> &v ) const {
     switch(_sortType){
     case 1: return bool((_arrow->getPos()-(*this)).getLength() < (_arrow->getPos()-v).getLength());
     case 2: return bool((_arrow->getDir()*(*this)) <  (_arrow->getDir()*v));
     case 3: return bool(_arrow->getDir().getAngle((*this)-_arrow->getPos()) < _arrow->getDir().getAngle(v-_arrow->getPos()));
     default: return false;// Use a debug error-message
     }
  }

  template <typename T, int n>
  inline
  bool Point<T, n>::operator >  ( const Point<T, n> &v ) const {
     switch(_sortType){
     case 1: return bool((_arrow->getPos()-(*this)).getLength() > (_arrow->getPos()-v).getLength());
     case 2: return bool((_arrow->getDir()*(*this)) >  (_arrow->getDir()*v));
     case 3: return bool(_arrow->getDir().getAngle((*this)-_arrow->getPos()) > _arrow->getDir().getAngle(v-_arrow->getPos()));
     default: return false;// Use a debug error-message
     }
  }

  template <typename T, int n>
  inline
  bool Point<T, n>::operator <= ( const Point<T, n> &v ) const {
    return !((*this) > v);
  }

  template <typename T, int n>
  inline
  bool Point<T, n>::operator >= ( const Point<T, n> &v ) const {
    return !((*this) < v);
  }


  template <typename T, int n>
  template <typename G, int m>
  inline
  Point<T, n>::operator Point<G,m>& () const {
    static Point<G,m> v;
    GM_Static1_<G,T,(n<m?n:m)>::eq( v.getPtr(), getPtr());
    return v;
  }


  /*! Point<float,n>& Point<T, n>::toFloat() const
   *  \brief Returns a point where all point elements is casted to float type
   *
   *  Returns a point where all point elements is casted to float type
   *
   *  \return A point where all point elemets is of float type
   */
  template <typename T, int n>
  inline
  Point<float,n>& Point<T, n>::toFloat() const {
    static Point<float,n> v;
    GM_Static1_<float,T,n>::eq(v.getPtr(), getPtr());
    return v;
  }


  /*! Point<double,n> Point<T, n>::toDouble() const
   *  \brief Returns a point where all point elements is casted to double type
   *
   *  Returns a point where all point elements is casted to double type
   *
   *  \return A point where all point elemets is of double type
   */
  template <typename T, int n>
  inline
  Point<double,n> Point<T, n>::toDouble() const {
    static Point<double,n> v;
    GM_Static1_<double,T,n>::eq( v.getPtr(), getPtr());
    return v;
  }


  /*! void Point<T, n>::_cpy( const Point<T, n> &v )
   *  \brief Copys a point element data set.
   *
   *  Copys a point element data set.
   *  Takes a point-object as parameter,
   *  and uses memcpy to copy the data raw from the src point to the dest point (this).
   *
   *  \param[in] v The src Point, from where the data is collected.
   */
  template <typename T, int n>
  inline
  void Point<T, n>::_cpy( const Point<T, n> &v ) {
    memcpy( _pt, v._pt, sizeof( Point<T,n> ) );
  }


  /*! void Point<T, n>::_cpy( const T p[n] )
   *  \brief Copys a point element data set.
   *
   *  Copys a point element data set.
   *  Takes a point element array
   *  and uses memcpy to copy the data raw from the src point to the dest point (this).
   *
   *  \param[in] p The src point element data set, from where the data is collected.
   */
  template <typename T, int n>
  inline
  void Point<T, n>::_cpy( const T p[n] ) {
    memcpy( _pt, p, sizeof( Point<T,n> ) );
  }


  /*! void Point<T, n>::_cpy( const T &d )
   *  \brief Copys a point element data set.
   *
   *  Copys a point element data set.
   *  Takes a T value, and copys the value into every point element in the data set of the point object.
   *
   *  \param[in] d The value to be set in every point element.
   */
  template <typename T, int n>
  inline
  void Point<T, n>::_cpy( const T &d ) {
    GM_Static_<T,n>::eq( getPtr(), d );
  }

}
