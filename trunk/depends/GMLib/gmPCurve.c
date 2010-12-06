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



/*! \file gmPCurve.c
 *
 *  Implementation of the PCurve template class.
 *
 *  \date   2008-09-09
 */


namespace GMlib {


  template <typename T>
  inline
  PCurve<T>::PCurve( int s ) {

    _no_sam           = s;
    _no_der           = 1;
    _d                = -1;
    _tr               = T(0);
    _sc               = T(1);

    setNoDer(2);

    this->_lighted    = false;
    _line_width       = 1.0;

    _default_visualizer = new PCurveVisualizer<T>();
    enableDefaultVisualizer( true );
  }


  template <typename T>
  inline
  PCurve<T>::PCurve( const PCurve<T>& copy ) : Parametrics<T,1>( copy ) {


    _no_sam       = copy._no_sam;
    _no_der       = copy._no_der;

    _p            = copy._p;
    _t            = copy._t;
    _d            = copy._d;
    _tr           = copy._tr;
    _sc           = copy._sc;


    _line_width   = copy._line_width;

    setNoDer(2);

    _default_visualizer = new PCurveVisualizer<T>();
    enableDefaultVisualizer( true );
  }

  template <typename T>
  PCurve<T>::~PCurve() {

    enableDefaultVisualizer( false );
    delete _default_visualizer;
  }



  template <typename T>
  inline
  void	PCurve<T>::_eval( T t, int d ) {

    if( !(d <=_d &&  t ==_t) ) {

      _t = t; _d = d;
      eval( shift(t), d );
    }
  }


  template <typename T>
  inline
  void PCurve<T>::_evalDerDD( DVector< DVector< Vector<T, 3> > > & p, int d, T du ) const {



    T one_over_du = T(1) / du;
    T one_over_2du = T(1) / ( T(2) * du );

    int u, i, k;

    for( u = 1; u < d; u++ ) {
      for( i = 1; i < p.getDim() - 1; i++ ) {
        for( k = 0; k < 3; k++ )
          p[i][u][k] = p[i+1][u-1][k] - p[i-1][u-1][k];

        p[i][u] *= one_over_2du;
      }
    }

    if( isClosed() ) {
      for( u = 1; u < d; u++ ) {
        for( k = 0; k < 3; k++ )
          p[0][u][k] = p[p.getDim()-1][u][k] = p[1][u-1][k] - p[p.getDim() - 2][u-1][k];

        p[0][u] = p[p.getDim()-1][u] *= one_over_2du;
      }
    }
    else {
      for( u = 1; u < d; u++ ) {
        for( k = 0; k < 3; k++ ) {
          p[0][u][k] = p[1][u-1][k] - p[0][u-1][k];
          p[p.getDim()-1][u][k] = p[p.getDim()-1][u-1][k] - p[p.getDim()-2][u-1][k];

        }

        p[0][u] *= one_over_du;
        p[p.getDim()-1][u] *= one_over_du;
      }
    }
  }

  template <typename T>
  void PCurve<T>::enableDefaultVisualizer( bool enable ) {

    if( !enable )
      removeVisualizer( _default_visualizer );
    else
      insertVisualizer( _default_visualizer );
  }


  template <typename T>
  DVector<Vector<T,3> >& PCurve<T>::evaluate( T t, int d ) {

    _eval(t,d);
    return _p;
  }


  template <typename T>
  DVector<Vector<T,3> >& PCurve<T>::evaluateGlobal( T t, int d ) {

    static DVector< Vector<T,3> > p;
    p.setDim(d+1);
    _eval(t,d);

    p[0] = this->_present*((Point<T,3>)_p[0]);

    for( int i = 1; i <= d; i++ )
      p[i] = this->_present * (Vector<T,3>)_p[i];

    return p;
  }


  template <typename T>
  DVector<Vector<T,3> >& PCurve<T>::evaluateParent( T t, int d ) {

    static DVector< Vector<T,3> > p;
    p.setDim(d+1);
    _eval(t,d);

    p[0] = this->_matrix*((Point<T,3>)_p[0]);

    for( int i = 1; i <= d; i++ )
      p[i] = this->_matrix * (Vector<T,3>)_p[i];

    return p;
  }


