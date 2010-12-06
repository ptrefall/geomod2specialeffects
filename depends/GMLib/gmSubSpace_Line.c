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



/*! \file gmSubSpace_Line.c
 *  \brief Implementation of the Static Line template class.
 *
 *  Implementation of the Static Line template class.
 *
 *  \date   2008-07-07
 */


namespace GMlib {



  /*!
   *  \brief
   */
  template <class T, int n>
  inline
  Line<T,n>::Line() : SubSpace<T,n,1> () {}


  /*!
   *  \brief
   */
  template <class T, int n>
  inline
  Line<T,n>::Line( const Point<T,n>& p ) : SubSpace<T,n,1>(p) {}


  /*!
   *  \brief
   */
  template <class T, int n>
  inline
  Line<T,n>::Line( const Point<T,n>& p, const Vector<T,n>& v) : SubSpace<T,n,1>(p,v) {}


  /*!
   *  \brief
   */
  template <class T, int n>
  inline
  Line<T,n>::Line( const Arrow<T,n>& a ) : SubSpace<T,n,1>(a) {}


  /*!
   *  \brief
   */
  template <class T, int n>
  inline
  Line<T,n>::Line( const SubSpace<T,n,1>& s) :  SubSpace<T,n,1>(s) {}

}
