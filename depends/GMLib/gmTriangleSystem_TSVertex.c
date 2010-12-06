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



/*! \file gmTriangleSystem_TSVertex.c
 *  \brief TSVertex class function implementations
 *
 *  \date   2008-10-22
 */


namespace GMlib {


  template <typename T>
  inline
  TSVertex<T>::TSVertex() : Arrow<T,3>(), _edges() {

    _const = false;
    _maxradius = _radius = 0.0;
  }


  template <typename T>
  inline
  TSVertex<T>::TSVertex( const Point<T,2>& v ) : Arrow<T,3>( Point3D<T>( v(0), v(1), 0 ) ) {

    _const = false;
    _maxradius = _radius = 0.0;
  }


  template <typename T>
  inline
  TSVertex<T>::TSVertex( const Point<T,3>& p ) : Arrow<T,3>( p ), _edges() {

    _const = false;
    _maxradius = _radius = 0.0;
  }


  template <typename T>
  inline
  TSVertex<T>::TSVertex( const Point<T,3>& p, const Vector<T,3>& n ) : Arrow<T,3>( p, n ), _edges() {

    _const = false;
    _maxradius = _radius = 0.0;
  }


  template <typename T>
  inline
  TSVertex<T>::TSVertex( const T& x, const T& y, const T& z ) : Arrow<T,3>( Point3D<T>( x, y, z ) ), _edges() {

    _const = false;
    _maxradius = _radius = 0.0;
  }


  template <typename T>
  TSVertex<T>::~TSVertex() {

    _edges.clear();
  }


  template <typename T>
  void TSVertex<T>::_computeNormal() {

    Array<TSTriangle<T>*> tris = getTriangles();
    Point<T,3> nor = Point<T,3>(T(0));
    for( int i = 0; i < tris.getSize(); i++ )
      nor += tris[i]->getNormal();

    nor /= tris.getSize();
    setDir( UnitVector3D<T>(nor) );
  }


  template <typename T>
  void TSVertex<T>::_deleteEdges() {

    while( _edges.getSize() > 0 )
      delete _edges[0];

    _edges.clear();
  }


  template <typename T>
  inline
  bool TSVertex<T>::_insertEdge(TSEdge<T>* e)	{

    return _edges.insert( e );
  }


  template <typename T>
  inline
  bool TSVertex<T>::_removeEdge(TSEdge<T>* e)	{

    return _edges.remove( e );
  }


  template <typename T>
  inline
  void TSVertex<T>::_set( const Point<T,3>& p, const Vector<T,3>& n ) {

    setPos(p);
    setDir(n);
  }


  template <typename T>
  inline
  void TSVertex<T>::_set( const TSVertex<T>& v ) {

    _set( v.getPosition(), v.getNormal() );
    _const = v._const;
  }


  template <typename T>
  inline
  bool TSVertex<T>::boundary() const {

    for( int i = 0; i < _edges.getSize(); i++ )
      if( _edges(i)->boundary() )
        return true;

    return false;
  }


  template <typename T>
  inline
  Arrow<T,3> TSVertex<T>::getArrow() {

    Arrow<T,3> r( this->getPos(), this->getDir() );
    return r;
  }


  template <typename T>
  inline
  ArrayT<TSEdge<T>*>&	TSVertex<T>::getEdges() {

    return _edges;
  }


  template <typename T>
  inline
  Point<T,3> TSVertex<T>::getNormal() const {

    return this->getDir();
  }


  template <typename T>
  Array<TSEdge<T>*> TSVertex<T>::getOuterEdges() const {

    Array<TSTriangle<T>*> tris  = getTriangles();
    Array<TSEdge<T>*>		s_edg = getEdges();
    Array<TSEdge<T>*>		o_edg( s_edg.getSize() );

    int i, j;
    for( i = 0; i < tris.getSize(); i++ ) {

      Array<TSEdge<T>*>	ee = tris[i]->getEdges();
      for( j = 0; j < ee.getSize(); j++ )
        if( !s_edg.exist( ee[j] ) )
          o_edg += ee[j];
    }

    return o_edg;
  }


  template <typename T>
  inline
  Point<T,2> TSVertex<T>::getParameter() const {

    return Point2D<T>( this->getPos() );
  }


