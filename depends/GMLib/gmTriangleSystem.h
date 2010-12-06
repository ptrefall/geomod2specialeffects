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



/*! \file gmTriangleSystem.h
 *
 *  Interface of the Triangle system classes.
 *
 *  \date   2008-10-21
 */



#ifndef __gmTRIANGLESYSTEM_H__
#define __gmTRIANGLESYSTEM_H__




#include "gmPoint3D.h"
#include "gmPoint2D.h"
#include "gmArray.h"
#include "gmArrayT.h"
#include "gmArrayLX.h"
#include "gmSArray.h"
#include "gmDMatrix.h"

#include "gmDisplayObject.h"



namespace GMlib {

  template <typename T>
  class TriangleFacets;

  template <typename T>
  class TriangleSystem;

  template <typename T>
  class TSVertex;

  template <typename T>
  class TSEdge;

  template <typename T>
  class TSTriangle;

  template <typename T>
  class TSTile;

  template <typename T>
  class TSLine;

  template <typename T>
  class TSVEdge;


  /** \class  TriangleFacets gmTriangleSystem.h <gmTriangleSystem>
   *  \brief  The storage class of the Triangle system
   *
   *  This is the main class. Here you can make, adjust
   *  and handle a triangle based surface. The class is also
   *  the storage class for the vertices, edges and triangles
   */
  template <typename T>
  class  TriangleFacets : public ArrayLX< TSVertex<T> >, public DisplayObject {
   public:

    TriangleFacets( int d = 0 );
    TriangleFacets( const ArrayLX<TSVertex<T> >& v);
    ~TriangleFacets();



    Point<T,3>                        eval(T x, T y, int deg=1) const;
    Point<T,3>                        eval(const Point2D<T>& p, int deg=1) const;


    T                                 evalZ(const Point2D<T>&, int deg=1); //const
    T                                 evalZ(T x, T y, int deg=1);

    void                              clear(int d=-1);
    void                              computeNormals();

    void                              createVoronoi();
    Box<T,3>                          getBoundBox() const;

    TSEdge<T>*                        getEdge(int i) const;
    int                               getNoVertices() const;
    int                               getNoEdges() const;
    int                               getNoTriangles() const;

    TSTriangle<T>*                    getTriangle(int i) const;
    TSVertex<T>*                      getVertex(int i) const;

    int                               initRender(); //const;

    void                              insertLine( TSLine<T>& );
    bool                              insertVertex( TSVertex<T>&, bool c = false );
    bool                              removeVertex( TSVertex<T>& v );
    bool                              removeVertexNew( TSVertex<T>& v);

    void                              render(); // const;
    void                              renderVoronoi();

    bool                              setConstEdge(TSVertex<T> v1, TSVertex<T> v2);

    void                              triangulateDelaunay();

   protected:
    int	                              _dlist_name;

    void                              localDisplay();
    void                              localSelect();


  private:
    ArrayLX< TSEdge<T>* >             _edges;
    ArrayLX< TSTriangle<T>* >         _triangles;
    Array< TSTile<T> *>               _tmptiles;
    Array<TSVEdge<T> >                _voredges;
    Array<Point<T,2> >                _vorpnts;

    int                               _d;

    DMatrix<ArrayT<TSTriangle<T>*> >  _tri_order;
    ArrayT<T>                         _u;
    ArrayT<T>                         _v;
    Box<T,3>                          _box;

   TSVertex<T>                        __v;		// dummy because of MS-VC++ compiler
   TSEdge<T>                          __e;		// dummy because of MS-VC++ compiler
   TSTriangle<T>                      __t;		// dummy because of MS-VC++ compiler

    bool                              _fillPolygon(Array<TSEdge<T>*>&);
    bool                              _removeLastVertex();;
    void                              _set(int i);
    int                               _surroundingTriangle(TSTriangle<T>*&, const TSVertex<T>&);// const;


  friend class TriangleSystem<T>;
  private:
    void                              _adjustTriangle( TSTriangle<T>*, bool wider = false );
    ArrayLX<TSEdge<T>* >&             _getEdges();
    TSVertex<T>*                      _find( const Point<T,3>& ) const;
    TSEdge<T>*                        _find( const Point<T,3>&, const Point<T,3>& ) const;
    void                              _insertTriangle( TSTriangle<T>* );
    void                              _removeTriangle( TSTriangle<T>* );
    ArrayLX<TSTriangle<T>* >&         _triangle();



