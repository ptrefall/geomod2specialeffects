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



/*! \file gmTimer.c
 *  \brief Inline mplementation of the GMTimer class.
 *
 *  Implementation of the GMTimer class.
 *
 *  \date   2008-07-16
 */

#include "gmTimer.h"


namespace GMlib {



  inline
  GMTimer::GMTimer() {

    ftime(&_time);
  }


  inline
  int GMTimer::getMilli( bool set ) {

    int   diff;
    timeb newTime;

    ftime(&newTime);
    diff = (int)(newTime.time - _time.time) * 1000 + newTime.millitm - _time.millitm;

    if(set) { _time = newTime; }
    return diff;
  }


  inline
  double GMTimer::getSec( bool set ) {

    return getMilli(set) / 1000.0;
  }


  inline
  void GMTimer::update() {

    ftime(&_time);
  }

}
