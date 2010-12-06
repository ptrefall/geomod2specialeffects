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



/*! \file gmPSurfContoursVisualizer.c
 *
 *  Implementation of the PSurfContoursVisualizer template class.
 *
 *  \date   2010-04-13
 */


namespace GMlib {


  template <typename T>
  PSurfContoursVisualizer<T>::PSurfContoursVisualizer() {

    _mapping = GM_PSURF_CONTOURSVISUALIZER_X;

    // Set default colors
    _colors += GMcolor::Red;
    _colors += GMcolor::Blue;

    // Set default interpolation method
    _method = GM_PSURF_CONTOURSVISUALIZER_LINEAR;

    glGenBuffers( 1, &_vbo );
  }

  template <typename T>
  PSurfContoursVisualizer<T>::~PSurfContoursVisualizer() {

    glDeleteBuffers( 1, &_vbo );
  }

  template <typename T>
  inline
  void PSurfContoursVisualizer<T>::display() {

    // Push GL Attribs
    glPushAttrib( GL_LIGHTING_BIT | GL_POINT_BIT | GL_LINE_BIT );

    // Disable lighting
    glDisable( GL_LIGHTING );

    glBindBuffer( GL_ARRAY_BUFFER, this->_vbo_v );
    glVertexPointer( 3, GL_FLOAT, 0, (const GLvoid*)0x0 );

    glBindBuffer( GL_ARRAY_BUFFER, _vbo );
    glColorPointer( 4, GL_FLOAT, 0, (const GLvoid*)0x0 );



    // Enable Vertex and Normal Array
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY );

    for( int i = 0; i < this->_tri_strips; i++ ) {


      const int first = i*this->_tri_strip_verts;
      glDrawArrays( GL_TRIANGLE_STRIP, first, this->_tri_strip_verts );
    }

