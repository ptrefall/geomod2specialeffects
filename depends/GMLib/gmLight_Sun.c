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



/*! \file gmLight_Sun.c
 *  \brief Inline Sun class implementations
 *
 *  Implementation of the Sun class.
 *
 *  \date   2008-08-03
 */


namespace GMlib {



  /*! const std::string Sun::getIdentity()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  std::string Sun::getIdentity() const {

    return "Sun";
  }


  /*! void Sun::scaleDayLight(double d)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void Sun::scaleDayLight(double d) {

    _setDayLight(d);
  }

}
