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



/*! \file gmTriangleSystem_TSVEdge.c
 *  \brief TSVEdge class function implementations
 *
 *  \date   2010-04-16
 */


namespace GMlib {

  template <typename T>
  inline
  TSVEdge<T>::TSVEdge() {}

  template <typename T>
  inline
  TSVEdge<T>::TSVEdge(const Point<T,2> &p, const Point<T,2> &q) {
    _pnts[0] = p;
    _pnts[1] = q;
  }

  template <typename T>
  inline
  bool TSVEdge<T>::operator==(const TSVEdge<T> &e) const {

    bool a=false ,b= false;
    if ((e._pnts[0] == _pnts[0])||(e._pnts[0] == _pnts[1])) a = true;
    if ((e._pnts[1] == _pnts[0])||(e._pnts[1] == _pnts[1])) b = true;

    return (a && b);
  }

  template <typename T>
  inline
  bool TSVEdge<T>::operator<(const TSVEdge<T> &e) const {
    return false;
  }

  template <typename T>
  inline
  Point<T,2> const &TSVEdge<T>::operator() (int i) const {
    return _pnts[i];
  }

} // END namespace GMlib
