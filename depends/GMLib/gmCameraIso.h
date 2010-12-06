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



/*! \file gmCameraIso.h
 *
 *  Interface for the CameraIso class.
 *
 *  \date   2008-07-27
 */


#ifndef __gmCAMERAISO_H__
#define __gmCAMERAISO_H__


// GMlib Includes
#include "gmStream.h"
#include "gmCamera.h"

namespace GMlib {



	/*! \class CameraIso gmCameraIso.h <gmCameraIso>
	 *	\brief Pending Documentation
	 *
	 *	Pending Documentation
	 */
	class CameraIso : public Camera {
	public:
		CameraIso(Scene* s);
		CameraIso(
			const Point<float,3>&  pos,
			const Point<float,3>&  look_pos
		);
		CameraIso(
			const Point<float,3>&  pos,
			const Vector<float,3>& dir,
			const Vector<float,3>& up,
			float zoom=1
		);
		~CameraIso();

		double					deltaTranslate(DisplayObject *);
		std::string 		getIdentity() const;

		void 						go(bool stereo=false);
		void						lockTarget(SceneObject* obj);
		void						lockTarget(const Point<float,3>& p);
		void						lockTarget(double d);
		SceneObject*		lockTargetAtPixel(int,int);
		void 						move(float d);
		void 						move(const Vector<float,3>& t);


		void 						rotate(Angle, const Vector<float,3>&);
		void 						rotate(Angle, const Point<float,3>&,const UnitVector<float,3>&);
		void 						rotateGlobal(Angle, const Vector<float,3>&);
		void 						rotateGlobal(Angle, const Point<float,3>&,const UnitVector<float,3>&);

		void 						setGrid(double w, double h);
		void 						tilt(Angle a);
		void 						translate(const Vector<float,3>& trans_vector);
		void 						translateGlobal(const Vector<float,3>&);
		void 						turn(Angle a);
		void 						zoom(float z);


	protected:
		// ***********
		// From Camera
		void						setPerspective();

		// ****************
		// From SceneObject
		void						localDisplay();
		void						localSelect();


	private:
		double					_horisontal;
		double					_gh,_gw;

		// ***********
		// From Camera
		void						drawActiveCam();
		SceneObject*		find(unsigned int name);				/// \todo ????? NOT IMPLEMENTED !!`????? why??
		void						resetC(float z=1);


	};	// END class CameraIso

}	// END namespace GMlib

// Include inline implementations
#include "gmCameraIso.c"

#endif // __gmCAMERAISO_H__
