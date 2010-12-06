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



/*! \file gmTriangleSystem_TriangleFacets.c
 *  \brief TriangleFacets class function implementations
 *
 *  \date   2008-10-22
 */

// stl
#include <cmath>

// local
#include "gmOpenGL.h"
#include "gmSArray.h"

namespace GMlib {

  template <class T>
  TriangleFacets<T>* TriangleSystem<T>::_tv = NULL;

  template <typename T>
  inline
  TriangleFacets<T>::TriangleFacets( int d ) : ArrayLX<TSVertex<T> >( d > 0 ? d+3 : 0 ), _edges(), _triangles() {

    //setStreamMode();
    _dlist_name=0;
  }


  template <typename T>
  inline
  TriangleFacets<T>::TriangleFacets( const ArrayLX<TSVertex<T> >& v): ArrayLX<TSVertex<T> >(v.size()+3), _edges(),_triangles()	{

    (*this) = v;
    //setStreamMode();
    _dlist_name = 0;
  }


  template <typename T>
  TriangleFacets<T>::~TriangleFacets() {

    int k=0,r=0,s=0,p=0;
    int i,j;
    for(i=0; i < _tri_order.getDim1(); i++)
    {
      for(j=0; j< _tri_order.getDim2(); j++)
      {
        r += _tri_order[i][j].getMaxSize();
        s += _tri_order[i][j].getSize();
        k += _tri_order[i][j].getMaxSize() - _tri_order[i][j].getSize();
        if(_tri_order[i][j].getMaxSize() > 20) p++;
      }
    }

    int ptbt=8*_tri_order.getDim1()*_tri_order.getDim2()+8 + 8*_tri_order.getDim1();

    std::cout << "antall element strre enn 20: " << p << " Av totalt: "
       << _tri_order.getDim1()*_tri_order.getDim2() << std::endl;

    std::cout << "Total byte pr element i matrise  : "
       << (4*r)/((double)_tri_order.getDim1()*_tri_order.getDim2()) << std::endl;

    std::cout << "Total kbyte bruk i matrise  : " << (4*r + ptbt)/1024 << std::endl;
    std::cout << "Minimum kbyte bruk i matrise: " << (4*s + ptbt)/1024 << std::endl;
    std::cout << "For mye kbyte bruk i matrise: " << (4*k)/1024  << std::endl;

    std::cout << "Total byte pr pkt i matrise  : " << (4*r + ptbt)/((double)this->getSize()) << std::endl;
    std::cout << "Minimum byte pr pkt i matrise: " << (4*s + ptbt)/((double)this->getSize()) << std::endl;
    std::cout << "For mye byte pr pkt i matrise: " << (4*k)/((double)this->getSize()) << std::endl;

    for(k=i=0; i< this->getSize(); i++) k += 4+8+4*(*this)[i].getEdges().getMaxSize();
    for(i=0; i< _edges.getSize(); i++) k += 4*5;
    for(i=0; i< _triangles.getSize(); i++) k += 14;


    std::cout << "Totalt brukt memory :" << (4*r+ptbt+k)/1024 << " kbyte\n";


    for(r=k=i=0; i< this->getSize(); i++)
    {
      k += (*this)[i].getEdges().getSize();
      r += (*this)[i].getEdges().getMaxSize();
    }
    std::cout << "Antall edger i snitt i Verticene: " << ((double)k)/i << std::endl;
    std::cout << "Max edger i snitt i Verticene   : " << ((double)r)/i << std::endl;

    clear();
  }


