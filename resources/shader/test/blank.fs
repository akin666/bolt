
#version 130

out vec4 color;
 
in vec3 vertex;

void main(void)
{
	color = vec4( 0.0 );
    
	if( mod( vertex.x , 16.0 ) > 15.0 || mod( vertex.z , 16.0 ) > 15.0 ) 
	{
		color = vec4( 1.0 );
//		color = vec4( 1.0 , 1.0 , 1.0 , 1.0 );
	}
}