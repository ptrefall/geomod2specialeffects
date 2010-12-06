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



/*! \file gmMaterial_MaterialObjectList.c
 *  \brief Inline MaterialObjectList class implementations
 *
 *  Implementation of the MaterialObjectList class.
 *
 *  \date   2008-08-03
 */

namespace GMlib {


  /*! MaterialObjectList::MaterialObjectList(bool init)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  MaterialObjectList::MaterialObjectList(bool init) {

    if(init)
      initPreDef();
  }


  /*! MaterialObjectList::MaterialObjectList(char* file_name)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  MaterialObjectList::MaterialObjectList( char* file_name ) {

    if(file_name) readFromFile(file_name);
  }

}