  template <typename T>
  void TriangleFacets<T>::_adjustTriangle( TSTriangle<T>* t, bool wider ) {

    int i,j;
    Box<unsigned char,2> b	= t->_getBox();
    t->_updateBox( _u, _v, _d );
    Box<unsigned char,2> a	= t->_getBox();

    for( i = b.getValueAt(0,0); i <= b.getValueAt(1,0); i++ )
      for( j = b.getValueAt(0,1); j <= b.getValueAt(1,1); j++ )
        if( i < a.getValueAt(0,0) || i > a.getValueAt(1,0) )
          _tri_order[i][j].remove(t);
        else if( j < a.getValueAt(0,1) || j > a.getValueAt(1,1) )
          _tri_order[i][j].remove(t);

    if(wider)
      for(i=a.getValueAt(0,0); i<=a.getValueAt(1,0); i++)
        for(j=a.getValueAt(0,1); j<=a.getValueAt(1,1); j++)
          if( i < b.getValueAt(0,0) || i > b.getValueAt(1,0) )
            _tri_order[i][j] += t;
          else if( j < b.getValueAt(0,1) || j > b.getValueAt(1,1) )
            _tri_order[i][j] += t;
  }


  template <typename T>
  inline
  ArrayLX<TSEdge<T>* >& TriangleFacets<T>::_getEdges() {

    return _edges;
  }


  template <typename T>
  bool TriangleFacets<T>::_fillPolygon( Array<TSEdge<T>*>& e ) {

    int i, j, index;
    bool stop;



    for(i=0; i< e.getSize(); i++)
    {
      TSTriangle<T>* t = e[i]->other(NULL);
      t->_reverse(e[i]);
      Array<TSEdge<T>*> edg = t->getEdges();
      if(e[i]->isFirst(e[i]->getCommonVertex(*edg[1])))
          e[i]->reverse();
    }

    for(i=0; i< e.getSize()-1; i++)
      for(j=i+1; j< e.getSize(); j++)
        if(e[i]->isLast(e[j]->getFirstVertex())) e.swap(i+1,j);


    TSEdge<T> *a = e[0];
    TSEdge<T> *b = e[1];
    int k0,k1,k2;

    while(e.getSize() > 3)
    {
      // Angle ang;
      SArray<Angle> ang;
      Array<int> index;

      for(i=0 ;i<e.getSize(); i++)
      {
        a = i==0? e[e.getSize()-1] : e[i-1];
        b = e[i];
        ang += (b->getVector2D()).getAngle(-(a->getVector2D()));
      }

      index=ang.sort();

      for(i=index.getSize()-1; i>=0; i--)
      {
        k1 = index[i];
        k0 = k1==0 ? e.getSize()-1 : k1-1;
        k2 = k1==e.getSize()-1 ? 0 : k1+1;
        for (j=0;  j< e.getSize(); j++)
        {
          if(j==k0 || j==k1 || j==k2) continue;

          if(e[j]->getFirstVertex()->getParameter().isInside(e[k0]->getFirstVertex()->getParameter(),
                                 e[k1]->getFirstVertex()->getParameter(),
                                 e[k2]->getFirstVertex()->getParameter()))
                                 break;
        }
        if(j==e.getSize()) break;
      }

      if(i<0) ;//error
      else
      {
        a = e[k0];
        b = e[k1];

        TSEdge<T> *ne = new TSEdge<T>(*(a->getFirstVertex()),*(b->getLastVertex()));
        TSTriangle<T> *nt = new TSTriangle<T>(ne,b,a);
        a->swapTriangle(NULL,nt);
        b->swapTriangle(NULL,nt);
        ne->setTriangle(nt,NULL);
        _edges += ne;
        insertTriangle(nt);
        e[k0] = ne;
        e.remove(b);
      }
    }

    TSTriangle<T> *nt = new TSTriangle<T>(e[2],e[1],e[0]);
    e[0]->swapTriangle(NULL,nt);
    e[1]->swapTriangle(NULL,nt);
    e[2]->swapTriangle(NULL,nt);
    insertTriangle(nt);

    return 1;
  }


  template <typename T>
  TSVertex<T>*  TriangleFacets<T>::_find( const Point<T,3>& p ) const {

    int i;
    for( i = 0; i < this->getSize(); i++ )
      if( this->getElement(i).getPosition() == p) break;

    if (i < this->getSize()) return &( this->getElement(i));
    else			return NULL;
  }


