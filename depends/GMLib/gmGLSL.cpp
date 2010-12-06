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



/*! \file gmGLSL.cpp
 *
 *  Pending Documentation
 *
 *  \date   2009-05-02
 */


#include "gmGLSL.h"

#ifdef GM_GPU_GLSL


namespace GMlib {

  namespace GLSL {

    GLShader::GLShader( GLenum type ) {

      _type = type;
      _id = glCreateShader( type );
      _source = 0x0;
      _compiled = false;
    }

    GLShader::~GLShader() {

      glDeleteShader( _id );
    }

    bool GLShader::compile() {

      if( _compiled ) return false;
      if( !_source )  return false;

      glShaderSource( _id, 1, &_source, 0x0 );
      glCompileShader( _id );

      _compiled = true;

      int param;
      glGetShaderiv( _id, GL_COMPILE_STATUS, &param );
      return param == GL_TRUE;
    }

    std::string GLShader::getInfoLog() const {

      return _info_log;
    }

    GLuint GLShader::getId() const {

      return _id;
    }

    GLenum GLShader::getType() const {

      return _type;
    }

    bool GLShader::isCompiled() const {

      return _compiled;
    }

    void GLShader::set( const char* source ) {

      _source = source;
      _compiled = false;
    }

    void GLShader::updateInfoLog() {

      int len = 0;
      int written = 0;
      char *log;

      _info_log.clear();
      glGetShaderiv( _id, GL_INFO_LOG_LENGTH, &len );

      if( len > 0 ) {

        log = new char[len];
        glGetShaderInfoLog( _id, len, &written, log );

        _info_log.append( log, len );
        delete log;
      }
    }








    GLProgram::GLProgram() {

      _id = glCreateProgram();
    }

    GLProgram::~GLProgram() {

      glDeleteProgram( _id );
    }

    void GLProgram::attachShader( GLShader* shader ) {

      if( !shader ) return;

      glAttachShader( _id, shader->getId() );
    }

    void GLProgram::begin() {

      glUseProgram( _id );
    }

    void GLProgram::detachShader( GLShader* shader ) {

      if( !shader ) return;

      glDetachShader( _id, shader->getId() );
    }

    void GLProgram::end() {

      glUseProgram( 0 );
    }

    GLuint GLProgram::getId() {

      return _id;
    }

    std::string GLProgram::getInfoLog() {

      return _info_log;
    }

    bool GLProgram::link() {

      glLinkProgram( _id );

      int param;
      glGetProgramiv( _id, GL_LINK_STATUS, &param );
      return param == GL_TRUE;
    }

    void GLProgram::updateInfoLog() {

      int len = 0;
      int written = 0;
      char *log;

      _info_log.clear();

      glGetProgramiv( _id, GL_INFO_LOG_LENGTH, &len );

      if( len > 0 ) {

        log = new char[len];
        glGetProgramInfoLog( _id, len, &written, log );

        _info_log.append( log, len );
        delete log;
      }
    }

























  } // End namespace GLSL

} // End namespace GMlib


#endif // GM_GPU_GLSL_ENABLED