  template <typename T>
  inline
  Point<T,3> TSVertex<T>::getPosition() const	{

    return this->getPos();
  }


  template <typename T>
  inline
  T TSVertex<T>::getRadius() {

    return _radius;
  }


  template <typename T>
  inline
  T TSVertex<T>::getRadiusMax() {

    return _maxradius;
  }


  template <typename T>
  inline
  T TSVertex<T>::getRadiusMin() {

    return _minradius;
  }


  template <typename T>
  Array<TSTriangle<T>*> TSVertex<T>::getTriangles() const {

    Array<TSTriangle<T>*> tris;
    for( int i = 0; i < _edges.getSize(); i++ )
      tris.insert( _edges(i)->getTriangle() );

    return tris;
  }


  template <typename T>
  inline
  bool TSVertex<T>::isConst() const {

    return _const;
  }


  template <typename T>
  int  TSVertex<T>::isInside( TSTriangle<T>* t ) const {

    Array<TSVertex<T>*> v = t->getVertices();
    Array<Point<T,2> > a;

    for( int i = 0; i < 3; i++ )
      a += v[i]->getParameter();

    Point2D<T> p = this->getPos();

    return p.isInside( a );
  }


  template <typename T>
  inline
  void TSVertex<T>::setConst( bool c ) {

    _const = c;
  }


  template <typename T>
  inline
  void TSVertex<T>::setRadius( T r ) {

    _radius = r;
  }


  template <typename T>
  inline
  void TSVertex<T>::setRadiusMax( T r ) {

    _maxradius = r;
  }


  template <typename T>
  inline
  void TSVertex<T>::setRadiusMin( T r ) {

    _minradius = r;
  }


  template <typename T>
  void TSVertex<T>::setZ( T z ) {

    setPos( Point3D<T>( this->getPosition()[0], this->getPosition()[1], z ) );
  }


  template <typename T>
  TSVertex<T>& TSVertex<T>::operator = ( const TSVertex<T>& t ) {

    _edges = t._edges;
    _const = t._const;

    _set( t.getPosition(),	t.getNormal() );

    return (*this);
  }


  template <typename T>
  inline
  bool TSVertex<T>::operator == (const TSVertex<T>& t) const {

    return getParameter() == t.getParameter();
  }


  template <typename T>
  inline
  bool TSVertex<T>::operator < (const TSVertex<T> &t) const {

    return true;
  }




  //
  //#if defined GM_STREAM
  //
  //
  //template <typename T>
  //inline
  //ostream& TSVertex<T>::operator<<(ostream& out, const TSVertex<T>& v) {
  //
  //  return v._prOut(out);
  //}
  //
  //
  //template <typename T>
  //inline
  //ostream& TSVertex<T>::operator<<(ostream& out, const TSVertex<T>* v) {
  //
  //  return v->_prOut(out);
  //}
  //
  //
  //template <typename T>
  //inline
  //istream& TSVertex<T>::operator>>(istream& in, TSVertex<T>& v)	{
  //
  //  return v._prIn(in);
  //}
  //
  //
  //template <typename T>
  //inline
  //istream& TSVertex<T>::operator>>(istream& in, TSVertex<T>* v)	{
  //
  //  return v->_prIn(in);
  //}
  //
  //
  //
  //template <typename T>
  //inline
  //void TSVertex<T>::print(char prompt[]="TSVertex<T>", ostream & out = std::cout) const {
  //
  //  out << prompt << ": " << (*this) << "\n";
  //}
  //
  //
  //
  //
  //
  //template <typename T>
  //inline
  //ostream& TSVertex<T>::_prOut(ostream& out)const
  //{
  //	out << getPosition() << GMlib::GMseparator::Group;
  ////	if(  ) out << dir() << "\n ";
  //
  //	return out;
  //}
  //
  //
  //template <typename T>
  //inline
  //istream& TSVertex<T>::_prIn(istream& in)
  //{
  //	Point<T,3> p;
  //	in >> p; setPos(p);
  ////	if(  ) in >> p; setDir(p);
  //	return in;
  //}
  //
  //
  //#endif


}
