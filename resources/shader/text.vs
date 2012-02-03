
#version 130

uniform mat4 model;
uniform mat4 lense;
uniform mat4 texMatrix;

in vec3 vertex;
in vec4 vertexColor;
in vec2 coordinates;

out vec2 texUv;
out vec4 texColor;

void main(void)
{
   vec4 pos = vec4( vertex , 1.0 );
   gl_Position = lense * model * pos;
   
   vec4 uvpos = texMatrix * vec4( coordinates , 1.0 , 1.0 );
   
   texUv = uvpos.xy;
   texColor = vertexColor;
}
