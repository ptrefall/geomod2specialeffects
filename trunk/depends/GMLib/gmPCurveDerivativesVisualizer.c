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



/*! \file gmPCurveDerivativesVisualizer.c
 *
 *  Implementation of the PCurveDerivativesVisualizer template class.
 *
 *  \date   2010-04-13
 */


namespace GMlib {

  template <typename T>
  PCurveDerivativesVisualizer<T>::PCurveDerivativesVisualizer() {

    _color = GMcolor::Green;
    _t = 1;
    _mode = GM_PCURVE_DERIVATIVESVISUALIZER_RELATIVE;
    _size = 1.0;

    glGenBuffers( 1, &_vbo );
  }

  template <typename T>
  PCurveDerivativesVisualizer<T>::~PCurveDerivativesVisualizer() {

    glDeleteBuffers( 1, &_vbo );
  }

  template <typename T>
  inline
  void PCurveDerivativesVisualizer<T>::display() {

    // Push GL Attributes
    glPushAttrib( GL_LINE_BIT | GL_LIGHTING_BIT );

    // Set Properties
    glDisable( GL_LIGHTING );
    glColor( _color );

    // Binder VBO
    glBindBuffer( GL_ARRAY_BUFFER, _vbo );
    glVertexPointer( 3, GL_FLOAT, 0, (const GLvoid*)0x0 );

    // Enable vertex array
    glEnableClientState( GL_VERTEX_ARRAY );

    // Draw
    glDrawArrays( GL_LINES, 0, _no_elements );

    // Disable vertex array
    glDisableClientState( GL_VERTEX_ARRAY );

    // UnBind VBO
    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );

    // Pop GL Attributes
    glPopAttrib();
  }

  template <typename T>
  const Color& PCurveDerivativesVisualizer<T>::getColor() const {

    return _color;
  }

  template <typename T>
  int PCurveDerivativesVisualizer<T>::getDerivative() const {

    return _t;
  }

  template <typename T>
  std::string PCurveDerivativesVisualizer<T>::getIdentity() const {

    return "PCurve Derivatives Visualizer";
  }

  template <typename T>
  GM_PCURVE_DERIVATIVESVISUALIZER_SIZE PCurveDerivativesVisualizer<T>::getMode() const {

    return _mode;
  }

  template <typename T>
  double PCurveDerivativesVisualizer<T>::getSize() const {

    return _size;
  }

  template <typename T>
  inline
  void PCurveDerivativesVisualizer<T>::replot(
    DVector< DVector< Vector<T, 3> > >& p,
    int /*m*/, int /*d*/
  ) {

    int der = 0;
    if( (_t >= 0) || (_t <= p[0].getDim()-1) )
      der = _t;


    int no_derivatives = p.getDim();
    _no_elements = no_derivatives * 2;

    glBindBuffer( GL_ARRAY_BUFFER, _vbo );
    glBufferData( GL_ARRAY_BUFFER, no_derivatives * 2 * 3 * sizeof(float), 0x0, GL_DYNAMIC_DRAW );

    float *ptr = (float*)glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY );
    if( ptr ) {

      switch( _mode ) {
      case GM_PCURVE_DERIVATIVESVISUALIZER_RELATIVE: {

          for( int i = 0; i < p.getDim(); i++ ) {

            for( int j = 0; j < 3; j++ )
              *(ptr++) = p[i][0][j];

            const GMlib::Vector<T,3> v = p[i][der] * _size;
            for( int j = 0; j < 3; j++ )
              *(ptr++) = p[i][0][j] + v(j);
          }
        }
        break;

      case GM_PCURVE_DERIVATIVESVISUALIZER_ABSOLUTE: {

          for( int i = 0; i < p.getDim(); i++ ) {

            for( int j = 0; j < 3; j++ )
              *(ptr++) = p[i][0][j];

            const GMlib::Vector<T,3> v = p[i][der].getNormalized() * _size;
            for( int j = 0; j < 3; j++ )
              *(ptr++) = p[i][0][j] + v(j);
          }
        }
        break;

      case GM_PCURVE_DERIVATIVESVISUALIZER_NORMALIZED:
      default: {

          for( int i = 0; i < p.getDim(); i++ ) {

            for( int j = 0; j < 3; j++ )
              *(ptr++) = p[i][0][j];

            const GMlib::UnitVector<T,3> uv = p[i][der];
            for( int j = 0; j < 3; j++ )
              *(ptr++) = p[i][0][j] + uv(j);
          }
        }
        break;
      }
    }

    glUnmapBuffer( GL_ARRAY_BUFFER );
    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );
  }

  template <typename T>
  void PCurveDerivativesVisualizer<T>::setColor( const Color& color ) {

    _color = color;
  }

  template <typename T>
  void PCurveDerivativesVisualizer<T>::setDerivative( int t ) {

    if( _t > 0 )
      _t = t;
  }

  template <typename T>
  void PCurveDerivativesVisualizer<T>::setMode( GM_PCURVE_DERIVATIVESVISUALIZER_SIZE mode ) {

    _mode = mode;
  }

  template <typename T>
  void PCurveDerivativesVisualizer<T>::setSize( double size ) {

    _size = size;
  }


} // END namespace GMlib
