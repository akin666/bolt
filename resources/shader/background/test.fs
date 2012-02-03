
uniform vec2 resolution;
uniform float time;

void main(void)
{
    vec4 color = vec4( 0.2 , 0.5 , 1.0 , 1.0 );
    
    //Blend the original color with the averaged pixels
    gl_FragColor = color;
}

