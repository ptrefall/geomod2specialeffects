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



/*! \file gmStream_Separator.cpp
 *  \brief Implementation of Separator class.
 *
 *  Implementation of Separator class.
 *
 *  \date   2008-07-02
 */



#include "gmStream.h"


namespace GMlib{

  namespace GMseparator {

    // ****************************
    // Predefined Separator Objects


    /*! extern Separator GMseparator::Element
     *  \brief  This Separator is used between elements in a class
     *
     *  This Separator is used between elements in a class.
     *  E.g.: Point where each parameter direction is separated.
     */
    Separator Element = Separator();


    /*! extern Separator GMseparator::Object
     *  \brief  This Separator is used between objects in a class
     *
     *  This Separator is used between objects in a class.
     *  E.g.: Array where each object in the array is separated.
     */
    Separator Object = Separator();

    /*! extern Separator GMseparator::Group
     *  \brief  This Separator is used between groups
     *
     *  This Separator is used between groups.
     *  For now used in matrix where the row is grouped.
     */
    Separator Group = Separator('\n');

  }

}




