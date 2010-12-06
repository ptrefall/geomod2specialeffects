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



/*! \file gmTriangleSystem_TSTile.c
 *  \brief TSTile class function implementations
 *
 *  \date   2008-10-24
 */


namespace GMlib {



  template <typename T>
  inline
  TSTile<T>::TSTile() {}


  template <typename T>
  inline
  TSTile<T>::TSTile( TSVertex<T>* v, Box<T,3> domain ) {

    _vertex = v;

    Array<TSEdge<T> *> edges;
    edges = v->getEdges();

    Array<TSTriangle<T> *> triangles = v->getTriangles();
    for( int i = 0; i < triangles.getSize(); i++ ) {

      Array<TSVertex<T>* > vertices = triangles[i]->getVertices();

      if(vertices[0] != _vertex)
        swap( vertices[0], vertices[1]);

      if(vertices[0] != _vertex)
        swap(vertices[0],vertices[2]);

      Point<T,2> t;
      t = _voronoi(vertices[0]->getParameter(), vertices[1]->getParameter(), vertices[2]->getParameter());

      if( domain.isSurrounding( Point3D<T>(t[0],t[1],0.2) ) )
        _vorpts.insertAlways(t);
    }

    for( int i = 0; i < edges.getSize(); i++ )
		if(edges(i)->boundary()) _vorpts.insertAlways( edges(i)->getCenterPos2D() );


    // make polygon, maybe edges should have been sorted first
    _vorpts[0].setTestType( 3, _vertex->getPosition(), Vector2D<T>(0.0,1.0) );
//    _vorpts.sort();
///////////
    _circumscribed=0.0;
    _inscribed=1.0E9;
    // for(int i=0; i<vorpts.size(); i++)
    // {
    //	 Vector2D<T> tmp=(vorpts[i]-myvtx->parameter());
    //	 if (tmp.length()>circumscribed) circumscribed=tmp.length()*1.00;
    // }
    for( int i = 0; i< edges.getSize(); i++ )
      if( edges(i)->getLength2D()*1.0 < _inscribed )
        _inscribed = (edges(i)->getLength2D())*1.0; // smallest

    for( int i = 0; i < edges.getSize(); i++ )
      if( edges(i)->getLength2D()*1.0 > _circumscribed )
        _circumscribed = ( edges(i)->getLength2D())*1.0; // largest
///////////////////////
    setSurroundingSphere( Sphere<T,3>( (Point<T,3>)_vertex->getParameter(), _circumscribed ) );
  }


  template <typename T>
  inline
  Point2D<T> TSTile<T>::_voronoi( const Point2D<T>& v1, const Point2D<T>& v2, const Point2D<T>& v3 ) {

    Vector2D<T> d1 = v2 - v1;
    Vector2D<T> d2 = v3 - v1;
    Vector2D<T> d3 = v3 - v2;
    d1 = d2 - ((d1*d2)/(d1*d1))*d1;
    return 0.5*(v1+v2 + ((d3*d2)/(d1*d2))*d1);
  }


  template <typename T>
  inline
  T TSTile<T>::getBigR() {

    return _circumscribed;
  }


  template <typename T>
  inline
  std::string TSTile<T>::getIdentity() const {

    return "TSTile";
  }


  template <typename T>
  inline
  T TSTile<T>::getSmallR() {

    return _inscribed;
  }


  template <typename T>
  inline
  void TSTile<T>::localDisplay() {

    render();
  }


  template <typename T>
  inline
  void TSTile<T>::localSelect() {

    glBegin( GL_LINE_STRIP ); {

      //glBegin(GL_TRIANGLE_FAN);
      //glVertex((Point3D<T>)myvtx->parameter());
      for( int i = 0; i < _vorpts.getSize(); i++ )
        glVertex( (Point3D<T>)_vorpts(i) );

      if( !_vertex->boundary() )
        glVertex( (Point3D<T>)_vorpts(0) );

    } glEnd();
  }


  template <typename T>
  inline
  void TSTile<T>::render() {

    glPushAttrib( GL_LIGHTING_BIT ); {
      glBegin(GL_LINE_STRIP); {

        for( int i=0; i<_vorpts.size(); i++ )
          glVertex( (Point3D<T>)_vorpts(i) );

        if(!_vertex->boundary())  glVertex((Point3D<T>)_vorpts(0));

      }glEnd();
    }glPopAttrib();
  }

}

