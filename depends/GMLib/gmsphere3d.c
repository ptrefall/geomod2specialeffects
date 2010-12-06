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



/*! \file gmSphere3D.c
 *  \brief Inline Shpere3D class implementations
 *
 *  Inline implementation of the Sphere3D class.
 *
 *  \date   2008-08-03
 */


// GMlib includes
#include "gmPoint3D.h"
#include "gmOpenGL.h"


namespace GMlib {



  /*! Sphere3D::Sphere3D(float r, int m1, int m2) : Sphere<float,3>(Point<float,3>(float(0)),r)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Sphere3D::Sphere3D(float r, int m1, int m2) : Sphere<float,3>(Point<float,3>(float(0)),r) {
    makeSample(m1,m2);
  }


  /*! Sphere3D::Sphere3D(const Sphere<float,3>& s, int m1, int m2) : Sphere<float,3>(s)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Sphere3D::Sphere3D(const Sphere<float,3>& s, int m1, int m2) : Sphere<float,3>(s) {
    makeSample(m1,m2);
  }


  /*! void Sphere3D::makeSample(int m1, int m2)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Sphere3D::makeSample(int m1, int m2) {
    double u,v,du,dv,sv,cv,su,cu,ru,r=_value;
    _m1 = m1-1; _m2 = m2+1;
    _pt[0] = Arrow<float,3>(_pos+Point3D<float>(0,0,(float)r), Vector3D<float>(0,0,1));
    _pt[1] = Arrow<float,3>(_pos+Point3D<float>(0,0,(float)-r),Vector3D<float>(0,0,-1));
    du = M_PI/m1;
    dv = M_2PI/m2;
    _p.setSize(_m1);
    u = M_PI_2-du;
    for(int i=0; i<_m1; i++,u-=du)
    {
      su = sin(u);
      cu = cos(u);
      ru = r*cu;
      _p[i].setSize(_m2);
      v = 0;
      for(int j=0; j<_m2; j++, v+=dv)
      {
        sv = (float)sin(v);
        cv = (float)cos(v);
        _p[i][j] = Arrow<float,3>(_pos+Point3D<float>((float)(ru*cv),(float)(ru*sv),(float)(r*su)),Vector3D<float>((float)(cu*cv),(float)(cu*sv),(float)su));
      }
    }
  }


  /*! void Sphere3D::display()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Sphere3D::display() {
    int j,i;
    glBegin(GL_TRIANGLE_FAN);
      glVertex(_pt[0]);
      for(j=0;j<_m2;j++)
        glVertex(_p[0][j]);
    glEnd();
    for(i=0; i<_m1-1; i++)
    {
      glBegin(GL_TRIANGLE_STRIP);
      for(j=0;j<_m2;j++)
      {
        glVertex(_p[i][j]);
        glVertex(_p[i+1][j]);
      }
      glEnd();
    }
    glBegin(GL_TRIANGLE_FAN);
      glVertex(_pt[1]);
      for(j=_m2-1;j>=0;j--)
        glVertex(_p[_m1-1][j]);
    glEnd();
  }

}