  template <typename T>
  TSEdge<T>*   TriangleFacets<T>::_find( const Point<T,3>& p1, const Point<T,3>& p2 ) const {

    int i;
    for(i=0; i<_edges.getSize(); i++)
      if( _edges(i)->hasPoints( p1, p2 ) ) break;

    if (i < _edges.getSize()) return _edges(i);
    else			return NULL;
  }


  template <typename T>
  void TriangleFacets<T>::_insertTriangle( TSTriangle<T>* t ) {

    _triangles += t;

    t->_updateBox( _u, _v, _d );

    Box<unsigned char,2> b	= t->_getBox();

    for( int i = b.getValueAt(0,0); i <= b.getValueAt(1,0); i++ )
      for( int j = b.getValueAt(0,1); j <= b.getValueAt(1,1); j++ )
        _tri_order[i][j] += t;
  }


  template <typename T>
  bool TriangleFacets<T>::_removeLastVertex() {

    (*this)[ this->getSize()-1 ]._deleteEdges();
    return removeIndex( this->getSize()-1 );

  }


  template <typename T>
  void TriangleFacets<T>::_removeTriangle( TSTriangle<T>* t ) {

    _triangles.remove(t);

    Box<unsigned char,2> b	= t->_getBox();

    for( int i = b.getValueAt(0,0); i <= b.getValueAt(1,0); i++ )
      for( int j = b.getValueAt(0,1); j <= b.getValueAt(1,1); j++ )
        _tri_order[i][j].remove(t);
  }


  /** void TriangleFacets<T>::_set( int i )
   *  \brief SET -COMPUTE THE TRIANGLE SYSTEM FOR THE VERTEX
   *
   *  Go through all vertices and if a vertex is on
   *  an edge split the edge and the two neighbour
   *  triangles, or if the vertex is inside one triangle
   *  split the triangle into three treangles
   */
  template <typename T>
  void TriangleFacets<T>::_set( int i ) {

    TSTriangle<T>* t;
    int k = _surroundingTriangle(t, (*this)[i]);

    if (k < 0)
      t->getEdges()[-(k+1)]->_split((*this)[i]);		// Split an edge
    else if (k>0)
      t->_split((*this)[i]);						// Split a triangle
    else
    {
        // Error vertex outside system or?
    }
  }


  template <typename T>
  int  TriangleFacets<T>::_surroundingTriangle( TSTriangle<T>*& t, const TSVertex<T>& v ) {

    int k,s,n = 1 << _d;
    Point<T,2>	nb = v.getParameter();

    int i=0,j=0;
    int it;
    for(it=1; it <= _d; it++)
    {
      s = n >> it;
      k = i + s;
      if ( _u(k) < nb[0]) i = k;
      k = j + s;
      if ( _v(k) < nb[1]) j = k;
    }

    k=0;
    for (it=_tri_order[i][j].getSize()-1; it>=0; it--)
      if( ( k = v.isInside( _tri_order[i][j](it) ) ) ) break;

      t = (it >= 0 ? _tri_order[i][j](it) : NULL);

    return k;
  }


  template <typename T>
  inline
  ArrayLX<TSTriangle<T>* >&	TriangleFacets<T>::_triangle()	{

    return _triangle;
  }


  template <typename T>
  inline
  Point<T,3> TriangleFacets<T>::eval( T x, T y, int deg ) const {

    return Point3D<T>( x, y, evalZ( x, y, deg ) );
  }


  template <typename T>
  inline
  Point<T,3> TriangleFacets<T>::eval( const Point2D<T>& p, int deg ) const {

    return eval( p(0), p(1), deg );
  }


  template <typename T>
  T TriangleFacets<T>::evalZ( const Point2D<T>& p, int deg ) {

    T z = 0;
    TSTriangle<T>* t;
    int idx = _surroundingTriangle( t, TSVertex<T>(p) );

    if( idx )
      z=t->evalZ( p, deg );

    return z;
  }


  template <typename T>
  inline
  T TriangleFacets<T>::evalZ( T x, T y, int deg ) {

    return evalZ( Point2D<T>( x, y ), deg );
  }


