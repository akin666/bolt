
#version 130

uniform sampler2D tex;

in vec2 texUv;
in vec4 texColor;
out vec4 color;
 
void main(void)
{
    vec4 fetched_color = texture2D(tex,texUv);
    
    color = fetched_color * texColor;
}
