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



/*! \file gmDisplayObject.c
 *  \brief Inline DisplayObject class implementations
 *
 *  Implementation of the DisplayObject class.
 *
 *  \date   2008-08-03
 */

// local
#include "gmGLMatrix.h"

namespace GMlib {


  /*! void DisplayObject::basisChange( const Vector<float,3>& x, const Vector<float,3>& y, const Vector<float,3>& z, const Vector<float,3>& p )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void DisplayObject::basisChange( const Vector<float,3>& x, const Vector<float,3>& y, const Vector<float,3>& z, const Vector<float,3>& p ) {

    static GLMatrix glmat;
    glmat = _matrix.getTransposed().getPtr();
    glmat.basisChange( z,x,y,p );
    for( int i = 0; i < 4; i++ )
      for( int j = 0; j < 4; j++ )
        _matrix[i][j] = glmat.get(j,i);
  }


  /*! Vector<float,3>	DisplayObject::getDir()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  ** In scene coordinates **
   */
  inline
  Vector<float,3>	DisplayObject::getDir()	{

    return _matrix_scene*_dir;
  }


  /*! Point<float,3>	DisplayObject::getLockPos()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  ** In the coordinates of the scene. **
   */
  inline
  Point<float,3> DisplayObject::getLockPos() {

    if(_lock_object)
      return  _lock_object->getCenterPos();
    else
      return  _lock_pos;
  }


  /*! Pdouble DisplayObject::getLockDist()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  double DisplayObject::getLockDist() {

    if(_locked)
      return  ( getLockPos()-getPos() ).getLength();
    else
      return  0.0;
  }


  /*! Point<float,3> DisplayObject::getPos()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  ** In scene coordinates **
   */
  inline
  Point<float,3> DisplayObject::getPos() {

    return _matrix_scene * _pos;
  }


  /*! Vector<float,3>	DisplayObject::getSide()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  ** In scene coordinates **
   */
  inline
  Vector<float,3>	DisplayObject::getSide() {

    return _matrix_scene * _side;
  }


  /*! Vector<float,3>	DisplayObject::getUp()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  ** In scene coordinates **
   */
  inline
  Vector<float,3>	DisplayObject::getUp() {

    return _matrix_scene * _up;
  }


  /*! bool DisplayObject::isLocked()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  bool DisplayObject::isLocked() {

    return _locked;
  }


  /*! const std::string DisplayObject::getIdentity() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  Virtual SceneObject function
   */
  inline
  std::string DisplayObject::getIdentity() const {

    return "DisplayObject";
  }


  /*! Point<float,3> DisplayObject::getSceneLockPos()
   *  \brief Get Lock Position in Scene Coordinates
   *
   *  Get Lock Position in Scene coordinates
   */
  inline
  Point<float,3> DisplayObject::getSceneLockPos() {

    if(_lock_object)
      return _matrix_scene_inv * _lock_object->getCenterPos();
    else
      return _matrix_scene_inv * _lock_pos;
  }


  /*! void DisplayObject::updateOrientation(const Point<float,3>& lock_pos )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void DisplayObject::updateOrientation(const Point<float,3>& lock_pos ) {

    _dir		= lock_pos - _pos;
    _up			= _up - (_up * _dir) * _dir;
    _side		= _up ^ _dir;
  }

}
