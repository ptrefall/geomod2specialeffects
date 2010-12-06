varying vec3 normal, lightVec, eyeVec;
varying vec4 Ag, A, D, S;
void main()
{
  normal       = vec3( gl_NormalMatrix * gl_Normal );
  eyeVec       = vec3( gl_ModelViewMatrix * gl_Vertex );
  lightVec     = vec3( gl_LightSource[0].position.xyz - eyeVec );
  Ag           = gl_LightModel.ambient       * gl_FrontMaterial.ambient;
  A            = gl_LightSource[0].ambient   * gl_FrontMaterial.ambient;
  D            = gl_LightSource[0].diffuse   * gl_FrontMaterial.diffuse;
  S            = gl_LightSource[0].specular  * gl_FrontMaterial.specular;
  gl_Position  = ftransform();
}
