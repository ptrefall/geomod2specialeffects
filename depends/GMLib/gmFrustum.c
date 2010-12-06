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



/*! \file gmFrustum.c
 *  \brief Inline Frustum class implementations
 *
 *  Inline implementation of the Frustum class.
 *  (previously located in: <gmOpenGL_Frustum.c>)
 *
 *  \date   2010-04-14 (2008-08-03)
 */



namespace GMlib {


  /*! Frustum(const Frustum&  v)
   *  \brief Pending Documentation
   *
   *  Default constructor
   */
  inline
  Frustum::Frustum(){}


  /*! Frustum::Frustum( const GL_Matrix& m, const Point<float,3>& p, const Vector<float,3>& d, const Vector<float,3>& u, const Vector<float,3>& s, float angle_tan, float ratio, float nearplane, float farplane )
   *  \brief Pending Documentation
   *
   *  Standar perspective constructor
   */
  inline
  Frustum::Frustum(
        const HqMatrix<float,3>& m,
        const Point<float,3>& p,
        const Vector<float,3>& d,
        const Vector<float,3>& u,
        const Vector<float,3>& s,
        float angle_tan,
        float ratio,
        float nearplane,
        float farplane
  ) {

    set(m,p,d,u,s,angle_tan,ratio,nearplane,farplane);
  }


  /*! stum::Frustum( const GL_Matrix& m, const Point<float,3>& p, float width, float ratio, const Vector<float,3>& d, const Vector<float,3>& u, const Vector<float,3>& s, float nearplane, float farplane )
   *  \brief Pending Documentation
   *
   *  Iso constructor constructor
   */
  inline
  Frustum::Frustum(
    const HqMatrix<float,3>& m,
    const Point<float,3>& p,
    float width,
    float ratio,
    const Vector<float,3>& d,
    const Vector<float,3>& u,
    const Vector<float,3>& s,
    float nearplane,
    float farplane
  ) {

    set(m,p,width,ratio,d,u,s,nearplane,farplane);
  }


  /*! Frustum(const Frustum&  v)
   *  \brief Pending Documentation
   *
   *  Copy constructor
   */
  inline
  Frustum::Frustum(const Frustum&  v)

    {memcpy(this,&v,sizeof(Frustum));
  }


  /*! void Frustum::set( const GL_Matrix& m, const Point<float,3>& p, const Vector<float,3>& d, const Vector<float,3>& u, const Vector<float,3>& s, float angle_tan, float ratio, float nearplane, float farplane )
   *  \brief Pending Documentation
   *
   *  Perspective
   */
  inline
  void Frustum::set(
    const HqMatrix<float,3>& m,
    const Point<float,3>& po,
    const Vector<float,3>& d,
    const Vector<float,3>& u,
    const Vector<float,3>& s,
    float at,
    float r,
    float nearplane,
    float farplane)
  {
    r *= at;
    double rr = sqrt(1+r*r);
    double tt = sqrt(1+at*at);
    Vector<float,3> f  = m*d;
    Vector<float,3> oe = m*u;
    Vector<float,3> ve = m*s;
    Vector<float,3> pp = r*ve-at*oe;
    _p[0] = m*po;			// Venstre, høyre, opp, ned (posisjon)
    _p[1] = _p[0]+farplane*(f+pp);
    _p[0] += nearplane*(f-pp);
    _v[0] = ve-r*f;			// Venstre	(normal)
    _v[1] = (_v[0]-2*ve)/rr;	// Høyre	(normal)
    _v[0] /= rr;
    _v[2] = oe-at*f;			// Opp		(normal)
    _v[3] = (_v[2]-2*oe)/tt;	// ned		(normal)
    _v[2] /= tt;
    _v[4] = -f;				// Bak		(normal)
    _v[5] = f;				// Fram		(normal)
  }


  /*! void Frustum::set( const GL_Matrix& m, const Point<float,3>& p, float width, float ratio, const Vector<float,3>& d, const Vector<float,3>& u, const Vector<float,3>& s, float nearplane, float farplane )
   *  \brief Pending Documentation
   *
   *  Iso
   */
  inline
  void Frustum::set(
    const HqMatrix<float,3>& m,
    const Point<float,3>& po,
    float w,
    float r,
    const Vector<float,3>& d,
    const Vector<float,3>& u,
    const Vector<float,3>& s,
    float nearplane,
    float farplane)
  {
    Vector<float,3> f  = m*d;
    Vector<float,3> oe = m*u;
    Vector<float,3> ve = m*s;
    _p[0] = m*po;
    _p[1] = _p[0]+farplane*f+w*(r*ve-oe);
    _p[0] += nearplane*f-w*(r*ve-oe);
    _v[0] = ve;				// Venstre	(normal)
    _v[1] = -ve;				// Høyre	(normal)
    _v[2] = oe;				// Opp		(normal)
    _v[3] = -oe;				// ned		(normal)
    _v[4] = -f;				// Bak		(normal)
    _v[5] = f;				// Fram		(normal)
  }


  /*! Point<float,3>  Frustum::getPos(int i) const
   *  \brief Pending Documentation
   *
   * Pending Documentation
   */
  inline
  Point<float,3>  Frustum::getPos(int i) const {
    if(i<4) return _p[0];
    else	return _p[i-3];
  }


  /*! Vector<float,3> Frustum::getNormal(int i) const
   *  \brief Pending Documentation
   *
   * Pending Documentation
   */
  inline
  Vector<float,3> Frustum::getNormal(int i) const {
    return _v[i];
  }


  /*! int Frustum::isInterfering(const Sphere<float,3>&) const
   *  \brief Pending Documentation
   *
   *  \htmlonly
   *    1 : Totally inside <br/>
   *    0 : Intersecting sides <br/>
   *   -1 : Totally outside <br/>
   *  \endhtmlonly
   *
   *  \todo
   *    For å optimalisere bør rekkefølgen av
   *    behandling av sidene studeres nærmere,
   *    i snitt bør antallet if else være under 3
   *    hvis objektet er utenfor frustrumet.
   */
  inline
  int Frustum::isInterfering(const Sphere<float,3>& s) const {

    if(!s.isValid())	return -1;
    int ret = 1;

    Vector<float,3> d = s.getPos()-_p[0];
    float dv = d*_v[1];							// Høyre
    if(dv >= s.getRadius())		return -1;
    else if(dv > -s.getRadius())	ret = 0;
    dv = d*_v[2];								// Opp
    if(dv >= s.getRadius())		return -1;
    else if(dv > -s.getRadius())	ret = 0;
    dv = d*_v[4];								// Bak
    if(dv >= s.getRadius())		return -1;
    else if(dv > -s.getRadius())	ret = 0;

    d=s.getPos()-_p[1];
    dv = d*_v[0];								// Venstre
    if(dv >= s.getRadius())		return -1;
    else if(dv > -s.getRadius())	ret = 0;
    dv = d*_v[3];								// Ned
    if(dv >= s.getRadius())		return -1;
    else if(dv > -s.getRadius())	ret = 0;
    dv = d*_v[5];								// Fram
    if(dv >= s.getRadius())		return -1;
    else if(dv > -s.getRadius())	ret = 0;
    return ret;
  }

} // END namespace GMlib
