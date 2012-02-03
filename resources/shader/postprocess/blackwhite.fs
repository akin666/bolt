
// This texture should hold the image to blur.
// This can perhaps be a previous rendered scene.
uniform sampler2D tex;
 
// texture coordinates passed from the vertex shader
varying vec2 uv;
uniform float effect;

void main(void)
{
    vec4 color = texture2D(tex,uv); 
    
    // weighten the blur effect with the distance to the
    // center of the screen ( further out is blurred more)
    float t = clamp( effect ,0.0,1.0);
 
    //Blend the original color with the averaged pixels
    gl_FragColor = mix( color, max(color.r,max(color.g,color.b), t );
}
