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
 *  \brief Inline CameraIso class implementations
 *
 *  Inline implementation of the CameraIso class.
 *
 *  \date   2008-08-03
 */


namespace GMlib {


  /*! void CameraIso::drawActivCam()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void CameraIso::drawActiveCam() {

    int i,ih,iw;
    iw = (int)(_horisontal/_gw);
    ih = (int)(_ratio*_horisontal/_gh);
    Point3D<float> cp=_pos+(0.99*_near_plane+0.01*_far_plane)*_dir;
    GLboolean lg;
    glGetBooleanv(GL_LIGHTING,&lg);
    if(lg) glDisable(GL_LIGHTING);
    Color gr(120,120,120);
    glColor(gr);
    glBegin(GL_LINES);
      Vector<float,3> dside = _gw*_side;
      Vector<float,3> dup   = _gh*_up;
      Vector<float,3> side  = ih*dside;
      Vector<float,3> up    = iw*dup;
      for(i=-iw; i<=iw; i++)
      {
        glPoint(cp+double(i)*dup-side);
        glPoint(cp+double(i)*dup+side);
      }
      for(i=-ih; i<=ih; i++)
      {
        glPoint(cp-up+double(i)*dside);
        glPoint(cp+up+double(i)*dside);
      }
    glEnd();
    if (lg) glEnable(GL_LIGHTING);
  }


  /*! std::string CameraIso::getIdentity() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  std::string CameraIso::getIdentity() const {

    return "CameraIso";
  }


  /*! void CameraIso::move(float d)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   *	Moveing in shooting direction
   */
  inline
  void CameraIso::move( float /* delta */ ) {}


  /*! void CameraIso::move(const Vector<float,3>& t)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   *	Move in direction t.
   */
  inline
  void CameraIso::move( const Vector<float,3>& /* delta */ ) {}


  /*! void CameraIso::rotate(Angle, const Vector<float,3>&)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void CameraIso::rotate( Angle /*angle*/, const Vector<float,3>& /* axel */ ) {}


  /*! void CameraIso::rotate(Angle, const Point<float,3>&,const UnitVector<float,3>&)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void CameraIso::rotate(Angle, const Point<float,3>&,const UnitVector<float,3>&) {}


  /*! void CameraIso::rotateGlobal(Angle, const Vector<float,3>&)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void CameraIso::rotateGlobal(Angle, const Vector<float,3>&) {}


  /*! void CameraIso::rotateGlobal(Angle, const Point<float,3>&,const UnitVector<float,3>&)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void CameraIso::rotateGlobal(Angle, const Point<float,3>&,const UnitVector<float,3>&) {}


  /*! void CameraIso::setGrid(double w, double h)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void CameraIso::setGrid(double w, double h) {
    _gw=w;
    _gh=h;
  }


  /*! void CameraIso::tilt(Angle a)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void CameraIso::tilt( Angle /* angle */ ) {}


  /*! void CameraIso::translate(const Vector<float,3>& trans_vector)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void CameraIso::translate( const Vector<float,3>& /*trans_vector*/ ) {}


  /*! void CameraIso::translateGlobal(const Vector<float,3>&)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void CameraIso::translateGlobal( const Vector<float,3>& /*trans_vector*/ ) {}


  /*! void CameraIso::turn(Angle a)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void CameraIso::turn( Angle /*angle*/ ) {}

}
