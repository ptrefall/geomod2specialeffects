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



/*! \file gmScaleObjectect.c
 *  \brief Inline ScaleObjectect class implementations
 *
 *  Inline implementation of the ScaleObjectect class.
 *  (previously located in: <gmOpenGL_ScaleObject.c>)
 *
 *  \date   2010-04-14 (2008-08-03)
 */



namespace GMlib {



  /*! ScaleObject::ScaleObject()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  ScaleObject::ScaleObject() {
    reset();
  }


  /*! ScaleObject::ScaleObject(float	s)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  ScaleObject::ScaleObject(float	s) {
    reset(Point<float,3>(s));
  }


  /*! ScaleObject::ScaleObject(Point<float,3>	sc)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  ScaleObject::ScaleObject(Point<float,3>	sc) {
    reset(sc);
  }


  /*! void ScaleObject::scale(const Point<float,3>& sc)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void ScaleObject::scale(const Point<float,3>& sc) {
    _scaled=true; _s %= sc; _updateMax();
  }


  /*! void ScaleObject::reset()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void ScaleObject::reset() {
    _scaled=false; _s=Point<float,3>(1);
  }


  /*! void ScaleObject::reset(const Point<float,3>& sc)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void ScaleObject::reset(const Point<float,3>& sc) {
    if(sc(0)!= 1 || sc(1)!= 1 || sc(2)!= 1) { _s=sc; _updateMax(); _scaled=true; }
    else { _scaled=false; _s=sc; }
  }


  /*! void ScaleObject::glScaling()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void ScaleObject::glScaling() {
    if(_scaled) glScale(_s);
  }


  /*! bool  ScaleObject::isActive()  const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  bool  ScaleObject::isActive()  const {
    return _scaled;
  }


  /*! float ScaleObject::getMax() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  float ScaleObject::getMax() const {
    return _max;
  }


  /*! Point<float,3>const& ScaleObject::getScale()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Point<float,3>const& ScaleObject::getScale() {
    return _s;
  }


  /*! Sphere<float,3> ScaleObject::scaleSphere(const Sphere<float,3>& sp) const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Sphere<float,3> ScaleObject::scaleSphere(const Sphere<float,3>& sp) const {

    if(_scaled)
    {
      if(sp.isValid()) return Sphere<float,3>(_max*sp.getPos(),_max*sp.getRadius());
      else return sp;
    }
    else return sp;
  }


  /*! void ScaleObject::_updateMax()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void ScaleObject::_updateMax() {
    _max = (_s[0] > _s[1] ? ( _s[0]>_s[2] ? _s[0]:_s[2] ):(_s[1]>_s[2] ? _s[1]:_s[2]));
  }

} // END namespace GMlib
