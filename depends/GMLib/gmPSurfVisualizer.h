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



/*! \file gmPSurfVisualizer.h
 *
 *  Interface for the PSurfVisualizer class.
 *
 *  \date   2010-04-13
 */


#ifndef __GMPSURFVISUALIZER_H__
#define __GMPSURFVISUALIZER_H__

#include "gmPoint.h"
#include "gmDMatrix.h"
#include "gmVisualizer.h"
#include "gmOpenGL.h"

namespace GMlib {

  template <typename T>
  class PSurf;

  template <typename T>
  class PSurfVisualizer : public Visualizer {
  public:
    PSurfVisualizer();
    ~PSurfVisualizer();
    void          display();
    std::string   getIdentity() const;
    virtual void  replot(
      DMatrix< DMatrix< Vector<T, 3> > >& p,
      DMatrix< Vector<T, 3> >& normals,
      int m1, int m2, int d1, int d2
    );
    void          select();
    void          set( SceneObject* obj );
//    void          setGLBlendFunc( GLenum sfactor, GLenum dfactor );

  protected:
    PSurf<T>      *_surf;
    GLuint        _vbo_v;
    GLuint        _vbo_n;
    GLuint        _vbo_t;

    int           _no_vertices;
    int           _no_normals;
    int           _no_texcoords;

    int           _tri_strips;
    int           _tri_strip_verts;
//
//    GLenum                        _blend_sfactor;
//    GLenum                        _blend_dfactor;


  }; // END class PSurfVisualizer

} // END namespace GMlib

// Include PSurfVisualizer class function implementations
#include "gmPSurfVisualizer.c"



#endif // __GMPSURFVISUALIZER_H__