  #if defined GM_STREAM


//  public:
//    int  getStreamMode() const;
//    void print( string prompt = " TriangleFacets<T>", ostream& out = std::cout ) const;
//    void setStreamMode( int i = 1 );
//
//    friend ostream& operator<<(ostream& out, const  TriangleFacets<T>& v) {
//      return v._prOut(out);
//    }
//    friend ostream& operator<<(ostream& out, const  TriangleFacets<T>* v) {
//      return v->_prOut(out);
//    }
//    friend istream& operator>>(istream& in,  TriangleFacets<T>& v) {
//      return istream >> v;
//    }
//    friend istream& operator>>(istream& in,  TriangleFacets<T>* v) {
//      return v->_prIn(in);
//    }
//
//
//  private:
//    int _stream_mode;
//
//    ostream& _prOut(ostream& out) const;
//    istream& _prIn(istream& in);

  #endif
  };



  /** \class TriangleSystem gmTriangleSystem.h <gmTriangleSystem>
   *  \brief The TriangleSystem base class
   *
   *  The base class for vertices, edges and triangles
   */
  template <typename T>
  class TriangleSystem {
  public:
    void                        set( TriangleFacets<T>& ts );

  protected:
    void                        adjust( TSTriangle<T> *t, bool wider = false );
    TSVertex<T>*                find( const Point<T,3>& p ) const;
    TSEdge<T>*                  find( const Point<T,3>& p1, const Point<T,3>& p2 );

//    int                         getStreamMode();

    void                        insert( TSEdge<T> *e );
    void                        insert( TSTriangle<T> *t );
    void                        remove( TSEdge<T> *e );
    void                        remove( TSTriangle<T> *t );


  private:
    static TriangleFacets<T>    *_tv;
  };

  /** \class VEdge
   *  \brief The Voronoi Edge class
   *
   *  Simple class containing the two voronoi points
  */
  template <typename T>
  class TSVEdge {
  public:
	  TSVEdge();
	  TSVEdge(const Point<T,2> &p, const Point<T,2> &q);
	  

	  bool operator==(const TSVEdge<T> &e) const;
	  bool operator<(const TSVEdge<T> &e) const;
	  Point<T,2> const &operator() (int i) const;
  private:
	  Point<T,2> _pnts[2];
  };


  /** \class  TSVertex
   *  \brief  The TSVertex class
   *
   *  The vertex class storing 3D position and a normal
   */
  template <typename T>
  class TSVertex : public Arrow<T,3>, public TriangleSystem<T> {
  public:
    TSVertex();
    TSVertex( const Point<T,2>& v );
    TSVertex( const Point<T,3>& p );
    TSVertex( const Point<T,3>& p, const Vector<T,3>& n );
    TSVertex( const T& x, const T& y, const T& z = T() );
    ~TSVertex();


    bool                    boundary() const;
    Arrow<T,3>              getArrow();
    ArrayT<TSEdge<T>*>&	    getEdges();
    Point<T,3>              getNormal() const;
    Array<TSEdge<T>*>       getOuterEdges() const;
    Point<T,2>              getParameter() const;
    Point<T,3>              getPosition() const;
    T                       getRadius();
    T                       getRadiusMax();
    T                       getRadiusMin();
    Array<TSTriangle<T>*>   getTriangles() const;

    bool                    isConst()	const;
    int                     isInside( TSTriangle<T>* ) const;

    void                    setConst( bool c = true );
    void                    setRadius( T r );
    void                    setRadiusMax( T r );
    void                    setRadiusMin( T r );
    void                    setZ( T z );

    TSVertex<T>&            operator=(const TSVertex<T>& t);
    bool                    operator==(const TSVertex<T>& t)	const;
    bool                    operator<(const TSVertex<T> &t) const;



  private:

    T                       _radius;
    T                       _maxradius;
    T                       _minradius;
    ArrayT<TSEdge<T>*>      _edges;

    bool                    _const;


    void                    _set( const Point<T,3>& p, const Vector<T,3>& n );


