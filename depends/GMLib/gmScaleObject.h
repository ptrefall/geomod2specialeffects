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



/*! \file gmScaleObject.h
 *
 *  ScaleObject class definitions
 *  (previously located in <gmOpenGL.h>
 *
 *  \date   2010-04-14 (2008-08-03)
 */


// local
#include "gmPoint.h"


#ifndef __GMSCALEOBJECT_H__
#define __GMSCALEOBJECT_H__


namespace GMlib {


  /*! \class ScaleObj
   *  \brief Pending Documentation
   *
   *  Scaleing Object
   */
  class ScaleObject {
  public:
    ScaleObject();
    ScaleObject(float	s);
    ScaleObject(Point<float,3>	sc);

    float                   getMax() const;
    Point<float,3>const&    getScale();
    void                    glScaling();

    bool                    isActive()  const;

    void                    reset();
    void                    reset(const Point<float,3>& sc);
    void                    scale(const Point<float,3>& sc);
    Sphere<float,3>         scaleSphere(const Sphere<float,3>& sp) const;


  private:
    bool                    _scaled;
    Point<float,3>          _s;
    float                   _max;

    void                    _updateMax();


  #ifdef GM_STREAM
    public:
      template<class T_Stream>
      friend T_Stream& operator<<(T_Stream& out, const ScaleObject& v)
      {
        out << (int)v._scaled << GMseparator::Element << v._s << GMseparator::Element << v._max ;
        return out;
      }

      template<class T_Stream>
      friend T_Stream& operator>>(T_Stream& in, ScaleObject& v)
      {
        static Separator es(GMseparator::Element);
        //		GLubyte r,g,b,a;
        int scaled;
        in >> scaled >> es >> v._s >> es >> v._max;
        v._scaled = (bool)scaled;
        return in;
      }

  #endif

  }; // END class ScaleObject

} // END namespace GMlib

// Include inline ScaleObject class implementations
#include "gmScaleObject.c"


#endif // __GMSCALEOBJECT_H__
