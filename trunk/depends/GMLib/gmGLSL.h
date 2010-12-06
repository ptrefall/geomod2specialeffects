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



/*! \file gmGLSL.h
 *
 *  Pending Documentation
 *
 *  \date   2009-05-02
 */


#ifndef __gmGPUGLSL_H__
#define __gmGPUGLSL_H__

#include "gmOpenGL.h"

#ifdef GM_GL_EXTENSION
  #define GM_GPU_GLSL
#endif


#ifdef  GM_GPU_GLSL


namespace GMlib {

  namespace GLSL {

    class GLShader {
    public:
      GLShader( GLenum type );
      ~GLShader();

      bool          compile();
      std::string   getInfoLog() const;
      GLuint        getId() const;
      GLenum        getType() const;
      bool          isCompiled() const;
      void          set( const char* source );

    protected:
      GLenum        _type;
      GLuint        _id;
      const char    *_source;
      bool          _compiled;
      std::string   _info_log;

      void          updateInfoLog();



    }; // END class Shader 2


    class GLProgram {
    public:
      GLProgram();
      ~GLProgram();

      void          attachShader( GLShader* shader );
      void          begin();
      void          detachShader( GLShader* shader );
      void          end();
      GLuint        getId();
      std::string   getInfoLog();
      bool          link();

    protected:
      GLuint        _id;
      std::string   _info_log;

      void          updateInfoLog();


    }; // END class GLProgram

  } // End namespace GLSL

} // End namespace GMlib


#endif // GM_GPU_GLSL

#endif // __gmGPUGLSL_H__
