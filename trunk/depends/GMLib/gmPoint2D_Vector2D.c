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



/*! \file gmPoint2D_Vector2D.c
 *  File Description
 *
 *  \date   2008-07-08
 */



namespace GMlib {




  /*! Vector2D<T>::Vector2D(T d=1)
   *  \brief  Brief Description
   *
   *  Detailed description
   */
  template <typename T>
  inline
  Vector2D<T>::Vector2D(T d) : Vector<T,2>(d) {}


  /*! Vector2D<T>::Vector2D(const T p[2])
   *  \brief  Brief Description
   *
   *  Detailed description
   */
  template <typename T>
  inline
  Vector2D<T>::Vector2D(const T p[2]) : Vector<T,2>(p) {
  }


  /*! Vector2D<T>::Vector2D(const Point<T,2>& v)
   *  \brief  Brief Description
   *
   *  Detailed description
   */
  template <typename T>
  inline
  Vector2D<T>::Vector2D(const Point<T,2>& v) : Vector<T,2>(v)	{
  }

  /*! Vector2D<T>::Vector2D(const T& x,const T& y)
   *  \brief Brief Description
   *
   *  Detailed description
   */
  template <typename T>
  inline
  Vector2D<T>::Vector2D(const T& x,const T& y) : Vector<T,2>(Point2D<T>(x,y)) {
  }


  /*! T Vector2D<T>::operator^(const Point<T,2>& v) const
   *  \brief  Semi vector product.
   *
   *  Detailed description
   */
  template <typename T>
  inline
  T Vector2D<T>::operator^(const Point<T,2>& v) const {

    return this->_pt[0]*v(1)-this->_pt[1]*v(0);
  }

  /*! Vector2D<T,2>	Point<T,2>::getNormal()
   *  \brief  Return a vector 90 deg. to this.
   *
   *  Detailed description
   */
  template <typename T>
  inline
  Point<T,2>	Vector2D<T>::getNormal() {

    return Vector2D<T>(-this->_pt[1],this->_pt[0]);
  }

}
