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



/*! \file gmGLPhongShader.cpp
 *
 *  Pending Documentation
 *
 *  \date   2009-05-23
 */


#include "gmGLPhongShader.h"


#ifdef GM_GPU_GLSL


namespace GMlib {

  namespace GLSL {

    GLPhongShader::GLPhongShader() : GLShader() {

      const char* vs = {
      "varying vec3 normal, lightVec, eyeVec;"
      "varying vec4 Ag, A, D, S;"
      "void main()"
      "{"
      " normal       = vec3( gl_NormalMatrix * gl_Normal );"
      " eyeVec       = vec3( gl_ModelViewMatrix * gl_Vertex );"
      " lightVec     = vec3( gl_LightSource[0].position.xyz - eyeVec );"
      " Ag           = gl_LightModel.ambient       * gl_FrontMaterial.ambient;"
      " A            = gl_LightSource[0].ambient   * gl_FrontMaterial.ambient;"
      " D            = gl_LightSource[0].diffuse   * gl_FrontMaterial.diffuse;"
      " S            = gl_LightSource[0].specular  * gl_FrontMaterial.specular;"
      " gl_Position  = ftransform();"
      "}"
      };


      const char* fs = {
      "varying vec3 normal, lightVec, eyeVec;"
      "varying vec4 Ag, A, D, S;"
      "void main()"
      "{"
      " vec4 color     = Ag + A;"
      " vec3 N         = normalize( normal );"
      " vec3 L         = normalize( lightVec );"
      " float lambert  = dot( N, L ); "
      " if( lambert > 0.0 )"
      " {"
      "   color    += D * lambert;"
      "   vec3 E    = normalize( -eyeVec );"
      "   vec3 R    = vec3( 2.0 * N * lambert - L );"
      "   float PS  = pow( max( dot( R, E ), 0.0 ), gl_FrontMaterial.shininess );"
      "   color    += S * PS;"
      " }"
      " gl_FragColor = color;"
      "}"
      };

      this->set( vs, fs );
      this->initShader();
    }


    GLPhongShader::~GLPhongShader() {}


  } // End namespace GLSL

} // End namespace GMlib


#endif // GM_GPU_GLSL_ENABLED
