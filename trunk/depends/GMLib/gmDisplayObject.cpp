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



/*! \file gmDisplayObject.cpp
 *
 *  Implementation of the DisplayObject class.
 *
 *  \date   2008-07-22
 */


// STL includes
#include <string>

// Header
#include "gmDisplayObject.h"


namespace GMlib {


  /*! DisplayObject::DisplayObject( const Point<float,3>&  pos, const Vector<float,3>& dir, const Vector<float,3>& up )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  DisplayObject::DisplayObject(
    const Point<float,3>&  pos,
    const Vector<float,3>& dir,
    const Vector<float,3>& up
  ) : SceneObject(),_matrix_scene(),_matrix_scene_inv() {

    set( pos, dir, up );
  }


  /*! DisplayObject::DisplayObject( const Point<float,3>&  lockPos, const Point<float,3>&  pos, const Vector<float,3>& up )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  DisplayObject::DisplayObject(
    const Point<float,3>&  lock_pos,
    const Point<float,3>&  pos,
    const Vector<float,3>& up
  ) : SceneObject(), _matrix_scene(), _matrix_scene_inv() {

    Vector<float,3> dir = up.getLinIndVec();
    set(pos,dir,up);
    _locked	= true;
    _lock_pos    = lock_pos;
  }


  /*! DisplayObject::DisplayObject( SceneObject* lockObject, const Point<float,3>&  pos, const Vector<float,3>& up )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  DisplayObject::DisplayObject(
    SceneObject* lock_object,
    const Point<float,3>&  pos,
    const Vector<float,3>& up
  ) : SceneObject(), _matrix_scene(), _matrix_scene_inv() {

    Vector<float,3> dir = up.getLinIndVec();
    set( pos, dir, up );
    _locked	= true;
    _lock_object	= lock_object;
  }


  /*! DisplayObject::DisplayObject( const DisplayObject& s )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  DisplayObject::DisplayObject( const DisplayObject& s )
    : SceneObject(s), _matrix_scene( s._matrix_scene ), _matrix_scene_inv( s._matrix_scene_inv )
  {

    set( s._pos, s._dir, s._up );
    _locked	= s._locked;
    _lock_object	= s._lock_object;
    _lock_pos	= s._lock_pos;
  }


  /*! DisplayObject::~DisplayObject()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  DisplayObject::~DisplayObject() {}


  /*! void DisplayObject::lock(SceneObject* obj)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void DisplayObject::lock(SceneObject* obj) {

    if(obj) {
      updateOrientation(obj->getCenterPos());

      basisChange(_side, _up, _dir, _pos);

      _locked	= true;
      _lock_object = obj;
    }
  }


  /*! void DisplayObject::lock( const Point<float,3>& pos )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  ** must be in scene coordinates **
   */
  void DisplayObject::lock( const Point<float,3>& pos ) {

    _lock_pos	= pos;
    _locked	= true;
    _lock_object = 0;
  }


  /*! void DisplayObject::lock( double d )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  ** must be in scene coordinates **
   */
  void DisplayObject::lock( double d ) {

    _lock_pos	= _matrix_scene * (_pos + d*_dir);
    _locked	= true;
    _lock_object = 0;
  }


  /*! void DisplayObject::move( float d )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  Moveing in shooting direction
   */
  void DisplayObject::move( float d ) {

    _pos += d*_dir;
    basisChange(_side, _up, _dir, _pos);
  }


  /*! void DisplayObject::move( const Vector<float,3>& t )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  Move in direction t.
   */
  void DisplayObject::move( const Vector<float,3>& t ) {

    Point3D<float> lock_pos;

    if( _locked ) {
      lock_pos = getSceneLockPos();
      _pos += t;
      updateOrientation(lock_pos);
    }
    else _pos += t;

    basisChange(_side, _up, _dir, _pos);
  }


  /*! void DisplayObject::move(char,double)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  Track u (up) d (down) l (left) r (right)
   */
  void DisplayObject::move(char c, double d) {

    double dir_length = double();
    Point3D<float> lock_pos;

    if(_locked)
    {
      lock_pos  = getSceneLockPos();
      dir_length = ( lock_pos - _pos ).getLength();
    }

    switch (c) {
    case 'u':
      _pos += d*_up;
      break;
    case 'd':
      _pos -= d*_up;
      break;
    case 'l':
      _pos += d*_side;
      break;
    case 'r':
      _pos -= d*_side;
      break;
    default:
      break;
    }

    if(_locked)
    {
      updateOrientation(lock_pos);
      _pos	= lock_pos - dir_length * _dir;
    }

    basisChange(_side, _up, _dir, _pos);
  }


  /*! void DisplayObject::move(const Vector<float,2>& t)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  Track in direction t.
   */
  void DisplayObject::move(const Vector<float,2>& t) {

    double dir_length;
    Point3D<float> lock_pos;

    if(_locked)
    {
      lock_pos  = getSceneLockPos();
      dir_length = (lock_pos - _pos).getLength();

      _pos += t(0)*_side + t(1)*_up;

      updateOrientation(lock_pos);
      _pos	= lock_pos - dir_length*_dir;
    }
    else {
      _pos += _side*t(0) + _up*t(1);
    }
    basisChange(_side, _up, _dir, _pos);
  }


