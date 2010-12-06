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



/*! \file gmPoint_Box.c
 *  Implementations for the M_I_ class
 *
 *  \date   2008-06-20
 */


namespace GMlib {


  template <typename T, int n, int m>
  M_I_<T, n, m>::M_I_() {
    for(int k=0,i=0; i<n; i++)
      for(int j=0; j<m; j++)
        if(i==j)	_p[k++] = T(1);
        else		_p[k++] = T(0);
  }

  template <typename T, int n, int m>
  inline
  T* M_I_<T, n, m>::getPtr() const {
    return (T*)this;
  }

}