  template <typename T>
  void TriangleFacets<T>::clear( int d ) {

    __e.set(*this);

    while( _triangles.getSize() > 0 )
      delete _triangles[0];

    while( _edges.getSize() > 0 )
      delete _edges[0];

    _triangles.clear();
    _edges.clear();

	_vorpnts.clear();
	_voredges.clear();

    ((ArrayLX< TSVertex<T> >*)this)->clear();

    if (d >= 0)
      _d = d;

	if (_dlist_name) {
		glDeleteLists(_dlist_name,1);
		_dlist_name = 0;
	}
  }


  template <typename T>
  void TriangleFacets<T>::computeNormals() {

    for( int i = 0; i < this->getSize(); i++ )
      (*this)[i]._computeNormal();
  }


  template <typename T>
  inline
  void TriangleFacets<T>::createVoronoi() {

    for (int i=0; i<_triangles.size(); i++) {
      Point2D<T> c;

      Array<TSVertex<T> *> v = _triangles(i)->getVertices();

      Point<T,2> p1 = (Point2D<T>)v(0)->getPosition();
      Point<T,2> p2 = (Point2D<T>)v(1)->getPosition();
      Point<T,2> p3 = (Point2D<T>)v(2)->getPosition();

      T b1 = p1*p1;
      T b2 = p2*p2;
      T b3 = p3*p3;

      Point2D<T> b(b2-b1,b3-b2);
      Point2D<T> a1 = p2 - p1;
      Point2D<T> a2 = p3 - p2;

          c = (0.5/(a1^a2))*
            Point2D<T>(Point2D<T>(a2[1],-a1[1])*b,Point2D<T>(-a2[0],a1[0])*b);
      _triangles(i)->_vorpnt = c;
    }

    int k = 0;
    for (int i=0; i<_triangles.size(); i++) {
      for (int j=0; j<_triangles(i)->getEdges().size(); j++) {
        Array<TSTriangle<T> *> tt = _triangles(i)->getEdges()(j)->getTriangle();

        if (tt.size() > 1) {
          if (tt[0] == _triangles[i]) k=1; else k=0;
          //int m = _triangles.getIndex(tt[k]);
         // std::cout << "triangle found: " << m << "--" << i << std::endl;
          //if (m!=-1)

          //_voredges.insert(TSVEdge<T>(_vorpnts(i),_vorpnts(m)));
          _voredges.insert(TSVEdge<T>(_triangles(i)->_vorpnt,tt[k]->_vorpnt));
        } else {
          // insert a voronoi edge splitting boundary edge
          /*
          Point<T,2> p = _triangles(i)->getEdges()(j)->getCenterPos2D();
          T length = max(T(1),T(2)*(p-_vorpnts(i)).getLength());
        //  int res = _triangles(i)->isAround(new TSVertex<T>(_vorpnts(i)));
          if ((_vorpnts(i)-p).getLength() > T(0)) {
            p = (p-_vorpnts(i))*length+_vorpnts(i);
         // else p = length*(_vorpnts(i)-_triangles(i)->getCenterPos2D())+_vorpnts(i);
            _voredges.insert(TSVEdge<T>(_vorpnts(i),p));
          }
          */
        }
      }
    }

    // Ikke fungerende versjon
    //std::cout << "tiles: " << _tmptiles.size() << std::endl;
    //_tmptiles.setSize(this->size());
    //Box<T,3> domain=getBoundBox();
    //for (int i=0; i<size(); i++)
     // //_triangles[i]->getCenterPos();
     // _tmptiles[i] = new TSTile<float> (&(*this)[i],domain);
  }


  template <typename T>
  inline
  Box<T,3> TriangleFacets<T>::getBoundBox() const	{

    return _box;
  }


  template <typename T>
  inline
  TSEdge<T>* TriangleFacets<T>::getEdge( int i )	const	{

    return _edges(i);
  }


  template <typename T>
  inline
  int TriangleFacets<T>::getNoVertices()	const {

    return this->getSize();
  }


  template <typename T>
  inline
  int TriangleFacets<T>::getNoEdges() const {

    return _edges.getSize();
  }


