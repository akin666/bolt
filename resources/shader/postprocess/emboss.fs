
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
    
    vec4 sum = color * 4.0;
    vec2 position = uv-res_step;
    sum += texture2D(tex,position);
    position.x += res_step.x;
    sum += texture2D(tex,position) * 2.0;
    position.x += res_step.x;
    sum += texture2D(tex,position);
    
    position.y += res_step.y;
    sum += texture2D(tex,position) * 2.0;
    position.y += res_step.y;
    sum += texture2D(tex,position);
    
    position.x -= res_step.x;
    sum += texture2D(tex,position) * 2.0;
    position.x -= res_step.x;
    sum += texture2D(tex,position);
    
    position.y -= res_step.y;
    sum += texture2D(tex,position) * 2.0;
    
    sum /= 16.0;
 
    //Blend the original color with the averaged pixels
    gl_FragColor = sum;
}
