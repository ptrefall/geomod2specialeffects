varying vec3 normal, lightVec, eyeVec;
varying vec4 Ag, A, D, S;
void main()
{
  vec4 color     = Ag + A;
  vec3 N         = normalize( normal );
  vec3 L         = normalize( lightVec );
  float lambert  = dot( N, L );
  if( lambert > 0.0 )
  {
    color    += D * lambert;
    vec3 E    = normalize( -eyeVec );
    vec3 R    = vec3( 2.0 * N * lambert - L );
    float PS  = pow( max( dot( R, E ), 0.0 ), gl_FrontMaterial.shininess );
    color    += S * PS;
  }
  gl_FragColor = color;
}