  template <typename T>
  inline
  int TriangleFacets<T>::getNoTriangles() const {

    return _triangles.getSize();
  }


  template <typename T>
  inline
  TSTriangle<T>* TriangleFacets<T>::getTriangle( int i )	const {

    return _triangles(i);
  }


  template <typename T>
  inline
  TSVertex<T>* TriangleFacets<T>::getVertex( int i )	const	{

    return &this->getElement(i);
  }


  // #ifdef __gmOPENGL_H__

  template <typename T>
  inline
  int TriangleFacets<T>::initRender() {

    if( _dlist_name )
      glDeleteLists( _dlist_name, 1 );

    _dlist_name = glGenLists(1);
    glNewList( _dlist_name, GL_COMPILE );
      glBegin( GL_TRIANGLES );
        for( int i = 0; i < _triangles.size(); i++ )
          _triangles(i)->_render();
      glEnd();
    glEndList();

    Sphere<float,3> s( getVertex(0)->getPos() );
    for( int j = 1; j < this->getSize(); j++ )
      s+= getVertex(j)->getPos();
    setSurroundingSphere(s);

    return _dlist_name;
  }

  // #endif


  template <typename T>
  void TriangleFacets<T>::insertLine( TSLine<T>& pwl ) {

    __e.set(*this);

    bool next;
    int i,j,k,m;
    T s,t,tt;

    for(i=0; i<pwl.getSize()-1; i++)
    {
      insertVertex(pwl[i]);
      j = index(pwl[i]);
      Point2D<T> p  = (*this)[j].getParameter();		// current point
      Point2D<T> np = pwl[i+1].getParameter();		// next new point

      ArrayT<TSEdge<T>*> edges = (*this)[j].getEdges();

      Array<Point2D<T> > pt;						// Find all neighbour points
      for(k=0; k<edges.getSize(); k++)
        pt += edges[k]->otherVertex((*this)[j])->getParameter();
      p.setTestType(3,p,Point2D<T>(0,1));
      pt.sort();									// All points sorted in a circle
      tt = 0;

      do
      {
        UnitVector2D<T> v;
        Vector2D<T> v1 = np - p;

        for(k=0; k<pt.getSize(); k++)				// If the next point is equal one of
          if(np == pt[k]) break;				// the neighbour points continue to
        if(k<pt.getSize()) break;					// the top and insert the new point.

        for(k=0; k<pt.getSize(); k++)				// If the next point is on one of
        {										// the neighbour edges continue to
          m = (k == (pt.getSize()-1))? 0:k+1;	// the top and insert the new point.
          v  = pt[m] - p[k];
          if(std::fabs(v^(np-pt[k])) < POS_TOLERANCE ) break;
        }
        if(k<pt.getSize()) break;

        next = true;

        for(k=0; k<pt.getSize(); k++)
        {
          m = (k == (pt.getSize()-1))? 0:k+1;
          t = 2;

          Vector2D<T> v2 = pt[k] - pt[m];
          Vector2D<T> v3 = pt[k] - p;

          T det = v1^v2;
          if (std::fabs(det) < 1e-15) continue;

          det = 1/det;

          t = -det*(v2.getNormal()*v3);
          s = det*(v1.getNormal()*v3);

          if (t>0 && s>=0 && s<=1)
          {
            v = v2;
            break;
          }
        }
        if (t<1)
          if((v^(np-pt[m])) > POS_TOLERANCE)	// outside all triangles
          {
            tt = tt +(1-tt)*t;
            TSVertex<T> vt = pwl.interpolate(i,tt);///FEILLLL
            vt.setConst();
            insertVertex(vt);
            j = getIndex(vt);
            p  = (*this)[j].getParameter();

            edges = (*this)[j].getEdges();
            pt.clear();						// Find all neighbour points
            for(k=0; k<edges.getSize(); k++)
              pt += edges[k]->otherVertex((*this)[j])->getParameter();
            p.setTestType(3,p,Point2D<T>(0,1));
            pt.sort();						// All points sorted in a circle

            next = false;
          }

      }while(!next);
    }
    insertVertex(pwl[pwl.getSize()-1]);
  }


