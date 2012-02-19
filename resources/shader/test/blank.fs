
#version 130

out vec4 color;
 
in vec3 vertex;

void main(void)
{
	color = vec4( 0.0 );
    
	if( mod( vertex.x , 16.0 ) > 15.5 || mod( vertex.z , 16.0 ) > 15.5 ) 
	{
//		color = vec4(.20, .40, .90, 1.0);
		color = vec4( 0.8 , 0.8 , 0.2 , 1.0 );
	}
}