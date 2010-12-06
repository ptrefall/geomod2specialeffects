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



/*! \file gmTriangleSystem_TSTriangle.c
 *  \brief TSTriangle class function implementations
 *
 *  \date   2008-10-24
 */


namespace GMlib {



  template <typename T>
  inline
  TSTriangle<T>::TSTriangle() {

    _edge[0] = NULL;
    _edge[1] = NULL;
    _edge[2] = NULL;
  }


  template <typename T>
  inline
  TSTriangle<T>::TSTriangle( TSEdge<T>* e1, TSEdge<T>* e2, TSEdge<T>* e3 ) {

    _edge[0] = e1;
    _edge[1] = e2;
    _edge[2] = e3;
  }


  template <typename T>
  inline
  TSTriangle<T>::TSTriangle( const TSTriangle<T>& t ) : _edge(t._edge), _box(t._box) {}


  template <typename T>
  TSTriangle<T>::~TSTriangle() {

    if( _edge[0] ) {

      _edge[0]->_removeTriangle( this );

      if( _edge[1] )
        _edge[1]->_removeTriangle( this );

      if( _edge[2] )
        _edge[2]->_removeTriangle( this );

      this->remove(this);
    }
  }


  template <typename T>
  T TSTriangle<T>::_evalZ( const Point2D<T>& p, int deg ) const {

    Array<TSVertex<T>*> ve = getVertices();
    Point2D<T> par[3];
    Point<T,3> pos[3];
    int i,j,k;

    for(i=0; i<3; i++) par[i] = pos[i] = ve[i]->getPosition();

    T a = p^par[0];
    T b = p^par[1];
    T c = p^par[2];
    T d = par[0]^par[1];
    T e = par[0]^par[2];
    T f = par[1]^par[2];
    T det = d-e+f;
    T u = (b-c+f)/det;
    T v = (-a+c-e)/det;
    T w = (a-b+d)/det;

    if (deg == 1)
      return u*pos[0](2) +v*pos[1](2) + w*pos[2](2);

    T pt[7];
    pt[6] = 0;

    for(i=0; i<3; i++) {

      if(i==2)	j = 0;
      else		j = i+1;
      k = 2*i;

      Vector3D<T>		vec = pos[j] - pos[i];
      vec[2] = 0;
      UnitVector3D<T> uv  = vec;
      T		   vec2 = 0.33333333333333333333*(vec*vec);

      Vector3D<T> vv	= ve[i]->getNormal()[2]*uv;
      vv[2]		   -= ve[i]->getNormal()*uv;
      pt[k]			= pos[i][2] + vec2/(vv*vec)*vv[2];

      vv				= ve[j]->getNormal()[2]*uv;
      vv[2]          -= ve[j]->getNormal()*uv;
      pt[k+1]			= pos[j][2] - vec2/(vv*vec)*vv[2];

      pt[6]		   += pt[k] + pt[k+1];
    }

    pt[6] /= 6;

    a = u*u;
    b = v*v;
    c = w*w;
    return a*u*pos[0](2) +   3*a*v*pt[0] + 3*u*b*pt[1] + b*v*pos[1](2) +
        3*a*w*pt[5]    + 6*u*v*w*pt[6] + 3*b*w*pt[2] +
        3*u*c*pt[4]    +   3*v*c*pt[3] +
         c*w*pos[2](2);
  }


  template <typename T>
  inline
  Box<unsigned char,2>& TSTriangle<T>::_getBox() {

    return _box;
  }


 // #ifdef __gmOPENGL_H__

  template <typename T>
  void TSTriangle<T>::_render()  {

    Array<TSVertex<T>*> v = getVertices();
    //double a = (v[0]->position()[2]+v[1]->position()[2]+v[2]->position()[2])/3/-5 + 0.0;

    //glColor4f(0.0, 0.3, a, 1.0);
  /* NY KODE FOR TEXTUREBRUK 1/9 -2001 (MARTIN)*/
    glTexCoord2f((v[0]->getPosition()[0])/100, (v[0]->getPosition()[1])/100);
    glVertex((Arrow<T,3>*)v[0]);
    glTexCoord2f((v[1]->getPosition()[0])/100, (v[1]->getPosition()[1])/100);
    glVertex((Arrow<T,3>*)v[1]);
    glTexCoord2f((v[2]->getPosition()[0])/100, (v[2]->getPosition()[1])/100);
    glVertex((Arrow<T,3>*)v[2]);
  }