  template <typename T>
  bool TriangleFacets<T>::insertVertex( TSVertex<T>& v, bool c ) {

    __e.set( *this );

    bool inserted = true;

    int i = getIndex( v );

    if (i<0) {

      insertAlways(v);
      i = this->getSize()-1;
    }
    else
      inserted = false;

    if (!inserted)
    {
      (*this)[i]._set(v);			// Vertex is already a vertex
      return inserted;
    }


    if (c)
      (*this)[i].setConst();

    _set(i);

    return inserted;
  }


  template <typename T>
  inline
  void TriangleFacets<T>::localDisplay() {

    glPushAttrib( GL_LIGHTING_BIT ); {

      if( this->isLighted() )
      {
        this->_material.glSet();
      }
      else
      {
        glDisable( GL_LIGHTING );
        glColor(this->_color);
      }

      render();

    } glPopAttrib();
  }


  template <typename T>
  inline
  void TriangleFacets<T>::localSelect() {

    glBegin( GL_TRIANGLES );
      for( int i = 0; i < _triangles.size(); i++ )
        _triangles(i)->_render();
    glEnd();
  }


  template <typename T>
  bool TriangleFacets<T>::removeVertex( TSVertex<T>& v ) {

    __e.set(*this);

    int id = getIndex(v);
    if( id < 0 ) return false;

    v.deleteEdges();

    ArrayT<TSEdge<T>*> edges = (*this)[this->getSize()-1].getEdges();
    for ( int i=0; i < edges.getSize(); i++ )
      edges[i]->swapVertex((*this)[this->getSize() - 1],(*this)[id]);

    return this->removeIndex(id);
  }


  template <typename T>
  bool TriangleFacets<T>::removeVertexNew( TSVertex<T>& v ) {

    Array<TSEdge<T>*>   o_edges = v.getOuterEdges();

    removeVertex(v);

    return fillPolygon( o_edges );
  }


 // #ifdef __gmOPENGL_H__

  template <typename T>
  inline
  void TriangleFacets<T>::render() {

    if( !_dlist_name )
      initRender();

    glCallList( _dlist_name );
  }

  template <typename T>
  inline
  void TriangleFacets<T>::renderVoronoi() {

  // /*
    glDisable(GL_LIGHTING);
    glPointSize(2.0f);
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    glColor3f(1.0f,0.0f,0.0f);
    for (int j=0; j<_vorpnts.size(); j++) {
      Point<T,2> c = _vorpnts(j);
      glVertex2f(c[0],c[1]);
    }
    glEnd();
    //glDisable(GL_POINT_SMOOTH);
    //*/

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    for (int i=0; i<_voredges.size(); i++) { // i+=2) {
      glColor3f(1.0f,0.0f,0.0f);
      glVertex2f(_voredges(i)(0)(0), _voredges(i)(0)(1));
      glVertex2f(_voredges(i)(1)(0), _voredges(i)(1)(1));
    }
    glEnd();
    glDisable(GL_POINT_SMOOTH);

    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 1.0f);
  /*  for (int k=0; k<_vec.size(); k++) {
      glVertex3f(0.0f,0.0f,0.0f);
      glVertex3f(_vec(k)(0),_vec(k)(1),0.0f);

    }*/
    glEnd();

    /*
    for (int h=0; h<_triangles.size(); h++) {
      Point<float,2> p;
      p[0] = _triangles(h)->getVertices()(0)->getPosition()(0);
      p[1] = _triangles(h)->getVertices()(0)->getPosition()(1);
      float r = (_vorpnts(h) - p).getLength();
      double a; int n = 36;
      glBegin(GL_LINE_LOOP);
        glColor3f(0.0f,0.0f,1.0f);
        for (int s=0;s<n;s++) {
          a = ((double)s*2.0*3.14)/((double)n);
          float x = r * cos(a) + _vorpnts(h)(0);
          float y = r * sin(a) + _vorpnts(h)(1);
          glVertex2f(x,y);
        }
      glEnd();
    }
    */




