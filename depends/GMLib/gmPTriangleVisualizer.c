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



/*! \file gmPTriangleVisualizer.c
 *
 *  Implementation of the PTriangleVisualizer template class.
 *
 *  \date   2010-04-13
 */

#include <gmPTriangle.h>

namespace GMlib {


  template <typename T>
  PTriangleVisualizer<T>::PTriangleVisualizer() {

    _triangle = 0x0;
    _m = 0;

    _no_vertices = 0;

    glGenBuffers( 1, &_vbo );
  }

  template <typename T>
  PTriangleVisualizer<T>::~PTriangleVisualizer() {

    glDeleteBuffers( 1, &_vbo );
  }

  template <typename T>
  inline
  void PTriangleVisualizer<T>::display() {

    // Push GL Attributes
    glPushAttrib( GL_LIGHTING_BIT | GL_LINE_BIT | GL_TEXTURE_BIT ); {

      // Get Material Data
      const Material &m = this->_obj->getMaterial();

      // Handle lighting and set Color/Material accordingly
      if( this->_obj->isLighted() ) {

        glEnable( GL_LIGHTING );
        m.glSet();
      }
      else {

        glDisable( GL_LIGHTING );

        // Get Color Data
        const Color &c = this->_obj->getColor();
        glColor(c);
      }

      // Bind buffers
      glBindBuffer( GL_ARRAY_BUFFER, _vbo );
      glVertexPointer( 3, GL_FLOAT, PTRIANGLEVERTEX_SIZE, (const GLvoid*)0x0 );
      glNormalPointer( GL_FLOAT, PTRIANGLEVERTEX_SIZE, (const GLvoid*)12 );

      // Enable client states
      glEnableClientState( GL_VERTEX_ARRAY );
      glEnableClientState( GL_NORMAL_ARRAY );

      // Draw

      for( int i = 0; i < _m; i++ )
        glDrawArrays( GL_TRIANGLE_STRIP, i*(i+2), 2*i+3 );


      // Disable client states
      glDisableClientState( GL_NORMAL_ARRAY );
      glDisableClientState( GL_VERTEX_ARRAY );

      // Unbind buffers
      glBindBuffer( GL_ARRAY_BUFFER, 0x0 );

    // Pop GL Attributes
    } glPopAttrib();
  }

  template <typename T>
  std::string PTriangleVisualizer<T>::getIdentity() const {

    return "PTriangle Visualizer";
  }

  template <typename T>
  inline
  void PTriangleVisualizer<T>::replot( DVector< DMatrix< Vector<T,3> > >& p, int m ) {

    _m = m-1;

    int no_verts = _m*(_m+2); // m^2 + m*2
    if( _no_vertices != no_verts ) {

      _no_vertices = no_verts;

      // Allocate GPU memory
      glBindBuffer( GL_ARRAY_BUFFER, _vbo );
      glBufferData( GL_ARRAY_BUFFER, PTRIANGLEVERTEX_SIZE * _no_vertices, 0x0, GL_DYNAMIC_DRAW );
      glBindBuffer( GL_ARRAY_BUFFER, 0x0 );
    }


    // Fill GPU memory
    glBindBuffer( GL_ARRAY_BUFFER, _vbo );
    PTriangleVertex *ptr = (PTriangleVertex*)glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY );

    if( ptr ) {

      for( int i = 0; i < _m; i++ ) {

        int o1 = 0.5 *  i    * (i+1);
        int o2 = 0.5 * (i+1) * (i+2);
        int o = i*(i+2);
        int is = 2 * i + 3; // 0.5 * (i+2) * (i+3) - 0.5 *  i    * (i+1)

        for( int j = 0; j < is/2; j++ ) {

          int idx1 = (o+j*2);
          int idxp1 = o2 +j;
          UnitVector<float,3> n1 = Vector3D<float>( p[idxp1][0][1] ) ^ p[idxp1][1][0];

          ptr[idx1].x   = p[idxp1][0][0][0];
          ptr[idx1].y   = p[idxp1][0][0][1];
          ptr[idx1].z   = p[idxp1][0][0][2];
          ptr[idx1].nx  = n1[0];
          ptr[idx1].ny  = n1[1];
          ptr[idx1].nz  = n1[2];


          int idx2 = (o+j*2+1);
          int idxp2 = o1 +j;
          UnitVector<float,3> n2 = Vector3D<float>( p[idxp2][0][1] ) ^ p[idxp2][1][0];

          ptr[idx2].x   = p[idxp2][0][0][0];
          ptr[idx2].y   = p[idxp2][0][0][1];
          ptr[idx2].z   = p[idxp2][0][0][2];
          ptr[idx2].nx  = n2[0];
          ptr[idx2].ny  = n2[1];
          ptr[idx2].nz  = n2[2];
        }

        UnitVector<float,3> norm = Vector3D<float>( p[o1+is-1][0][1] ) ^ p[o1+is-1][1][0];

        ptr[o+is-1].x   = p[o1+is-1][0][0][0];
        ptr[o+is-1].y   = p[o1+is-1][0][0][1];
        ptr[o+is-1].z   = p[o1+is-1][0][0][2];
        ptr[o+is-1].nx  = norm[0];
        ptr[o+is-1].ny  = norm[1];
        ptr[o+is-1].nz  = norm[2];
      }
    }

    glUnmapBuffer( GL_ARRAY_BUFFER );
    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );
  }

  template <typename T>
  inline
  void PTriangleVisualizer<T>::select() {

    glBindBuffer( GL_ARRAY_BUFFER, _vbo );
    glEnableClientState( GL_VERTEX_ARRAY );

    glVertexPointer( 3, GL_FLOAT, PTRIANGLEVERTEX_SIZE, (const GLvoid*)0x0 );
    for( int i = 0; i < _m; i++ )
      glDrawArrays( GL_TRIANGLE_STRIP, i*(i+2), 2*i+3 );

    glDisableClientState( GL_VERTEX_ARRAY );
    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );
  }

  template <typename T>
  void PTriangleVisualizer<T>::set( SceneObject* obj ) {

    Visualizer::set( obj );

    _triangle = dynamic_cast<PTriangle<T>*>( obj );
  }





} // END namespace GMlib