 // #endif


  template <typename T>
  bool TSTriangle<T>::_reverse( TSEdge<T>* a ) {

    int i,j;

    if(a == _edge[0])	return true;
    else if(a == _edge[1]) i = 1;
    else if(a == _edge[2]) i = 2;
    else			return false;

    j = (i==1? 2:1);

    TSEdge<T> *tmp = _edge[0];
    _edge[0] = _edge[i];
    _edge[i] = _edge[j];
    _edge[j] = tmp;

    return true;
  }


  template <typename T>
  inline
  void TSTriangle<T>::_setEdges( TSEdge<T>* e1, TSEdge<T>* e2, TSEdge<T>* e3 ) {

    _edge[0] = e1;
    _edge[1] = e2;
    _edge[2] = e3;
  }


  template <typename T>
  bool TSTriangle<T>::_split( TSVertex<T>& p ) {

    TSEdge<T>* edg1 = new TSEdge<T>(p,*(_edge[0]->getCommonVertex(*(_edge[1]))));
    TSEdge<T>* edg2 = new TSEdge<T>(p,*(_edge[1]->getCommonVertex(*(_edge[2]))));
    TSEdge<T>* edg3 = new TSEdge<T>(p,*(_edge[2]->getCommonVertex(*(_edge[0]))));

    TSTriangle<T>* t2 = new TSTriangle<T>( edg1, _edge[1], edg2 );
    TSTriangle<T>* t3 = new TSTriangle<T>( edg2, _edge[2], edg3 );

    edg1->_setTriangle( this, t2 );
    edg2->_setTriangle( t2, t3 );
    edg3->_setTriangle( t3, this );

    _edge[1]->_setTriangle( _edge[1]->_getOther(this), t2 );
    _edge[2]->_setTriangle( _edge[2]->_getOther(this), t3 );

    insert( edg1 );
    insert( edg2 );
    insert( edg3 );

    edg2 = _edge[1];
    _edge[1] = edg1;
    edg1 = _edge[2];
    _edge[2] = edg3;

    insert( t2 );
    insert( t3 );

    adjust( this );

    _edge[0]->_okDelaunay();
    edg1->_okDelaunay();
    edg2->_okDelaunay();

    return true;
  }


  template <typename T>
  void TSTriangle<T>::_updateBox( ArrayT<T>& u, ArrayT<T>& v, int d ) {

    int k,s,n = 1 << d;
    int i0=0, i1=n, j0=0, j1=n;
    Array<TSVertex<T>*>  ve = getVertices();
    Box<T,2> b( ve[0]->getParameter(), ve[1]->getParameter(), ve[2]->getParameter() );

    for( int i=1; i <= d; i++ ) {

      s = n >> i;
      k = i0 + s;
      if ( u[k] < b.getValueMin(0)) i0 = k;
      k = i1 - s;
      if ( u[k] > b.getValueMax(0)) i1 = k;
      k = j0 + s;
      if ( v[k] < b.getValueMin(1)) j0 = k;
      k = j1 - s;
      if ( v[k] > b.getValueMax(1)) j1 = k;
    }
    _box.reset(Point2D<unsigned char>((unsigned char)i0,(unsigned char)j0));
    _box.insert(Point2D<unsigned char>((unsigned char)(i1-1),(unsigned char)(j1-1)));
  }


  template <typename T>
  inline
  T TSTriangle<T>::getAngleLargest() {

    SArray<Angle> a;
    a += this->_edges[0]->getVector().getAngle( this->_edges[1]->getVector() );
    a += this->_edges[1]->getVector().getAngle( this->_edges[2]->getVector() );
    a += this->_edges[2]->getVector().getAngle( this->_edges[0]->getVector() );
    a.sort();
    return (T) a[2].getRad();
  }


  template <typename T>
  inline
  T TSTriangle<T>::getAngleSmallest() {

    SArray<Angle> a;
    a += this->_edges[0]->getVector().getAngle( this->_edges[1]->getVector() );
    a += this->_edges[1]->getVector().getAngle( this->_edges[2]->getVector() );
    a += this->_edges[2]->getVector().getAngle( this->_edges[0]->getVector() );
    a.sort();
    return (T) a[0].getRad();
  }


  template <typename T>
  inline
  T TSTriangle<T>::getArea() {

    return ( Vector3D<T>(_edge[0]->getVector())^_edge[1]->getVector()).getLength() * 0.5;
  }


