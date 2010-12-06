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



/*! \file gmPSurfPointsVisualizer.c
 *
 *  Implementation of the PSurfPointsVisualizer template class.
 *
 *  \date   2010-04-13
 */


namespace GMlib {

  template <typename T>
  PSurfPointsVisualizer<T>::PSurfPointsVisualizer() {

    _size = 1.0;
    _color = GMcolor::BlueViolet;

    _no_points = 0;
    glGenBuffers( 1, &_vbo );
  }

  template <typename T>
  PSurfPointsVisualizer<T>::~PSurfPointsVisualizer() {

    glDeleteBuffers( 1, &_vbo );
  }

  template <typename T>
  inline
  void PSurfPointsVisualizer<T>::display() {

    // Push GL Attribs
    glPushAttrib( GL_LIGHTING_BIT | GL_POINT_BIT ); {

      // Set Properties
      glDisable( GL_LIGHTING );
      glColor( _color );
      glPointSize( _size );

      // Bind VBO
      glBindBuffer( GL_ARRAY_BUFFER, _vbo );

      // Enable vertex array
      glEnableClientState( GL_VERTEX_ARRAY );
      glVertexPointer( 3, GL_FLOAT, 0, (GLvoid*)0x0 );

      // Draw
      glDrawArrays( GL_POINTS, 0, _no_points );

      // Disable vertex array
      glDisableClientState( GL_VERTEX_ARRAY );

      // Unbind VBO
      glBindBuffer( GL_ARRAY_BUFFER, 0x0 );

    // Pop GL Attribs
    } glPopAttrib();

  }

  template <typename T>
  const Color& PSurfPointsVisualizer<T>::getColor() const {

    return _color;
  }

  template <typename T>
  std::string PSurfPointsVisualizer<T>::getIdentity() const {

    return "PSurf Point Visualizer";
  }

  template <typename T>
  float PSurfPointsVisualizer<T>::getSize() const {

    return _size;
  }

  template <typename T>
  inline
  void PSurfPointsVisualizer<T>::replot(
    DMatrix< DMatrix< Vector<T, 3> > >& p,
    DMatrix< Vector<T, 3> >& /*normals*/,
    int /*m1*/, int /*m2*/, int /*d1*/, int /*d2*/
  ) {

    _no_points = p.getDim1() * p.getDim2();

    glBindBuffer( GL_ARRAY_BUFFER, _vbo );
    glBufferData( GL_ARRAY_BUFFER, _no_points * 3 * sizeof(float), 0x0, GL_DYNAMIC_DRAW );

    float *ptr = (float*)glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY );
    if( ptr ) {

      for( int i = 0; i < p.getDim1(); i++ )
        for( int j = 0; j < p.getDim2(); j++ )
          for( int k = 0; k < 3; k++ )
            *(ptr++) = p[i][j][0][0][k];
    }

    glUnmapBuffer( GL_ARRAY_BUFFER );
    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );
  }

  template <typename T>
  void PSurfPointsVisualizer<T>::setColor( const Color& color ) {

    _color = color;
  }

  template <typename T>
  void PSurfPointsVisualizer<T>::setSize( float size ) {

    _size = size;
  }

} // END namespace GMlib
