
#version 130

uniform mat4 model;
uniform mat4 lense;

void main(void)
{
   gl_Position = lense * model * gl_Vertex;
}