  template <typename T>
  inline
  T PCurve<T>::getCurvature( T t ) {

    _eval( t, 2 );
    Vector<T,3> d1 = _p[1];
    T a1= d1.getLength();

    if( a1 < T(1.0e-5) )
      return T(0);

    d1 /= a1;

    Vector<T,3> d2 = ( _p[2] - ( d1 * _p[2] ) * d1 ) / ( a1 * a1 );

    return d2.getLength();
  }


  template <typename T>
  inline
  T PCurve<T>::getCurveLength( T a , T b ) {

    if(b<a)	{

      a = getParStart();
      b = getParEnd();
    }

    return _integral( a, b, 1e-10 );
  }


  template <typename T>
  inline
  int PCurve<T>::getDerivatives() const {

    return _no_der;
  }


  template <typename T>
  inline
  Vector<T,3> PCurve<T>::getDer1( T t ) {

    eval( t, 1 );
    return _p[1];
  }


  template <typename T>
  inline
  Vector<T,3> PCurve<T>::getDer2( T t ) {

    _eval(t,2);
    return _p[2];
  }


  template <typename T>
  inline
  std::string PCurve<T>::getIdentity() const {

    return "PCurve";
  }

  template <typename T>
  inline
  float PCurve<T>::getLineWidth() const {

    return _line_width;
  }


  template <typename T>
  inline
  T PCurve<T>::getLocalMapping( T t, T /*ts*/, T /*ti*/, T /*te*/ ) {

    return t;
  }


  template <typename T>
  inline
  T PCurve<T>::getParDelta()	{

    return _sc*( getEndP() - getStartP() );
  }


  template <typename T>
  inline
  T PCurve<T>::getParEnd() {

    return getParStart() + getParDelta();
  }


  template <typename T>
  inline
  T PCurve<T>::getParStart()	{

    return getStartP() + _tr;
  }


  template <typename T>
  inline
  T PCurve<T>::getRadius( T t ) {

    return T(1) / getCurvature( t );
  }


  template <typename T>
  inline
  int PCurve<T>::getSamples() const {

    return _no_sam;
  }


  template <typename T>
  inline
  T PCurve<T>::getSpeed( T t ) {

    return getDer1( t ).getLength();
  }

  template <typename T>
  inline
  void PCurve<T>::insertVisualizer( Visualizer* visualizer ) {

    PCurveVisualizer<T> *visu = dynamic_cast<PCurveVisualizer<T>*>( visualizer );
    if( !visu )
      return;

    if( _pcurve_visualizers.exist( visu ) )
      return;

    _pcurve_visualizers += visu;

    SceneObject::insertVisualizer( visualizer );
  }


  template <typename T>
  inline
  bool PCurve<T>::isClosed() const {

    return false;
  }


  template <typename T>
  inline
  void PCurve<T>::preSample( int /*m*/, int /*d*/, T /*s*/, T /*e*/ ) {}


  template <typename T>
  void PCurve<T>::replot( int m, int d ) {


    // Correct sample domain
    if( m < 2 )
      m = _no_sam;
    else
      _no_sam = m;

    // Correct derivatives
    if( d < 1 )
      d = _no_der;
    else
      _no_der = d;


    // pre-sampel / pre evaluate data for a given parametric curve, if wanted/needed
    preSample( m, 1, getStartP(), getEndP() );

    // Resample
    DVector< DVector< Vector<T, 3> > > p;
    resample( p, m, 1, getStartP(), getEndP() );

    // Set The Surrounding Sphere
    setSurroundingSphere( p );


    // Replot Visaulizers
    for( int i = 0; i < this->_pcurve_visualizers.getSize(); i++ )
      this->_pcurve_visualizers[i]->replot( p, m, d );
  }

