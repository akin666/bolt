
#version 130

uniform mat4 model;
uniform mat4 lense;

in vec3 vertex;
in vec2 textureCoordinates;

out vec2 textureUV;

void main(void)
{
   vec4 pos = vec4( vertex , 1.0 );
   gl_Position = lense * model * pos;
   
   textureUV = textureCoordinates;
}
