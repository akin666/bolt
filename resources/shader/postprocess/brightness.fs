
// This texture should hold the image to blur.
// This can perhaps be a previous rendered scene.
uniform sampler2D tex;
 
// texture coordinates passed from the vertex shader
varying vec2 uv;
uniform float effect;

void main(void)
{
    //Blend the original color with the averaged pixels
    gl_FragColor = texture2D(tex,uv) * effect;
}