  friend class TSEdge<T>;
  friend class TriangleFacets<T>;
  private:
    void                    _computeNormal();
    void                    _deleteEdges();
    bool                    _insertEdge(TSEdge<T>* e);
    bool                    _removeEdge(TSEdge<T>* e);
    void                    _set( const TSVertex<T>& v );


//  #if defined GM_STREAM
//
//
//  public:
//    friend ostream&       operator<<(ostream& out, const TSVertex<T>& v) { return v._prOut(out); }
//    friend ostream&       operator<<(ostream& out, const TSVertex<T>* v) { return v->_prOut(out); }
//    friend istream&       operator>>(istream& in, TSVertex<T>& v)	{ return v._prIn(in); }
//    friend istream&       operator>>(istream& in, TSVertex<T>* v)	{ return v->_prIn(in); }
//
//    void                  print(char prompt[]="TSVertex<T>", ostream & out = std::cout) const
//    { out << prompt << ": " << (*this) << "\n"; }
//
//  private:
//    ostream&              _prOut(ostream& out)const;
//    istream&              _prIn(istream& in);
//
//  #endif

  };



  /** \class TSEdge gmTriangleSystem.h <gmTriangleSystem>
   *  \brief The TSEdge class
   *
   *  The edge class defined by 2 vertices, can be fixed
   */
  template <typename T>
  class TSEdge : public TriangleSystem<T> {
  public:
    TSEdge();
    TSEdge(TSVertex<T>& s, TSVertex<T>& e);
    TSEdge(const TSEdge<T>& e);
    ~TSEdge();

    bool                    boundary() const;
    TSVertex<T>*            getCommonVertex(const TSEdge<T>&) const;
    TSVertex<T>*            getFirstVertex() const;
    Point<T,3>              getCenterPos();
    Point<T,2>              getCenterPos2D();
    T                       getLength();
    T                       getLength2D();
    Array<TSTriangle<T>*>   getTriangle();
    Vector<T,3>             getVector();
    Vector2D<T>             getVector2D();
    TSVertex<T>*            getLastVertex() const;
    TSVertex<T>*            getOtherVertex(const TSVertex<T>&) const;
    void                    setConst(bool c = true);

    bool                    operator <  (const TSEdge<T>& v) const;
    bool                    operator >  (const TSEdge<T>& v) const;
    bool                    operator <= (const TSEdge<T>& v) const;
    bool                    operator >= (const TSEdge<T>& v) const;


  private:
    TSVertex<T>             *_vertex[2];
    TSTriangle<T>           *_triangle[2];
    bool                    _const;

    bool                    _swap();
    void                    _upv();


  friend class TSTriangle<T>;
  friend class TriangleFacets<T>;
  private:

    TSEdge<T>*              _getNext();
    bool                    _hasPoints(const Point<T,3>& , const Point<T,3>&) const;
    bool                    _isFirst(TSVertex<T>* v);
    bool                    _isLast(TSVertex<T>* v);

    void                    _okDelaunay();

    TSTriangle<T>*          _getOther(TSTriangle<T>*);
    bool                    _removeTriangle(TSTriangle<T>*);
    void                    _reverse();
    void                    _setTriangle(TSTriangle<T>* t1,TSTriangle<T>* t2);
    bool                    _split( TSVertex<T>& p );
    bool                    _swapTriangle(TSTriangle<T>* ot, TSTriangle<T>* nt);
    bool                    _swapVertex(TSVertex<T>& is_v,TSVertex<T>& new_v);



//  #if defined GM_STREAM
//  private:
//    ostream& _prOut(ostream& out)const;
//    istream& _prIn(istream& in);
//  public:
//
//    friend ostream& operator<<(ostream& out, const TSEdge<T>& v);
//    friend ostream& operator<<(ostream& out, const TSEdge<T>* v);
//    friend istream& operator>>(istream& in, TSEdge<T>& v);
//    friend istream& operator>>(istream& in, TSEdge<T>* v);
//
//    void print(char prompt[]="TSEdge<T>", ostream & out = std::cout) const;
//  #endif
  };



