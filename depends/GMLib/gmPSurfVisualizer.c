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



/*! \file gmPSurfVisualizer.c
 *
 *  Implementation of the PSurfVisualizer template class.
 *
 *  \date   2010-04-13
 */


// local
#include "gmMaterial.h"
#include "gmPSurf.h"
#include "gmOpenGL.h"


namespace GMlib {

  template <typename T>
  PSurfVisualizer<T>::PSurfVisualizer() {

    _surf = 0x0;
    _tri_strips = 0;
    _tri_strip_verts = 0;

    _no_vertices = 0;
    _no_normals = 0;
    _no_texcoords = 0;

    glGenBuffers( 1, &_vbo_v );
    glGenBuffers( 1, &_vbo_n );
    glGenBuffers( 1, &_vbo_t );
  }

  template <typename T>
  PSurfVisualizer<T>::~PSurfVisualizer() {

    glDeleteBuffers( 1, &_vbo_v );
    glDeleteBuffers( 1, &_vbo_n );
    glDeleteBuffers( 1, &_vbo_t );
  }

  template <typename T>
  inline
  void PSurfVisualizer<T>::display() {

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


      // Handle Opacity/Transparency
//      if( this->_obj->isOpaque() ) {
//
//        glBlendFunc(_blend_sfactor, _blend_dfactor);
//      }

      glBindBuffer( GL_ARRAY_BUFFER, _vbo_v );
      glVertexPointer( 3, GL_FLOAT, 0, (const GLvoid*)0x0 );

      glBindBuffer( GL_ARRAY_BUFFER, _vbo_n );
      glNormalPointer( GL_FLOAT, 0, (const GLvoid*)0x0 );

      glBindBuffer( GL_ARRAY_BUFFER, _vbo_t );
      glTexCoordPointer( 2, GL_FLOAT, 0, (const GLvoid*)0x0 );


      glEnableClientState( GL_VERTEX_ARRAY );
      glEnableClientState( GL_NORMAL_ARRAY );

      if( m.getTextureID() )
        glEnableClientState( GL_TEXTURE_COORD_ARRAY );

      for( int i = 0; i < _tri_strips; i++ ) {


        const int first = i*_tri_strip_verts;
        glDrawArrays( GL_TRIANGLE_STRIP, first, _tri_strip_verts );
      }

      glDisableClientState( GL_TEXTURE_COORD_ARRAY );
      glDisableClientState( GL_NORMAL_ARRAY );
      glDisableClientState( GL_VERTEX_ARRAY );
      glBindBuffer( GL_ARRAY_BUFFER, 0x0 );


    // Pop GL Attributes
    } glPopAttrib();
  }

  template <typename T>
  std::string PSurfVisualizer<T>::getIdentity() const {

    return "PSurf Visualizer";
  }

  template <typename T>
  inline
  void PSurfVisualizer<T>::replot(
    DMatrix< DMatrix< Vector<T, 3> > >& p,
    DMatrix< Vector<T, 3> >& normals,
    int /*m1*/, int /*m2*/, int /*d1*/, int /*d2*/
  ) {

    _no_vertices = (p.getDim1()-1) * p.getDim2() * 2;
    _no_normals = _no_vertices;
    _no_texcoords = _no_vertices;

    glBindBuffer( GL_ARRAY_BUFFER, _vbo_v );
    glBufferData( GL_ARRAY_BUFFER, _no_vertices * 3 * sizeof(float), 0x0,  GL_DYNAMIC_DRAW );
    float *vptr = (float*)glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY );

    glBindBuffer( GL_ARRAY_BUFFER, _vbo_n );
    glBufferData( GL_ARRAY_BUFFER, _no_normals * 3 * sizeof(float), 0x0, GL_DYNAMIC_DRAW );
    float *nptr = (float*)glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY );

    glBindBuffer( GL_ARRAY_BUFFER, _vbo_t );
    glBufferData( GL_ARRAY_BUFFER, _no_texcoords * 2 * 2 * sizeof(float), 0x0, GL_DYNAMIC_DRAW );
    float *tptr = (float*)glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY );

    if( vptr && nptr && tptr ) {

      _tri_strips = p.getDim1()-1;
      _tri_strip_verts = p.getDim2()*2;

      for( int i = 0; i < p.getDim1()-1; i++ ) {

        const int idx_i = i * p.getDim2() * 2;

        for( int j = 0; j < p.getDim2(); j++ ) {


          // Vertices and Normals
          const int idx_j = (idx_i + (j*2)) * 3;
          const UnitVector<T,3> n1 = normals[ i   ][j];
          const UnitVector<T,3> n2 = normals[ i+1 ][j];
          for( int k = 0; k < 3; k++ ) {

            const int idx_k = idx_j + k;
            vptr[idx_k]   = p[ i   ][j][0][0][k];
            vptr[idx_k+3] = p[ i+1 ][j][0][0][k];
            nptr[idx_k]   = n1(k);
            nptr[idx_k+3] = n2(k);
          }

          // Texture Coords
          const int idx_k = (idx_i + (j*2)) * 2;
          tptr[idx_k]   = i / float( p.getDim1() - 1 ); // s1
          tptr[idx_k+1] = j / float( p.getDim2() - 1 ); // t1
          tptr[idx_k+2] = (i+1) / float( p.getDim1() - 1 ); // s2
          tptr[idx_k+3] = j / float( p.getDim2() - 1 ); // t2
        }
      }
    }

    glBindBuffer( GL_ARRAY_BUFFER, _vbo_v );
    glUnmapBuffer( GL_ARRAY_BUFFER );

    glBindBuffer( GL_ARRAY_BUFFER, _vbo_n );
    glUnmapBuffer( GL_ARRAY_BUFFER );

    glBindBuffer( GL_ARRAY_BUFFER, _vbo_t );
    glUnmapBuffer( GL_ARRAY_BUFFER );

  }

  template <typename T>
  inline
  void PSurfVisualizer<T>::select() {

    glBindBuffer( GL_ARRAY_BUFFER, _vbo_v );
    glEnableClientState( GL_VERTEX_ARRAY );

    glVertexPointer( 3, GL_FLOAT, 3*sizeof(float), (const GLvoid*)0 );
    for( int i = 0; i < _tri_strips; i++ ) {

      glDrawArrays( GL_TRIANGLE_STRIP, i*_tri_strip_verts, _tri_strip_verts );
    }

    glDisableClientState( GL_VERTEX_ARRAY );
    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );
  }

  template <typename T>
  void PSurfVisualizer<T>::set( SceneObject* obj ) {

    Visualizer::set( obj );

    _surf = dynamic_cast<PSurf<T>*>( obj );
  }

//  template <typename T>
//  void PSurfVisualizer<T>::setGLBlendFunc( GLenum sfactor, GLenum dfactor ) {
//
//    _blend_sfactor = sfactor;
//    _blend_dfactor = dfactor;
//  }

} // END namespace GMlib






