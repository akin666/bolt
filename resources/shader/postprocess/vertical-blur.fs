
// This texture should hold the image to blur.
// This can perhaps be a previous rendered scene.
uniform sampler2D tex;
uniform float effect;
 
// texture coordinates passed from the vertex shader
varying vec2 uv;
 
void main(void)
{
   // some sample positions
   float samples[10] =
   float[](-0.08,-0.05,-0.03,-0.02,-0.01,0.01,0.02,0.03,0.05,0.08);

    // calculate the distance to the center of the screen
    float dist = 0.5 - uv.x; 
    vec2 dir = vec2( dist , 0.0 );
 
    // normalize the direction (reuse the distance)
    dir = dir/dist;
    
    // this is the original colour of this fragment
    // using only this would result in a nonblurred version
    vec4 color = texture2D(tex,uv); 
 
    vec4 sum = color;
 
    // take 10 additional blur samples in the direction towards
    // the center of the screen
    for (int i = 0; i < 10; i++)
    {
      sum += texture2D( tex, uv + dir * samples[i] * effect );
    }
 
    // we have taken eleven samples
    sum *= 1.0/11.0;
 
    //Blend the original color with the averaged pixels
    gl_FragColor = sum;
}
