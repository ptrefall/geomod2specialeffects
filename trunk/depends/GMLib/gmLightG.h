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



/*! \file gmLightG.h
 *
 *  Interface for the Graphical Light Classes
 *	Graphical versions of
 *  PointLight and SpotLight
 *
 *  \date   2009-01-22
 */



#ifndef __gmLIGHTG_H__
#define __gmLIGHTG_H__


// STL include
#include <string>

// GMlib includes
#include "gmLight.h"

namespace GMlib{


  class PointLightG : public PointLight {
  public:
    PointLightG();
		PointLightG(	const Point<float,3>& pos);
		PointLightG(
      const Color& amb,
			const Color& dif,
			const Color& spe,
			const Point<float,3>& pos
		);
		PointLightG( const PointLight& copy );
		PointLightG( const PointLightG& copy );

		std::string     getIdentity() const;

  protected:
    void            localDisplay();
    void            localSelect();

  private:
    unsigned int    _dlist;

    void            _init();
    void            _makeDisplayList();
  };






  class SpotLightG : public SpotLight {
  public:
		SpotLightG();
		SpotLightG(
			const Point<float,3>& pos,
			const Vector<float,3>& dir,
			Angle cut_off
    );
		SpotLightG(
			const Color& amb,
			const Color& dif,
			const Color& spe,
			const Point<float,3>& pos,
			const Vector<float,3>& dir,
			Angle cut_off = 90
    );

		SpotLightG( const SpotLight& copy );
		SpotLightG( const SpotLightG& copy );

		std::string     getIdentity() const;

		void            setCutOff(const Angle& cut_off);

  protected:
    void            localDisplay();
    void            localSelect();

  private:
    unsigned int    _dlist;

    void            _init();
    void            _makeDisplayList();






  };

}


#endif // __gmLIGHTG_H__
