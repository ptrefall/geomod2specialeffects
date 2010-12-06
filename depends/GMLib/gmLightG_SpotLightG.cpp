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



/*! \file gmLightG_SpotLightG.cpp
 *
 *  Implementation of the SpotLightG class.
 *
 *  \date   2009-01-22
 */

// GMlib includes
#include "gmLightG.h"


namespace GMlib {


  SpotLightG::SpotLightG() {

    _init();
  }


  SpotLightG::SpotLightG(
    const Point<float,3>& pos,
    const Vector<float,3>& dir,
    Angle cut_off
  ) : SpotLight( pos, dir, cut_off ) {

    _init();
  }


  SpotLightG::SpotLightG(
    const Color& amb,
    const Color& dif,
    const Color& spe,
    const Point<float,3>& pos,
    const Vector<float,3>& dir,
    Angle cut_off
  ) : SpotLight( amb, dif, spe, pos, dir, cut_off ) {

    _init();
  }


  SpotLightG::SpotLightG( const SpotLight& copy ) : SpotLight( copy ) {

    _init();
  }


  SpotLightG::SpotLightG( const SpotLightG& copy) : SpotLight( copy ) {

    _dlist = copy._dlist;
    setSurroundingSphere( Sphere<float,3>( Point3D<float>( 0.0 ), 1.0 ) );
  }


  void SpotLightG::_init() {

    _dlist = 0;
    setSurroundingSphere( Sphere<float,3>( Point3D<float>( 0.0 ), 1.0 ) );

    _makeDisplayList();
  }


  void SpotLightG::_makeDisplayList() {


    int i;
    double k = 3.3;
    double b = k/sqrt(1+pow(tan(_cutoff.getRad()),2));
    double a = sqrt(k*k-b*b);
    if(_cutoff.getDeg()>90) b = -b;

    Vector3D<float> d = _dir;
    Vector3D<float> n = d^d.getLinIndVec();
    d.setLength((float)b);
    n.setLength((float)a);
    UnitVector3D<float> n2 = -d;
    if(_cutoff.getDeg()!=90) n2 = Vector3D<float>((b/a)*n-(a/b)*d);
    GLMatrix m1(Angle(30),_pos,_dir);
    GLMatrix m2(Angle(-30),_pos,_dir);

    Array<Point<float,3> > p1;
    p1 += _pos;
    p1 += _pos+d+n;
    for(i=1; i<12; i++) p1 += m1*p1.back();

    Vector3D<float> bb=0.6*d;
    if(b<0.0) bb.setLength(0.0);
    Array<Point<float,3> > p2;
    p2 += _pos+bb+0.1*_dir;
    p2 += _pos+0.6*d+0.6*n;
    for(i=1; i<12; i++) p2 += m2*p2.back();

    Array<Vector<float,3> > v1;
    v1 += UnitVector<float,3>(-d);
    v1 += n2;
    for(i=1; i<12; i++) v1 += m1*v1.back();

    Array<Vector<float,3> > v2;
    v2 += UnitVector<float,3>(d);
    v2 += UnitVector<float,3>(d+n);
    for(i=1; i<12; i++) v2 += m2*v2.back();



    if( _dlist )
      glDeleteLists( _dlist, 2 );

    _dlist = glGenLists( 2 );

    glNewList(_dlist, GL_COMPILE); // The Light Box
      glBegin(GL_TRIANGLE_FAN);
        for(i=0; i<p1.size(); i++) { glNormal(v1[i]); glPoint(p1[i]); }
        glNormal(v1[1]); glPoint(p1[1]);
      glEnd();
    glEndList();


    glNewList( _dlist+1, GL_COMPILE );  // The Light
      glBegin(GL_TRIANGLE_FAN);
        for(i=0; i<p2.size(); i++) { glNormal(v2[i]); glPoint(p2[i]); }
        glNormal(v2[1]); glPoint(p2[1]);
      glEnd();
    glEndList();

  }


  std::string SpotLightG::getIdentity() const {

    return "SpotLightG";
  }



  void SpotLightG::setCutOff(const Angle& cut_off) {

    SpotLight::setCutOff( cut_off );
    _makeDisplayList();
  }


  void SpotLightG::localDisplay() {

    // Draw Casing
    glPushAttrib( GL_POINT_BIT | GL_LIGHTING_BIT ); {

      GMmaterial::Bronze.glSet();
      glCallList( _dlist );

    } glPopAttrib();


    // Draw Light
    glPushAttrib( GL_LIGHTING_BIT ); {

      glDisable( GL_LIGHTING );

      glColor(getAmbient());
      glCallList( _dlist+1 );

    } glPopAttrib();
  }


  void SpotLightG::localSelect() {

    glCallList( _dlist );
  }

}

