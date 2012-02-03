lsdlvdsbnvlj INCOMPLETE
// This texture should hold the image to blur.
// This can perhaps be a previous rendered scene.
uniform sampler2D tex;
uniform float effect;
uniform float position;
 
// texture coordinates passed from the vertex shader
varying vec2 uv;
 
void main(void)
{
	// some sample positions
	float samples[10] = float[](-0.08,-0.05,-0.03,-0.02,-0.01,0.01,0.02,0.03,0.05,0.08);
 	
 	float distance = 0.5 - uv.y;
 	
 	
 	float angle = 90.0 * effect;
 	
 	//
 	// effect 
 	// 
 	
 	
 	
    // 0.5,0.5 is the center of the screen
    // so substracting uv from it will result in
    // a vector pointing to the middle of the screen
    vec2 dir = 0.5 - uv; 
 
    // calculate the distance to the center of the screen
    float dist = sqrt(dir.x*dir.x + dir.y*dir.y); 
 
    // normalize the direction (reuse the distance)
    dir = dir/dist;
    
    // this is the original colour of this fragment
    // using only this would result in a nonblurred version
    vec4 color = texture2D(tex,uv); 
 
    vec4 sum = color;
 
    // take 10 additional blur samples in the direction towards
    // the center of the screen
    for (int i = 0; i < 10; i++)
    {
      sum += texture2D( tex, uv + dir * samples[i] * effect );
    }
 
    // we have taken eleven samples
    sum *= 1.0/11.0;
 
    //Blend the original color with the averaged pixels
    gl_FragColor = sum;
}