  template <typename T>
  inline
  T TSTriangle<T>::getArea2D() {

    T a=_edge[0]->getLength2D();
    T b=_edge[1]->getLength2D();
    T c=_edge[2]->getLength2D();
    T scf=0.5*(a+b+c);
    return sqrt(scf*(scf-a)*(scf-b)*(scf-c));
    //abs(_edge[0]->vector2D()^_edge[1]->vector2D())*0.5;
  }


  template <typename T>
  inline
  Point<T,3> TSTriangle<T>::getCenterPos() {

    Array<TSVertex<T>* > tmp= getVertices();
    return (tmp[0]->getPosition()+tmp[1]->getPosition()+tmp[2]->getPosition())/3.0;
  }


  template <typename T>
  inline
  Point<T,2> TSTriangle<T>::getCenterPos2D() {

    Array<TSVertex<T>* > tmp = getVertices();
    return (tmp[0]->getParameter() + tmp[1]->getParameter() + tmp[2]->getParameter())/3.0;
  }


  template <typename T>
  inline
  T TSTriangle<T>::getCircum() {

    return _edge[0]->getLength() + _edge[1]->getLength() + _edge[2]->getLength();
  }


  template <typename T>
  inline
  T TSTriangle<T>::getCircum2D() {

    return _edge[0]->getLength2D() + _edge[1]->getLength2D() + _edge[2]->getLength2D();
  }


  template <typename T>
  inline
  Array<TSEdge<T>*> TSTriangle<T>::getEdges() const	{

    return Array<TSEdge<T>*>(3,_edge);
  }


  template <typename T>
  Vector<T,3> TSTriangle<T>::getNormal() const {

    Array<TSVertex<T>*> v = getVertices();
    return  Vector3D<T>( v[1]->getPosition() - v[0]->getPosition() ) ^
            Vector3D<T>( v[2]->getPosition() - v[1]->getPosition() );
  }


  template <typename T>
  Array<TSVertex<T>*>	TSTriangle<T>::getVertices() const {

    Array<TSVertex<T>*> r;
    r.setSize(3);

    r[1] = _edge[0]->getCommonVertex( *(_edge[1]) );
    r[2] = _edge[1]->getCommonVertex( *(_edge[2]) );
    r[0] = _edge[2]->getCommonVertex( *(_edge[0]) );

    return r;
  }


  template <typename T>
  inline
  int TSTriangle<T>::isAround( const TSVertex<T>& v ) const {

    return v.isInside(*this);
  }










  //#if defined GM_STREAM
  //
  //
  //
  //template <typename T>
  //inline
  //ostream& TSTriangle<T>::operator << ( ostream& out, const TSTriangle<T>& v ) {
  //
  //  return v._prOut(out);
  //}
  //
  //
  //template <typename T>
  //inline
  //ostream& TSTriangle<T>::operator << ( ostream& out, const TSTriangle<T>* v ) {
  //
  //  return v->_prOut(out);
  //}
  //
  //
  //template <typename T>
  //inline
  //istream& TSTriangle<T>::operator>>( istream& in, TSTriangle<T>& v ) {
  //
  //  return v._prIn(in);
  //}
  //
  //
  //template <typename T>
  //inline
  //istream& TSTriangle<T>::operator >> ( istream& in, TSTriangle<T>* v ) {
  //
  //  return v->_prIn(in);
  //}
  //
  //
  //template <typename T>
  //inline
  //void TSTriangle<T>::print( char prompt[] = "TSTriangle<T>", ostream & out = std::cout ) const {
  //
  //  out << prompt << ": " << (*this) << "\n";
  //}
  //
  //
  //
  //
  //template <class T>
  //inline
  //ostream& TSTriangle<T>::_prOut(ostream& out)const {
  //
  //	Array<TSVertex<T>*> v = getVertices();
  //	out << (*v[0]) << " " << (*v[1]) << " " << (*v[2]) << " ";
  //
  //	return out;
  //}
  //
  //
  //template <class T>
  //inline
  //istream& TSTriangle<T>::_prIn(istream& in) {
  //
  //	Point<T,3> p1, p2, p3;
  //	in >> p1 >> p2 >> p3;
  //	_edge[0] = find(p1,p2);
  //	_edge[1] = find(p2,p3);
  //
  //	_edge[2] = find(p3,p1);
  //
  //	return in;
  //}
  //
  //
  //
  //#endif

}

