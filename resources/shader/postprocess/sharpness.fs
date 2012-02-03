
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
    
    vec4 sum = color;
    vec2 position = uv-res_step;
    sum += color - texture2D(tex,position);
    position.x += res_step.x;
    sum += color - texture2D(tex,position);
    position.x += res_step.x;
    sum += color - texture2D(tex,position);
    
    position.y += res_step.y;
    sum += color - texture2D(tex,position);
    position.y += res_step.y;
    sum += color - texture2D(tex,position);
    
    position.x -= res_step.x;
    sum += color - texture2D(tex,position);
    position.x -= res_step.x;
    sum += color - texture2D(tex,position);
    
    position.y -= res_step.y;
    sum += color - texture2D(tex,position);
 
    //Blend the original color with the averaged pixels
    gl_FragColor = sum;
}