  /*! void DisplayObject::roll(Angle a)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void DisplayObject::roll(Angle a) {

    Vector3D<float> ra = _dir;
    Vector3D<float> lu = ra.getLinIndVec();
    Vector<float,3> u = lu ^ ra;
    Vector<float,3> v = ra ^ u;

    HqMatrix<float,3> m( a, u, v );
    _up   = m * _up;
    _side = m * _side;
    basisChange(_side, _up, _dir, _pos);
  }


  /*! void DisplayObject::set ( const Point<float,3>&  pos, const Vector<float,3>& dir, const Vector<float,3>& up )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  ** In scene coordinates **
   */
  void DisplayObject::set (
    const Point<float,3>&  pos,
    const Vector<float,3>& dir,
    const Vector<float,3>& up
  ) {

    _pos	= pos;
    _dir	= dir;
    _up		= up - (up*_dir)*_dir;
    _side	= _up^_dir;
    _locked	= false;
    _lock_object	= 0;

    basisChange(_side, _up, _dir, _pos);
  }


  /*! void DisplayObject::tilt( Angle a )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void DisplayObject::tilt( Angle a ) {

    if(!_locked) {

      Vector3D<float> ra = _side;
      Vector3D<float> lu = ra.getLinIndVec();
      Vector<float,3> u = lu ^ ra;
      Vector<float,3> v = ra ^ u;

      HqMatrix<float,3> m( a, u, v );
      _up   = m * _up;
      _dir  = m * _dir;
      basisChange(_side, _up, _dir, _pos);
    }
  }


  /*! void DisplayObject::turn(Angle a)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void DisplayObject::turn(Angle a) {

    if(!_locked) {

      Vector3D<float> ra = _up;
      Vector3D<float> lu = ra.getLinIndVec();
      Vector<float,3> u = lu ^ ra;
      Vector<float,3> v = ra ^ u;

      HqMatrix<float,3> m( a, u, v );
      _dir  = m * _dir;
      _side = m * _side;
      basisChange(_side, _up, _dir, _pos);
    }
  }


  /*! void DisplayObject::unLock()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  void DisplayObject::unLock() {

    _locked	= false;
    _lock_object = 0;
  }


  /*! void DisplayObject::rotate(Angle a, const Vector<float,3>& rot_axel)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  Virtual SceneObject function
   *  ** In local coordinates.**
   */
  void DisplayObject::rotate(Angle a, const Vector<float,3>& rot_axel) {

    if(_locked)
    {
      Point3D<float> lock_pos = getSceneLockPos();
      double dir_length = (lock_pos - _pos).getLength();
      Vector3D<float> t,ra=rot_axel;
      double dd= a.getRad()/M_PI_4;
      while(dd > 1.0)
      {
        t = ra^_dir;
        t.setLength((float)dir_length);
        move(Vector2D<float>(t*_side,t*_up));
        dd -= 1.0;
      }
      t = ra^_dir;
      t.setLength(tan((float)(dd*M_PI_4))*(float)dir_length);
      move(Vector2D<float>(t*_side,t*_up));
    }
    else
    {
      Vector3D<float> ra = rot_axel;
      Vector3D<float> lu = ra.getLinIndVec();
      Vector<float,3> u = lu ^ ra;
      Vector<float,3> v = ra ^ u;

      HqMatrix<float,3> m( a, u, v );
      _up   = m * _up;
      _dir  = m * _dir;
      _side = m * _side;
    }
    basisChange(_side, _up, _dir, _pos);
  }


  /*! void DisplayObject::rotate(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  Virtual SceneObject function
   *  ** In local coordinates.**
   */
  void DisplayObject::rotate(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d) {

    Vector3D<float> ra = d;
    Vector3D<float> lu = ra.getLinIndVec();
    Vector<float,3> u = lu ^ ra;
    Vector<float,3> v = ra ^ u;

    HqMatrix<float,3> m( a, u, v, p );
    _pos  = m * _pos;
    _up   = m * _up;
    _dir  = m * _dir;
    _side = m * _side;

    if(_locked)
    {
      Point3D<float> lock_pos = getSceneLockPos();
      updateOrientation(lock_pos);
    }

    basisChange(_side, _up, _dir, _pos);
  }


  /*! void DisplayObject::rotateGlobal(Angle a, const Vector<float,3>& rot_axel)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  Virtual SceneObject function
   *  ** In Scene Coordinates **
   */
  void DisplayObject::rotateGlobal(Angle a, const Vector<float,3>& rot_axel) {

    rotate( a, _matrix_scene_inv * rot_axel );
  }


  /*! void DisplayObject::rotateGlobal(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  Virtual SceneObject function
   *  ** In Scene Coordinates **
   */
  void DisplayObject::rotateGlobal(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d) {

    rotate( a, _matrix_scene_inv * p, _matrix_scene_inv *d );
  }


  /*! void DisplayObject::translate( const Vector<float,3>& trans_vector )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  Virtual SceneObject function
   *  ** In local coordinates.**
   */
  void DisplayObject::translate( const Vector<float,3>& trans_vector ) {

    move(trans_vector);
  }


  /*! void DisplayObject::translateGlobal(const Vector<float,3>& trans_vector)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  Virtual SceneObject function
   *  ** In Scene Coordinates **
   */
  void DisplayObject::translateGlobal(const Vector<float,3>& trans_vector) {

    move( _matrix_scene_inv * trans_vector );
  }


  /*! void DisplayObject::_prepareDisplay(const HqMatrix<float,3>& m)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  Virtual SceneObject function
   */
  void DisplayObject::_prepareDisplay( const HqMatrix<float,3>& mat ) {

    /*! \todo fix the way the matrix is handled */
    _matrix_scene = mat;
    _matrix_scene_inv = mat;
    _matrix_scene_inv.invertOrthoNormal();
  }


  /*! void DisplayObject::localSimulate(double dt)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  Virtual SceneObject function
   */
  void DisplayObject::localSimulate( double /*dt*/ ) {

    if(_locked) {

      updateOrientation( getSceneLockPos() );
      basisChange(_side, _up, _dir, _pos);
    }
  }

}
