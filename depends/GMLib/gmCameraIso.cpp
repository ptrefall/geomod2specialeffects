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



/*! \file gmCameraIso.cpp
 *
 *  Implementation of the CameraIso class.
 *
 *  \date   2008-07-27
 */


// Header Include
#include "gmCameraIso.h"


namespace GMlib {


  /*! CameraIso::CameraIso(Scene* s)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  CameraIso::CameraIso(Scene* s) : Camera(s) {

    resetC();
  }


  /*!CameraIso::CameraIso( const Point<float,3>&  pos, const Point<float,3>&  look_pos )
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  CameraIso::CameraIso(
    const Point<float,3>&  pos,
    const Point<float,3>&  look_pos
  ) : Camera(pos,look_pos) {

    resetC();
  }


  /*! CameraIso::CameraIso( const Point<float,3>&  pos, const Vector<float,3>& dir, const Vector<float,3>& up, float zoom )
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  CameraIso::CameraIso(
    const Point<float,3>&  pos,
    const Vector<float,3>& dir,
    const Vector<float,3>& up,
    float zoom
  ) : Camera(pos,dir,up,zoom) {

    resetC(zoom);
  }


  /*! CameraIso::~CameraIso()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  CameraIso::~CameraIso() {}


  /*! double CameraIso::deltaTranslate(DisplayObject *)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  double CameraIso::deltaTranslate(DisplayObject * obj) {

    if(obj)
      return 2*_horisontal/getViewportH();
    else
      return 0.0;
  }


  /*! void CameraIso::go(bool stereo)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   *	Running the CameraIso.
   */
  void CameraIso::go(bool /*stereo*/) {

    _active = true;
    display();
    _active = false;
  }


  /*! void CameraIso::localDisplay()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void CameraIso::localDisplay() {}


  /*! void CameraIso::localSelect()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void CameraIso::localSelect() {}


  /*! void CameraIso::lockTarget(SceneObject* obj)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void CameraIso::lockTarget(SceneObject* /*obj*/) {}


  /*! void CameraIso::lockTarget(const Point<float,3>& p)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void CameraIso::lockTarget(const Point<float,3>& /*p*/) {}


  /*! void CameraIso::lockTarget(double d)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void CameraIso::lockTarget(double /*d*/) {}


  /*! SceneObject* CameraIso::lockTargetAtPixel(int x,int y)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  SceneObject* CameraIso::lockTargetAtPixel(int /*x*/,int /*y*/) {

    return 0;
  }


  /*! void CameraIso::resetC(float z)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   *	Only for the constructors.
   */
  void CameraIso::resetC(float z) {

    _horisontal	= z;
    _gw  = _gh  = 0.1;
  }


  /*! void CameraIso::setPerspective()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void CameraIso::setPerspective() {

    float	hh = (float)_horisontal;
    float	rr = (float)(_ratio*_horisontal);
    _frustum = Frustum(_matrix_scene,_pos,(float)_horisontal,_ratio,_dir,_up,_side,_near_plane,_far_plane);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-rr, rr, -hh, hh, _near_plane, _far_plane);
    glMatrixMode(GL_MODELVIEW);
  }


  /*! void CameraIso::zoom(float z)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  void CameraIso::zoom(float z) {

    _horisontal *= z;
  }

}
