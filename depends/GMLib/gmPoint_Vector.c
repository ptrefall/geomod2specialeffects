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



/*! \file gmPoint_Vector.c
 *  \brief Implementations for the Vector class
 *
 *  Implementations for the Vector class
 *
 *  \date   2008-06-19
 */


namespace GMlib {



  /*! Vector<T, n>::Vector() : Point<T, n>()
   *  \brief Default constructor, does not initalize the vector
   *
   *  Default constructor, does not initalize the vector.
   *  If the default constructor should be used, the vector needs to be initalized at a later point.
   */
  template <typename T, int n>
  inline
  Vector<T, n>::Vector() : Point<T, n>() {}


  /*! Vector<T, n>::Vector( T d ) : Point<T, n>(d)
   *  \brief Constructor taking a value t of T
   *
   *  Constructor taking a value t of T.
   *  The vector will be initialzied with t in each axis.
   *
   *  \param[in] t The initialization value.
   */
  template <typename T, int n>
  inline
  Vector<T, n>::Vector( T t ) : Point<T, n>(t) {}



  /*! Vector<T, n>::Vector( const T *t ) : Point<T, n>(t)
   *  \brief  Constructuer taking an array of n T values.
   *
   *  This constructor has been created to make the vector class
   *  compatible with other librarys and general datasets.
   *  The constructor presupposes that the input array has n T values.
   *
   * \param[in] t A const T pointer of n values.
   */
  template <typename T, int n>
  inline
  Vector<T, n>::Vector( const T *t ) : Point<T, n>(t) {}


  /*! Vector<T, n>::Vector( const Point<T, n> &p ) : Point<T, n>(p)
   *  \brief Default copy constructor
   *
   *  Default copy constructor.
   *  Taking a Point or Vector as parameter.
   *
   *  \param[in] p Point/Vector to copy from.
   */
  template <typename T, int n>
  inline
  Vector<T, n>::Vector( const Point<T, n> &p ) : Point<T, n>(p) {}


  /*! Point<T,n>& Vector<T, n>::getNormalized()
   *  \brief Get the vector normalized.
   *
   *  Get the vector normalized.
   *
   *  \return A normalized Vector
   */
  template <typename T, int n>
  inline
  Point<T,n> Vector<T, n>::getNormalized() {
    return (*this)/Point<T,n>::getLength();
  }

  /*! Vector<T,n> Vector<T, n>::getLinIndVec() const
   *  \brief Get a linear independent vector to the vector
   *
   *  Get a linear independent vector to the vector
   *
   *  \return A linear independent vector
   */
  template <typename T, int n>
  Vector<T,n> Vector<T, n>::getLinIndVec() const {

    if(n==1|| Point<T,n>::getLength()==0) return Vector<T,n>(T(0));
    else
    {
      int i,j=0;
      for(i=1; i < n;i++) if(( Point<T,n>::_pt[i]*Point<T,n>::_pt[i])>(Point<T,n>::_pt[j]*Point<T,n>::_pt[j])) j=i;
      if(j==0) i = 1;
      else	 i = j-1;

      Vector<T,n> r = *this;
      T tmp = -r[j];
      r[j]  = r[i];
      r[i]  = tmp;
      r    -= ((r*(*this))/((*this)*(*this)))*(*this);
      return r;
    }
  }


  /*! void Vector<T, n>::normalize()
   *  \brief Normalize the vector
   *
   *  Normalize the vector
   */
  template <typename T, int n>
  inline
  void Vector<T, n>::normalize() {
    (*this)/=Point<T,n>::getLength();
  }


  /*! void Vector<T, n>::setLength( T length )
   *  \brief Set the length of the vector
   *
   *  Set the length of the vector and adjust it accordingly
   *
   *  \param[in] length The new vector length
   */
  template <typename T, int n>
  inline
  void Vector<T, n>::setLength( T length ) {
    length /= Point<T,n>::getLength();
    (*this) *= length;
  }

}
