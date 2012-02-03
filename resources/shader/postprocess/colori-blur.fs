
#version 140

// This texture should hold the image to blur.
// This can perhaps be a previous rendered scene.
uniform sampler2D tex;
uniform float effect;
 
// texture coordinates passed from the vertex shader
in vec2 uv;
out vec4 out_color;
 
void main(void)
{
	float siz = effect * 0.01;
    vec4 colorr = texture2D(tex,uv + vec2(siz,siz)); 
    vec4 colorg = texture2D(tex,uv + vec2(-siz,-siz)); 
    vec4 colorb = texture2D(tex,uv); 
 
    out_color = vec4( colorr.r , colorg.g , colorb.b , colorb.a );
}
