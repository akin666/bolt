
#version 130

uniform sampler2D texture;

in vec2 textureUV;
out vec4 color;
 
void main(void)
{
    vec4 fetched_color = texture2D(texture,textureUV);
    
    color = fetched_color;
}
