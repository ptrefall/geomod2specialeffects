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



/*! \file gmUtils.c
 *
 *  GMUtils
 *
 *  \date   2010-05-16
 */


namespace GMlib {

  namespace GMutils {

    template <typename T>
    T fact( int j )
    {
      if ( j <= 0 )
        return T(1);

      T r=1;
      for( int i = j; i > 1; i-- )
        r *= i;

      return r;
    }


    template <typename T>
    T binomial( int n, int j )
    {
           if( n < j )
             return T(0);

           return fact <T> (n) / (double)( fact <T> (j) * fact <T> (n-j) );
    }


  } // END namespace GMutils

} // END namespace GMlib
