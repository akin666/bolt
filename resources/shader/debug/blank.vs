
#version 130

uniform mat4 model;
uniform mat4 lense;

out vec3 vertex;

void main(void)
{
   gl_Position = lense * model * gl_Vertex;
   vertex = gl_Vertex.xyz;
}
