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



/*! \file gmPoint3D_Plane3D.c
 *  File Description
 *
 *  \date   2008-07-03
 */



namespace GMlib {



  /*! Plane3D<T,n>:: Plane3D()
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T, int n>
  inline
  Plane3D<T,n>::Plane3D() : Arrow<T,3>() {
  }

  /*! Plane3D<T,n>:: Plane3D()
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T, int n>
  inline
  Plane3D<T,n>::Plane3D(const Point<T,3>& p) : Arrow<T,3>(p) {
  }

  /*! Plane3D<T,n>:: Plane3D()
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T, int n>
  inline
  Plane3D<T,n>::Plane3D(const Point<T,3>& p ,const Vector<T,n>& v) : Arrow<T,3>(p,v) {
  }

  /*! Plane3D<T,n>:: Plane3D()
   *  \brief  Default Constructor
   *
   *  Detailed description of
   *  the default constructor
   */
  template <typename T, int n>
  inline
  Plane3D<T,n>::Plane3D(const Arrow<T,3>& a) : Arrow<T,3>(a) {
  }

  /*! void Plane3D<T,n>::setNormal(const Vector<T,3>& v)
   *  \brief  setNormal
   *
   *  Detailed description of
   *  the function
   */
  template <typename T, int n>
  inline
  void Plane3D<T,n>::setNormal(const Vector<T,3>& v) {
    setDir(v);
  }

  /*! const Vector<T,3>&	Plane3D<T,n>::getNormal()
   *  \brief  getNormal
   *
   *  \return normal
   *  Detailed description of
   *  the function
   */
  template <typename T, int n>
  inline
  const Vector<T,3>&	Plane3D<T,n>::getNormal() const {
    return Arrow<T, n>::getDir();
  }

  /*! Point<T,3> Plane3D<T,n>::getClosestPoint(const Point<T,3>& p) const
   *  \brief  getNormal
   *
   *  Detailed description of
   *  the function
   *
   *	\param[in] 	p
   *  \return 		closestPoint
   */
  template <typename T, int n>
  inline
  Point<T,3> Plane3D<T,n>::getClosestPoint(const Point<T,3>& p) const {

    Vector<T,3> d = p-Arrow<T, n>::getPos();
    return Arrow<T, n>::getPos()+d-(d*getNormal())*getNormal();
  }

  /*! Vector<T,3> Plane3D<T,n>::getDistanceVector(const Point<T,3>& p) const
   *  \brief  getDistanceVector
   *
   *  \return distanceVector
   *  Detailed description of
   *  the function
   */
  template <typename T, int n>
  inline
  Vector<T,3> Plane3D<T,n>::getDistanceVector(const Point<T,3>& p) const {

    Vector<T,3> d = p-Arrow<T,n>::getPos();
    return (d*getNormal())*getNormal();
  }

  /*! T Plane3D<T,n>::getDistanceTo(const Point<T,3>& p) const
   *  \brief  getDistanceTo
   *
   *  \return distanceTo
   *  Detailed description of
   *  the function
   */
  template <typename T, int n>
  inline
  T Plane3D<T,n>::getDistanceTo(const Point<T,3>& p) const {

    return (p-Arrow<T,n>::getPos())*getNormal();
  }

}