  template <typename T>
  void PCurve<T>::removeVisualizer( Visualizer* visualizer ) {

    PCurveVisualizer<T> *visu = dynamic_cast<PCurveVisualizer<T>*>( visualizer );
    if( visu )
      _pcurve_visualizers.remove( visu );

    SceneObject::removeVisualizer( visu );
  }




//  template <typename T>
//  inline
//  void PCurve<T>::resample( Array< Point<T, 3> >& a, T eps ) {
//
//    _sam = 0; _s_sam = 0; _e_sam = 1;
//    T t, ddt, dp5 = getParDelta()/5;
//    bool go_on=true;
//
//    for( t = getParStart(); go_on; t += ddt ) {
//
//      eval( t, 2 );
//      a += _p[0];
//      if ( a.getSize() > 7000 )
//        break;
//
//      T _r = _p[1] * _p[1];
//      Vector<T,3> r = _p[2]-( (_p[2] * _p[1] ) / _r) * _p[1];
//      _r = sqrt(double(_r));
//      ddt = 2 * _r / _p[1].getLength() * acos( ( _r - eps ) / _r);
//
//      if( ddt > dp5)
//        ddt = dp5;
//
//      if( ddt > getParEnd() - t ) {
//
//        T oddt = ddt;
//        ddt = getParEnd() - t;
//        go_on = false;
//
//        if( ddt < oddt / 5 )
//          a.removeIndex( a.getSize() - 1 );
//      }
//    }
//    eval( t, 0 );
//    a += _p[0];
//  }
//
//
//  template <typename T>
//  inline
//  void PCurve<T>::resample( Array<Point<T,3> >& a, int m ) {
//
//    _sam = m; _s_sam = 0; _e_sam = 1;
//    T du = getParDelta() / ( m - 1 );
//    a.setSize( m );
//
//    for( int i = 0; i < m; i++ ) {
//
//      eval( getParStart() + i * du, 0 );
//      a[i] = _p[0];
//    }
//
//  }
//
//
//  template <typename T>
//  inline
//  void PCurve<T>::resample( Array<Point<T,3> >& a, int m, T start, T end ) {
//
//    _sam = m; _s_sam = start; _e_sam = end;
//    T du = getParDelta();
//    T st = getParStart() + start * du;
//    T et = getParStart() + end * du;
//    du = ( et - st ) / ( m - 1 );
//    a.setSize( m );
//
//    for(int i=0; i<m; i++) {
//
//      eval( st + i * du, 0 );
//      a[i] = _p[0];
//    }
//  }


  template <typename T>
  inline
  void PCurve<T>::resample( DVector< DVector< Vector<T, 3> > >& p, int m, int d, T start, T end ) {

    T du = (end-start)/(m-1);
    p.setDim(m);

    for( int i = 0; i < m - 1; i++ ) {

      eval( start + i * du, d, true);
      p[i] = _p;
    }
    eval( end, d, true );
    p[m-1] = _p;


    switch( this->_dm ) {
      case GM_DERIVATION_EXPLICIT:
        // Do nothing, evaluator algorithms for explicite calculation of derivatives
        // should be defined in the eval( ... ) function enclosed by
        // if( this->_derivation_method == this->EXPLICIT ) { ... eval algorithms for derivatives ... }
        break;

      case GM_DERIVATION_DD:
      default:
        _evalDerDD( p, d, du );
        break;
    };
  }


  template <typename T>
  inline
  void PCurve<T>::setDomain(T start, T end) {

    _sc = ( end - start );
    _tr= getStartP() + start;
  }


  template <typename T>
  inline
  void PCurve<T>::setDomainScale( T sc ) {

    _sc = sc;
  }


  template <typename T>
  inline
  void PCurve<T>::setDomainTrans( T tr ) {

    _tr = tr;
  }


  template <typename T>
  inline
  void PCurve<T>::setLineWidth( float width ) {

    _line_width = width;
  }


  template <typename T>
  inline
  void PCurve<T>::setNoDer( int d ) {

    _defalt_d = d;
  }


  template <typename T>
  inline
  void PCurve<T>::setSurroundingSphere( const DVector< DVector< Vector<T, 3> > >& p ) {

    Sphere<float,3>  s;
    s.resetPos( Point<float,3>( p(0)(0) ) );
    s += Point<float,3>( p(p.getDim() - 1)(0) );
    for( int i = p.getDim() - 2; i > 0; i-- )
      s += Point<float,3>( p(i)(0) );
    Parametrics<T,1>::setSurroundingSphere(s);
  }


  template <typename T>
  inline
  T PCurve<T>::shift( T t ) {

    return _tr + _sc * ( t - getStartP() );
  }

  template <typename T>
  void PCurve<T>::toggleDefaultVisualizer() {

    if( !_pcurve_visualizers.exist( _default_visualizer ) )
      enableDefaultVisualizer( true );
    else
      enableDefaultVisualizer( false );
  }


  template <typename T>
  inline
  Point<T,3> PCurve<T>::operator()( T t )	{

    eval( t, _defalt_d );
    return ( Point<T,3> ) _p[0];
  }


} // END namespace GMlib
