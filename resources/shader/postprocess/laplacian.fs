
// This texture should hold the image to blur.
// This can perhaps be a previous rendered scene.
uniform sampler2D tex;
 
// texture coordinates passed from the vertex shader
varying vec2 uv;
uniform vec2 resolution;

void main(void)
{
    vec4 color = texture2D(tex,uv);
    vec2 res_step = 1.0 / resolution;
    
    vec2 position = uv;
    position.y -= res_step.y;
    vec4 sum = texture2D(tex,position) - color;
    position.y += res_step.y * 2.0;
    sum += texture2D(tex,position) - color;
    
    position.y = uv.y;
    position.x -= res_step.x;
    sum += texture2D(tex,position) - color;
    position.x += res_step.x * 2.0;
    sum += texture2D(tex,position) - color;
    
    //Blend the original color with the averaged pixels
    gl_FragColor = sum;
}
