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



/*! \file gmMaterial_MaterialObjectList.cpp
 *
 *  Implementation of the MaterialObjectList class.
 *
 *  \date   2008-07-24
 */


#include "gmMaterial.h"


namespace GMlib {


  /*! void	MaterialObjectList::initPreDef()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void	MaterialObjectList::initPreDef() {

    if( (getMaxSize() - getSize()) < 25 )
      setMaxSize( getMaxSize() + 25 );

    insert( MaterialObject( GMmaterial::BlackPlastic, "BlackPlastic" ) );
    insert( MaterialObject( GMmaterial::BlackRubber, "BlackRubber" ) );
    insert( MaterialObject( GMmaterial::Brass, "Brass" ) );
    insert( MaterialObject( GMmaterial::Bronze, "Bronze" ) );
    insert( MaterialObject( GMmaterial::Chrome, "Chrome" ) );
    insert( MaterialObject( GMmaterial::Copper, "Copper" ) );
    insert( MaterialObject( GMmaterial::Emerald, "Emerald" ) );
    insert( MaterialObject( GMmaterial::Gold, "Gold" ) );
    insert( MaterialObject( GMmaterial::Jade, "Jade" ) );
    insert( MaterialObject( GMmaterial::Obsidian, "Obsidian" ) );
    insert( MaterialObject( GMmaterial::Pearl, "Pearl" ) );
    insert( MaterialObject( GMmaterial::Pewter, "Pewter" ) );
    insert( MaterialObject( GMmaterial::Plastic, "Plastic" ) );
    insert( MaterialObject( GMmaterial::PolishedBronze, "PolishedBronze" ) );
    insert( MaterialObject( GMmaterial::PolishedCopper, "PolishedCopper" ) );
    insert( MaterialObject( GMmaterial::PolishedGold, "PolishedGold" ) );
    insert( MaterialObject( GMmaterial::PolishedGreen, "PolishedGreen" ) );
    insert( MaterialObject( GMmaterial::PolishedRed, "PolishedRed" ) );
    insert( MaterialObject( GMmaterial::PolishedSilver, "PolishedSilver" ) );
    insert( MaterialObject( GMmaterial::Ruby, "Ruby" ) );
    insert( MaterialObject( GMmaterial::Sapphire, "Sapphire" ) );
    insert( MaterialObject( GMmaterial::Silver, "Silver" ) );
    insert( MaterialObject( GMmaterial::Snow, "Snow" ) );
    insert( MaterialObject( GMmaterial::Turquoise, "Turquoise" ) );
  }


  /*! bool	MaterialObjectList::readFromFile(char* file_name)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  bool	MaterialObjectList::readFromFile( char* /*file_name*/ ) {

    return true;
  }


  /*! bool	MaterialObjectList::storeToFile(char* file_name)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  bool	MaterialObjectList::storeToFile( char* /*file_name*/ ) {

    return true;
  }

}
