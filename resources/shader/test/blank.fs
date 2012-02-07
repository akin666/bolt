
#version 130

out vec4 color;
 
in vec3 vertex;

void main(void)
{
	vec3 normalizedColor = (vertex + 1.0) / 2.0;
	
    //vec4 color = vec4( smoothstep( 1.0 , 0.0 , normalizedColor ) , 1.0 );
    
    vec4 color = vec4( normalizedColor , 1.0 );
    
    //Blend the original color with the averaged pixels
    gl_FragColor = color;
}