  //  glEnable(GL_LIGHTING);
    // rendring av ikke fungerende versjon
  /*	for (int i=0;i<_tmptiles.size();i++)
      _tmptiles[i]->render();*/
  }

 // #endif


  template <typename T>
  bool TriangleFacets<T>::setConstEdge( TSVertex<T> v1, TSVertex<T> v2 ) {

    int i;

    for( i=0; i < getNoEdges(); i++ ) {
      if(
        (*(getEdge(i)->_vertex[0]) == v1 && (*getEdge(i)->_vertex[1]) == v2) ||
        (*(getEdge(i)->_vertex[0]) == v2 && (*getEdge(i)->_vertex[1]) == v1)
      ) {

        getEdge(i)->setConst();
        return true;
      }
    }

    return false;
  }


  template <typename T>
  void TriangleFacets<T>::triangulateDelaunay() {

    __e.set( *this );

    int i,j;

    if( this->getSize() < 3 ) return;

    ArrayLX<TSVertex<T> >& vertex = *this;

    // Set the size of edge and triangle array to the upper bound.
    // Remember that there is only 3 outer edges.

    _edges.setMaxSize(3* this->getSize()+3);
    _triangles.setMaxSize(2* this->getSize()+1);

    // Make surrounding box and tree new vertices

    _box.reset(vertex[0].getPosition());

    for (i=1; i<vertex.getSize(); i++)
      _box += vertex[i].getPosition();

    double dx	  = _box.getValueDelta(0);
    double dy	  = _box.getValueDelta(1);
    double delta  = dx>dy?dx:dy;

    TSVertex<T> p1(_box.getValueMin(0) - delta,   _box.getValueMin(1) - delta);
    TSVertex<T> p2(_box.getValueMax(0) + 3*delta, _box.getValueMin(1) - delta);
    TSVertex<T> p3(_box.getValueMin(0) - delta,   _box.getValueMax(1) + 3*delta);

    vertex += p1;
    vertex += p2;
    vertex += p3;

    // Make tree Edges.

    _edges += new TSEdge<T>(vertex[vertex.getSize()-3], vertex[vertex.getSize()-2]);
    _edges += new TSEdge<T>(vertex[vertex.getSize()-2], vertex[vertex.getSize()-1]);
    _edges += new TSEdge<T>(vertex[vertex.getSize()-1], vertex[vertex.getSize()-3]);

    // Make a triangle.

    _triangles += new TSTriangle<T>(_edges[0],_edges[1],_edges[2]);

    _edges[0]->_setTriangle(_triangles[0],NULL);
    _edges[1]->_setTriangle(_triangles[0],NULL);
    _edges[2]->_setTriangle(_triangles[0],NULL);

    //**********************************************************************
    // Here we constuct the dervided structure for speeding up the algoritm
    //**********************************************************************

    if(this->getSize() < 200)			_d = 2;
    else if(this->getSize() < 800)		_d = 3;
    else if(this->getSize() < 3200)		_d = 4;
    else if(this->getSize() < 12800)		_d = 5;
    else if(this->getSize() < 51200)		_d = 6;
    else if(this->getSize() < 204800)	_d = 7;
    else						_d = 8;

    int n = 1 << _d;

    _tri_order.setDim(n,n);
    _u.setMaxSize(n+1);
    _v.setMaxSize(n+1);

    for(i=0; i<= n; i++)
    {
      _u += _box.getValueMin(0) + i*_box.getValueDelta(0)/n;
      _v += _box.getValueMin(1) + i*_box.getValueDelta(1)/n;
    }

    for(i=0; i< n; i++)
      for(j=0; j< n; j++)
      {
        _tri_order[i][j].setMaxSize(20);//,10);
        _tri_order[i][j] += _triangles[0];
      }

    //*****************************************************
    // End dervided structure for speeding up the algoritm
    //*****************************************************


    // Go through all vertices and if a vertex is on an edge split the edge
    // and the two neighbour triangles, or if the vertex is inside one triangle
    // split the triangle into tree treangles.

    for ( i = 0; i < vertex.getSize()-3; i++ ) _set(i);

    // remove constructed outer triangles

    _removeLastVertex();
    _removeLastVertex();
    _removeLastVertex();

    // Insert Edges and Triangles to make a convecs boundary

    int n_bound=0;
    for(i=0; i< _edges.getSize(); i++)
      if(_edges[i]->boundary())
      {
        n_bound++;
        TSTriangle<T>* t = _edges[i]->_getOther(NULL);
        t->_reverse(_edges[i]);
        Array<TSEdge<T>*> edges = t->getEdges();
        if( _edges[i]->_isFirst( _edges[i]->getCommonVertex(*edges[1]) ) )
          _edges[i]->_reverse();
      }

    for(i=0; i< _edges.getSize(); i++)
      if( _edges[i]->boundary() )
        break;

    TSEdge<T> *a = _edges[i];
    TSEdge<T> *b = a->_getNext();


    for(i=0; i<n_bound;i++)
    {
      Vector2D<T>		v = a->getVector2D();
      UnitVector2D<T>	u = v + b->getVector2D();
      if((u^v) > POS_TOLERANCE) {

        TSEdge<T> *ne = new TSEdge<T>(*(a->getFirstVertex()),*(b->getLastVertex()));
        TSTriangle<T> *nt = new TSTriangle<T>(ne,b,a);
        a->_swapTriangle(NULL,nt);
        b->_swapTriangle(NULL,nt);
        ne->_setTriangle(nt,NULL);
        _edges += ne;
        _insertTriangle(nt);
        a = ne;
        b = a->_getNext();
        i--;
      }
      else
      {
        a = b;
        b = a->_getNext();
      }
    }
  }







  //#if defined GM_STREAM
  //
  //
  //
  //template <typename T>
  //inline
  //int TriangleFacets<T>::getStreamMode() const {
  //
  //  return _stream_mode;
  //}
  //
  //
  //template <typename T>
  //inline
  //void TriangleFacets<T>::setStreamMode( int i = 1 ) {
  //
  //  _stream_mode = i;
  //}
  //
  //
  //template <typename T>
  //inline
  //void TriangleFacets<T>::print( string prompt = " TriangleFacets<T>", ostream& out = cout ) const {
  //
  //  out << prompt << ": " << (*this) << "\n";
  //}
  //
  //
  //template <typename T>
  //ostream& TriangleFacets<T>::_prOut(ostream& out) const {
  //
  //	const ArrayLX< TSVertex<T> >& vertex = *this;
  //	if( _stream_mode == 1 || _stream_mode == 4 || _stream_mode == 5 || _stream_mode == 7 )
  //		out << vertex << endl << endl;
  //	if( _stream_mode == 2 || _stream_mode == 4 || _stream_mode == 6 || _stream_mode == 7 )
  //		out << _edge << endl;
  //	if( _stream_mode == 3 || _stream_mode == 5 || _stream_mode == 6 || _stream_mode == 7 )
  //		out << _triangle << endl;
  //	return out;
  //}
  //
  //
  //template <typename T>
  //istream& TriangleFacets<T>::_prIn(istream& in) {
  //
  //	__e.set(*this);
  //
  //	ArrayLX<TSVertex<T> >& vertex = *this;
  //
  //	if( _stream_mode == 1 || _stream_mode == 4 || _stream_mode == 7 ) {
  //
  //		int n , mark = in.tellg();
  //		in >> n;
  //		in.seekg(mark);
  //		vertex.setMax(n+3);
  //		in >> vertex;
  //	}
  //	if( _stream_mode == 4 || _stream_mode == 7 )
  //		in >> _edge;
  //	if( _stream_mode == 7 )
  //		in >> _triangle;
  //	if( _stream_mode == 2 || _stream_mode == 3 || _stream_mode == 5 || _stream_mode == 6 )
  //	{
  //		// Error message
  //	}
  //	return in;
  //}
  //
  //
  //
  //#endif

}