    // Disable Client States
    glDisableClientState( GL_COLOR_ARRAY );
    glDisableClientState( GL_VERTEX_ARRAY );

    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );

    // Pop GL Attribs
    glPopAttrib();
  }

  template <typename T>
  inline
  Color PSurfContoursVisualizer<T>::getColor( T d ) {

    // Find Index
    int idx;
    idx = d * ( _colors.getSize()-1 );
    if( idx == _colors.getSize()-1 ) idx--;
    if( (idx < 0) || (idx > _colors.getSize()-1) ) idx = 0;

    return _colors[idx];
  }

  template <typename T>
  inline
  Color PSurfContoursVisualizer<T>::getColorInterpolated( T d ) {

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
  const Array<Color>& PSurfContoursVisualizer<T>::getColors() const {

    return _colors;
  }

  template <typename T>
  inline
  T PSurfContoursVisualizer<T>::getCurvatureGauss( DMatrix< Vector<T,3> >& p ) {

    UnitVector<T,3> N   = Vector3D<T>(p[1][0])^p[0][1];
    Vector<T,3>		  du  = p[1][0];
    Vector<T,3>		  dv  = p[0][1];
    Vector<T,3>		  duu = p[2][0];
    Vector<T,3>		  duv = p[1][1];
    Vector<T,3>		  dvv = p[0][2];

    T E = du  * du;
    T F = du  * dv;
    T G = dv  * dv;
    T e = N   * duu;
    T f = N   * duv;
    T g = N   * dvv;

    return (e*g - f*f) / (E*G - F*F);
  }

  template <typename T>
  inline
  T PSurfContoursVisualizer<T>::getCurvatureMean( DMatrix< Vector<T,3> >& p ) {

    UnitVector<T,3> N   = Vector3D<T>(p[1][0])^p[0][1];
    Vector<T,3>		  du  = p[1][0];
    Vector<T,3>		  dv  = p[0][1];
    Vector<T,3>		  duu = p[2][0];
    Vector<T,3>		  duv = p[1][1];
    Vector<T,3>		  dvv = p[0][2];

    T E = du  * du;
    T F = du  * dv;
    T G = dv  * dv;
    T e = N   * duu;
    T f = N   * duv;
    T g = N   * dvv;

    return 0.5 * (e*G - 2 * (f*F) + g*E) / (E*G - F*F);
  }

  template <typename T>
  inline
  T PSurfContoursVisualizer<T>::getCurvaturePrincipalMax( DMatrix< Vector<T,3> >& p ) {

    T K = getCurvatureGauss( p );
    T H = getCurvatureMean( p );

    return H + sqrt( H*H - K );
  }

  template <typename T>
  inline
  T PSurfContoursVisualizer<T>::getCurvaturePrincipalMin( DMatrix< Vector<T,3> >& p ) {

    T K = getCurvatureGauss( p );
    T H = getCurvatureMean( p );

    return H - sqrt( H*H - K );
  }

  template <typename T>
  std::string PSurfContoursVisualizer<T>::getIdentity() const {

    return "PSurf Contours Visualizer";
  }

  template <typename T>
  GM_PSURF_CONTOURSVISUALIZER_INTERPOLATION_METHOD PSurfContoursVisualizer<T>::getInterpolationMethod() const {

    return _method;
  }

  template <typename T>
  GM_PSURF_CONTOURSVISUALIZER_MAP PSurfContoursVisualizer<T>::getMapping() const {

    return _mapping;
  }

  template <typename T>
  inline
  void PSurfContoursVisualizer<T>::replot(
    DMatrix< DMatrix< Vector<T, 3> > >& p,
    DMatrix< Vector<T, 3> >& normals,
    int m1, int m2, int d1, int d2
  ) {

    // Replot the default visualizer
    PSurfVisualizer<T>::replot( p, normals, m1, m2, d1, d2 );

    // Color/Material Countours
    DMatrix<double> cmap;

    T min, max;
    T C;
    cmap.setDim( p.getDim1(), p.getDim2() );
    switch( _mapping ) {

    case GM_PSURF_CONTOURSVISUALIZER_U:
      {
        for( int i = 0; i < p.getDim1(); i++ )
          for( int j = 0; j < p.getDim2(); j++ )
            cmap[i][j] = double(i) / double(p.getDim1()-1);
      }
      break;
    case GM_PSURF_CONTOURSVISUALIZER_V:
      {
        for( int i = 0; i < p.getDim1(); i++ )
          for( int j = 0; j < p.getDim2(); j++ )
            cmap[i][j] = double(j) / double(p.getDim2()-1);
      }
      break;

    default:
      {
        // Init min/max
        min = max = getValue(p, 0, 0);

        // Extract all Gaussian Curvature data
        for( int i = 0; i < p.getDim1(); i++ ) {
          for( int j = 0; j < p.getDim2(); j++ ) {

            const T curvature = getValue(p, i, j);
            if( curvature < min )
              min = curvature;
            if( curvature > max )
              max = curvature;
          }
        }

        // Correct interval
        if( (max-min) < 1e-5 ) {

          for( int i = 0; i < p.getDim1(); i++ )
            for( int j = 0; j < p.getDim2(); j++ )
              cmap[i][j] = 0.0;
        }
        else {
          C = 1.0f / (max-min);
          min /= (max-min);

          // Compute interpolated map values
          for( int i = 0; i < p.getDim1(); i++ ) {
            for( int j = 0; j < p.getDim2(); j++ ) {

              const T curvature = getValue(p, i, j);
              cmap[i][j] = ( C * curvature ) - min;
            }
          }
        }
      }
      break;
    }


    DMatrix<Color> ccs;
    ccs.setDim( p.getDim1(), p.getDim2() );

    switch( _method ) {
    case GM_PSURF_CONTOURSVISUALIZER_NO_INTERPOLATION:
      for( int i = 0; i < p.getDim1(); i++ )
        for( int j = 0; j < p.getDim2(); j++ )
          ccs[i][j] = getColor( cmap[i][j] );
      break;

    case GM_PSURF_CONTOURSVISUALIZER_LINEAR:
    default:
      for( int i = 0; i < p.getDim1(); i++ )
        for( int j = 0; j < p.getDim2(); j++ )
          ccs[i][j] = getColorInterpolated( cmap[i][j] );
      break;
    }






    glBindBuffer( GL_ARRAY_BUFFER, _vbo );
    glBufferData( GL_ARRAY_BUFFER, this->_no_vertices * 4 * sizeof(float), 0x0,  GL_DYNAMIC_DRAW );
    float *ptr = (float*)glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY );

    if( ptr ) {

      // Create Vertex arrays ^^
      for( int i = 0; i < p.getDim1()-1; i++ ) {

        const int idx_i = i * p.getDim2() * 2;
        for( int j = 0; j < p.getDim2(); j++ ) {

          const int idx_j = (idx_i + (j*2)) * 4;
          for( int k = 0; k < 4; k++ ) {
            ptr[idx_j+k]  =   ccs[i][j].getClampd(k);
            ptr[idx_j+k+4]  = ccs[i+1][j].getClampd(k);
          }
        }
      }
    }

    glUnmapBuffer( GL_ARRAY_BUFFER );
    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );

  }

  template <typename T>
  inline
  T PSurfContoursVisualizer<T>::getValue( DMatrix< DMatrix< Vector<T, 3> > >& p, int i, int j ) {

    switch( _mapping ) {
    case GM_PSURF_CONTOURSVISUALIZER_X:
      return p[i][j][0][0][0];
    case GM_PSURF_CONTOURSVISUALIZER_Y:
      return p[i][j][0][0][1];
    case GM_PSURF_CONTOURSVISUALIZER_Z:
      return p[i][j][0][0][2];

    default: break;
    }


    // Values requireing 1st derivatives
    if( p[i][j].getDim1() < 2 || p[i][j].getDim2() < 2 )
      return T(0);

    switch( _mapping ) {
    case GM_PSURF_CONTOURSVISUALIZER_U:
      return p[i][j][1][0].getLength();
    case GM_PSURF_CONTOURSVISUALIZER_V:
      return p[i][j][0][1].getLength();

    default: break;
    }


    // Values requireing 2nd derivatives
    if( p[i][j].getDim1() < 3 || p[i][j].getDim2() < 3 )
      return T(0);

    switch( _mapping ) {
    case GM_PSURF_CONTOURSVISUALIZER_CURVATURE_GAUSS:
      return getCurvatureGauss(p[i][j]);

    case GM_PSURF_CONTOURSVISUALIZER_CURVATURE_MEAN:
      return getCurvatureMean(p[i][j]);

    case GM_PSURF_CONTOURSVISUALIZER_CURVATURE_PRINCIPAL_MAX:
      return getCurvaturePrincipalMax( p[i][j] );

    case GM_PSURF_CONTOURSVISUALIZER_CURVATURE_PRINCIPAL_MIN:
      return getCurvaturePrincipalMin( p[i][j] );

    default: break;
    }

    return T(0);
  }

  template <typename T>
  void PSurfContoursVisualizer<T>::setColors( const Array<Color>& c ) {

    _colors = c;
  }

  template <typename T>
  void PSurfContoursVisualizer<T>::setInterpolationMethod( GM_PSURF_CONTOURSVISUALIZER_INTERPOLATION_METHOD method ) {

    _method = method;
  }

  template <typename T>
  void PSurfContoursVisualizer<T>::setMapping( GM_PSURF_CONTOURSVISUALIZER_MAP mapping ) {

    _mapping = mapping;
  }



} // END namespace GMlib
