
// This texture should hold the image to blur.
// This can perhaps be a previous rendered scene.
uniform sampler2D tex;
 
// texture coordinates passed from the vertex shader
varying vec2 uv;
uniform float effect;

void main(void)
{
    vec4 color = texture2D(tex,uv); 
    vec4 negative = vec4( vec3( 1.0 , 1.0 , 1.0 ) - color.rgb , color.a );
    
    //Blend the original color with the averaged pixels
    gl_FragColor = mix( negative , color , effect );
}

