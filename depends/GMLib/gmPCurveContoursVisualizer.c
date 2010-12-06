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



/*! \file gmPCurveContoursVisualizer.c
 *
 *  Implementation of the PCurveContoursVisualizer template class.
 *
 *  \date   2010-04-13
 */


namespace GMlib {

  template <typename T>
  PCurveContoursVisualizer<T>::PCurveContoursVisualizer() {

    // Set default mapping
    _mapping = GM_PCURVE_CONTOURSVISUALIZER_X;

    // Set default colors
    _colors += GMcolor::Red;
    _colors += GMcolor::Blue;

    glGenBuffers( 1, &_vbo_c );
  }

  template <typename T>
  PCurveContoursVisualizer<T>::~PCurveContoursVisualizer() {

    glDeleteBuffers( 1, &_vbo_c );
  }

  template <typename T>
  inline
  void PCurveContoursVisualizer<T>::display() {

    // Push GL Attribs
    glPushAttrib( GL_LIGHTING_BIT | GL_POINT_BIT | GL_LINE_BIT );

    // Disable lighting
    glDisable( GL_LIGHTING );

    // Binder VBO
    glBindBuffer( GL_ARRAY_BUFFER, this->_vbo );
    glVertexPointer( 3, GL_FLOAT, 0, (const GLvoid*)0x0 );

    glBindBuffer( GL_ARRAY_BUFFER, _vbo_c );
    glColorPointer( 4, GL_FLOAT, 0, (const GLvoid*) 0x0 );

    // Enable vertex array
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY );

    // Draw
    glDrawArrays( GL_LINE_STRIP, 0, this->_no_vertices );

    // Disable vertex array
    glDisableClientState( GL_COLOR_ARRAY );
    glDisableClientState( GL_VERTEX_ARRAY );

    // UnBind VBO
    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );

    // Pop GL Attribs
    glPopAttrib();
  }

  template <typename T>
  inline
  Color PCurveContoursVisualizer<T>::getColor( T d ) {

    // Find Index
    int idx;
    idx = d * ( _colors.getSize()-1 );
    if( idx == _colors.getSize()-1 ) idx--;
    if( (idx < 0) || (idx > _colors.getSize()-1) ) idx = 0;


    double local_d = (double( _colors.getSize()-1 ) * d) - idx;
    Color ret = _colors[idx].getInterpolatedHSV( local_d, _colors[idx+1] );

    return ret;
  }

  template <typename T>
  const Array<Color>& PCurveContoursVisualizer<T>::getColors() const {

    return _colors;
  }

  template <typename T>
  inline
  T PCurveContoursVisualizer<T>::getCurvature( DVector< Vector<T, 3> >& p ) {

    Vector<T,3> d1 = p[1];
    T a1= d1.getLength();

    if( a1 < T(1.0e-5) )
      return T(0);

    d1 /= a1;

    Vector<T,3> d2 = ( p[2] - ( d1 * p[2] ) * d1 ) / ( a1 * a1 );

    return d2.getLength();
  }

  template <typename T>
  std::string PCurveContoursVisualizer<T>::getIdentity() const {

    return "PCurve Contours Visualizer";
  }

  template <typename T>
  GM_PCURVE_CONTOURSVISUALIZER_MAP PCurveContoursVisualizer<T>::getMapping() const {

    return _mapping;
  }

  template <typename T>
  inline
  T PCurveContoursVisualizer<T>::getValue( DVector< DVector< Vector<T, 3> > >& p, int i ) {

    switch( _mapping ) {
    case GM_PCURVE_CONTOURSVISUALIZER_X:
      return p[i][0][0];
    case GM_PCURVE_CONTOURSVISUALIZER_Y:
      return p[i][0][1];
    case GM_PCURVE_CONTOURSVISUALIZER_Z:
      return p[i][0][2];

    default: break;
    }


    // Values requireing 1st derivative
    if( p[i].getDim() < 2 )
      return T(0);

    switch( _mapping ) {
    case GM_PCURVE_CONTOURSVISUALIZER_SPEED:
      return p[i][1].getLength();

    default: break;
    }


    // Values requireing 2nd derivative
    if( p[i].getDim() < 2 )
      return T(0);

    switch( _mapping ) {
    case GM_PCURVE_CONTOURSVISUALIZER_CURVATURE:
      return getCurvature (p[i] );

    default: break;
    }

    return T(0);
  }

  template <typename T>
  inline
  void PCurveContoursVisualizer<T>::replot(
    DVector< DVector< Vector<T, 3> > >& p,
    int m, int d
  ) {

    // Replot the default visualizer
    PCurveVisualizer<T>::replot( p, m, d );

    T min, max;
    T C; // Color Factor, (map to local)
    _c.setDim( p.getDim() );
    switch( _mapping ) {

    case GM_PCURVE_CONTOURSVISUALIZER_T:
      {
        for( int i = 0; i < p.getDim(); i++ )
          _c[i] = getColor( double(i) / double(p.getDim()-1) );
      }
      break;
    default:
      {
        // Init min/max
        min = max = getValue( p, 0 );//_getCurvatureCurve(p[0]);

        // Extract all speed data
        for( int i = 0; i < p.getDim(); i++ ) {

          const T curvature = getValue( p, i );//_getCurvatureCurve(p[i]);
          if( curvature < min )
            min = curvature;
          if( curvature > max )
            max = curvature;
        }

        // Correct interval
        if( (max-min) < 1e-5 ) {

          for( int i = 0; i < p.getDim(); i++ )
            _c[i] = _colors[0];
        }
        else {
          C = 1.0f / (max-min);
          min /= (max-min);

          // Compute interpolated color values
          for( int i = 0; i < p.getDim(); i++ ) {

            const T curvature = getValue( p, i );//_getCurvatureCurve(p[i]);
            _c[i] = getColor( ( C * curvature ) - min );
          }
        }
      }
      break;
    }

    glBindBuffer( GL_ARRAY_BUFFER, _vbo_c );
    glBufferData( GL_ARRAY_BUFFER, this->_no_vertices * 4 * sizeof(float), 0x0,  GL_DYNAMIC_DRAW );
    float *ptr = (float*)glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY );

    if( ptr ) {

      for( int i = 0; i < _c.getDim(); i++ )
        for( int j = 0; j < 4; j++ )
          *(ptr++) = _c[i].getClampd(j);
    }

    glUnmapBuffer( GL_ARRAY_BUFFER );
    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );
  }

  template <typename T>
  void PCurveContoursVisualizer<T>::setColors( const Array<Color>& c ) {

    _colors = c;
  }

  template <typename T>
  void PCurveContoursVisualizer<T>::setMapping( GM_PCURVE_CONTOURSVISUALIZER_MAP mapping ) {

    _mapping = mapping;
  }



} // END namespace GMlib
