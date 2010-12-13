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



/*! \file gmPCurveVisualizer.c
 *
 *  Implementation of the PCurveVisualizer template class.
 *
 *  \date   2010-04-13
 */

#include "../../src/Engine/Parametric/PCurve.h"
#include "gmPCurve.h"

namespace GMlib {

  template <typename T>
  PCurveVisualizer<T>::PCurveVisualizer() {

    _curve = 0x0;
    _no_vertices = 0;

    glGenBuffers( 1, &_vbo );
  }

  template <typename T>
  PCurveVisualizer<T>::~PCurveVisualizer() {

    glDeleteBuffers( 1, &_vbo );
  }

  template <typename T>
  inline
  void PCurveVisualizer<T>::display() {

    // Push GL Attributes
    glPushAttrib( GL_LIGHTING_BIT | GL_LINE_BIT | GL_TEXTURE_BIT ); {

      // Disable lighting
      glDisable( GL_LIGHTING );

      // Get Color Data
      const Color &c = this->_obj->getColor();
      glColor(c);

//      // Handle Opacity/Transparency
//      if( this->_obj->isOpaque() ) {
//
//        glBlendFunc(_blend_sfactor, _blend_dfactor);
//      }

      // GL States
	  GMlib::PCurve<T> *p_c = dynamic_cast< GMlib::PCurve<T>* >(_curve);
	  Engine::PCurve *pp_c = dynamic_cast< Engine::PCurve* >(_curve);
	  if(p_c)
		glLineWidth( p_c->getLineWidth() );
	  else if(pp_c)
		glLineWidth( pp_c->getLineWidth() );

      // Binder VBO
      glBindBuffer( GL_ARRAY_BUFFER, _vbo );
      glVertexPointer( 3, GL_FLOAT, 0, (const GLvoid*)0x0 );

      // Enable vertex array
      glEnableClientState( GL_VERTEX_ARRAY );

      // Draw
      glDrawArrays( GL_LINE_STRIP, 0, _no_vertices );

      // Disable vertex array
      glDisableClientState( GL_VERTEX_ARRAY );

      // UnBind VBO
      glBindBuffer( GL_ARRAY_BUFFER, 0x0 );

    // Pop GL Attributes
    } glPopAttrib();
  }

  template <typename T>
  std::string PCurveVisualizer<T>::getIdentity() const {

    return "PCurve Visualizer";
  }

  template <typename T>
  inline
  void PCurveVisualizer<T>::replot(
    DVector< DVector< Vector<T, 3> > >& p,
    int /*m*/, int /*d*/
  ) {

    _no_vertices = p.getDim();

    glBindBuffer( GL_ARRAY_BUFFER, _vbo );
    glBufferData( GL_ARRAY_BUFFER, _no_vertices * 3 * sizeof(float), 0x0, GL_DYNAMIC_DRAW );
    float *ptr = (float*)glMapBuffer( GL_ARRAY_BUFFER, GL_WRITE_ONLY );

    if( ptr ) {

      for( int i = 0; i < p.getDim(); i++ )
        for( int j = 0; j < 3; j++ )
          *(ptr++) = p[i][0][j];
    }

    glUnmapBuffer( GL_ARRAY_BUFFER );
    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );
  }

  template <typename T>
  inline
  void PCurveVisualizer<T>::select() {

    // Binder VBO
    glBindBuffer( GL_ARRAY_BUFFER, _vbo );
    glVertexPointer( 3, GL_FLOAT, 0, (const GLvoid*)0x0 );

    // Enable vertex array
    glEnableClientState( GL_VERTEX_ARRAY );

    // Draw
    glDrawArrays( GL_LINE_STRIP, 0, _no_vertices );//_v.getDim() );

    // Disable vertex array
    glDisableClientState( GL_VERTEX_ARRAY );

    // UnBind VBO
    glBindBuffer( GL_ARRAY_BUFFER, 0x0 );
  }

  template <typename T>
  void PCurveVisualizer<T>::set( SceneObject* obj ) {

    Visualizer::set(obj);

    _curve = dynamic_cast<PCurve<T>*>( obj );
  }


} // END namespace GMlib