  /** \class  TSTriangle gmTriangleSystem.h <gmTriangleSystem>
   *  \brief  The TriangleSystem Trangle class
   *
   *  The triangle class defined by 3 edges
   */
  template <typename T>
  class TSTriangle: public TriangleSystem<T> {
  public:
    TSTriangle();
    TSTriangle( TSEdge<T>* e1, TSEdge<T>* e2, TSEdge<T>* e3 );
    TSTriangle( const TSTriangle<T>& t );
    ~TSTriangle();


    T                       getAngleLargest();
    T                       getAngleSmallest();
    T                       getArea();
    T                       getArea2D();

    Point<T,3>              getCenterPos();
    Point<T,2>              getCenterPos2D();
    T                       getCircum();
    T                       getCircum2D();

    Array<TSEdge<T>*>       getEdges() const;
    Vector<T,3>             getNormal() const;
    Array<TSVertex<T>*>     getVertices() const;
    int	                    isAround(const TSVertex<T>& v) const;



  private:
    TSEdge<T>               *_edge[3];
    Box<unsigned char,2>    _box;



  friend class TSEdge<T>;
  friend class TriangleFacets<T>;
    Point<T,2>              _vorpnt;
  private:

    T                       _evalZ( const Point2D<T>& p, int deg = 1 ) const;
    Box<unsigned char,2>&   _getBox();
    void                    _render();//  const;
    bool                    _reverse( TSEdge<T>* edge );
    void                    _setEdges( TSEdge<T>* e1, TSEdge<T>* e2, TSEdge<T>* e3 );
    bool                    _split( TSVertex<T>& p );
    void                    _updateBox( ArrayT<T>& u, ArrayT<T>& v, int d );



//  #if defined GM_STREAM
//  public:
//    friend ostream& operator << ( ostream& out, const TSTriangle<T>& v );
//    friend ostream& operator << ( ostream& out, const TSTriangle<T>* v );
//    friend istream& operator >> ( istream& in, TSTriangle<T>& v );
//    friend istream& operator >> ( istream& in, TSTriangle<T>* v );
//
//    void print( char prompt[] = "TSTriangle<T>", ostream & out = std::cout ) const;
//
//  private:
//    ostream& _prOut( ostream& out )const;
//    istream& _prIn( istream& in );
//  #endif
  };



  /** \class  TSTile gmTriangleSystem.h <gmTriangleSystem>
   *  \brief  The TSTile class
   *
   *  The tile class defined by vertex, and dual of its triangles
   */
  template <typename T>
  class TSTile : public DisplayObject {
  public:
    TSTile();
    TSTile( TSVertex<T>* v, Box<T,3> domain );

    T                     getBigR();
    std::string           getIdentity() const;
    T                     getSmallR();
    void                  render();

  protected:
    void                  localDisplay();
    void                  localSelect();

  private:
    Array< Point<T,2> >   _vorpts;
    TSVertex<T>           *_vertex;
    T                     _inscribed;
    T                     _circumscribed;

    Point2D<T>            _voronoi( const Point2D<T>& v1, const Point2D<T>& v2, const Point2D<T>& v3 );
  };



  /** \class  TSLine gmTriangleSystem.h <gmTriangleSystem>
   *  \brief  The TSLine class
   *
   *  TSLine
   */
  template <typename T>
  class TSLine : public Array< TSVertex<T> > {
  public:
    TSLine( int d = 0);
    TSLine( const Array<TSVertex<T> >& v );

    TSVertex<T>     interpolate( int i, double t ) const;
  };


} // end namespace




// Include TriangleFacets class function implementations
#include "gmTriangleSystem_TriangleFacets.c"

// Include TriangleSystem class function implementations
#include "gmTriangleSystem_TriangleSystem.c"

// Include TriangleSystem Vertex class function implementations
#include "gmTriangleSystem_TSVertex.c"

// Include TriangleSystem Edge class function implementations
#include "gmTriangleSystem_TSEdge.c"

// Include TriangleSystem Triangle class function implementations
#include "gmTriangleSystem_TSTriangle.c"

// Include TriangleSystem Tile class function implementations
#include "gmTriangleSystem_TSTile.c"

// Include TriangleSystem Line class function implementations
#include "gmTriangleSystem_TSLine.c"

// Include TriangleSystem Voronoi Edge class function implementations
#include "gmTriangleSystem_TSVEdge.c"



#endif // __gmTRIANGLESYSTEM_H__


