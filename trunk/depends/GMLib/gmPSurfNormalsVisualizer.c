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



/*! \file gmPSurfNormalsVisualizer.c
 *
 *  Implementation of the PSurfNormalsVisualizer template class.
 *
 *  \date   2010-04-13
 */


namespace GMlib {

  template <typename T>
  PSurfNormalsVisualizer<T>::PSurfNormalsVisualizer() {

    _color = GMcolor::Black;
    _size = 1.0;

    _no_elements = 0;

    glGenBuffers( 1, &_vbo );
  }

  template <typename T>
  PSurfNormalsVisualizer<T>::~PSurfNormalsVisualizer() {

    glDeleteBuffers( 1, &_vbo );
  }

  template <typename T>
  inline
  void PSurfNormalsVisualizer<T>::display() {

    // Push GL Attributes
    glPushAttrib( GL_LINE_BIT | GL_LIGHTING_BIT );

    // Set Properties
    glDisable( GL_LIGHTING );
    glColor( _color );

    // Bind VBO
    glBindBuffer( GL_ARRAY_BUFFER, _vbo );

    // Enable Vertex and Normal Array
    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 3, GL_FLOAT, 0, (GLvoid*)0x0 );

    // Draw
    glDrawArrays( GL_LINES, 0, _no_elements );

    // Disable Client States
    glDisableClientState( GL_VERTEX_ARRAY );

    // Unbind VBO
    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );

    // Pop GL Attributes
    glPopAttrib();
  }

  template <typename T>
  const Color& PSurfNormalsVisualizer<T>::getColor() const {

    return _color;
  }

  template <typename T>
  std::string PSurfNormalsVisualizer<T>::getIdentity() const {

    return "PSurf Normals Visualizer";
  }

  template <typename T>
  double PSurfNormalsVisualizer<T>::getSize() const {

    return _size;
  }

  template <typename T>
  void PSurfNormalsVisualizer<T>::replot(
    DMatrix< DMatrix< Vector<T, 3> > >& p,
    DMatrix< Vector<T, 3> >& normals,
    int /*m1*/, int /*m2*/, int /*d1*/, int /*d2*/
  ) {

    int no_normals = p.getDim1() * p.getDim2();
    _no_elements = no_normals * 2;

    glBindBuffer( GL_ARRAY_BUFFER, _vbo);
    glBufferData( GL_ARRAY_BUFFER, no_normals * 2 * 3 * sizeof(float), 0x0, GL_DYNAMIC_DRAW );


    float *ptr = (float*)glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY );
    if( ptr ) {


      for( int i = 0; i < p.getDim1(); i++ )
        for( int j = 0; j < p.getDim2(); j++ ) {

          for( int k = 0; k < 3; k++ )
            *(ptr++) = p[i][j][0][0][k];

          const GMlib::Vector<T,3> N = normals[i][j].getNormalized() * _size;
          for( int k = 0; k < 3; k++ )
            *(ptr++) = p[i][j][0][0][k] + N(k);
        }
    }

    glUnmapBuffer( GL_ARRAY_BUFFER );
    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );
  }

  template <typename T>
  void PSurfNormalsVisualizer<T>::setColor( const Color& color ) {

    _color = color;
  }

  template <typename T>
  void PSurfNormalsVisualizer<T>::setSize( double size ) {

    _size = size;
  }



} // END namespace GMlib
