// Starfield effect, extracted from: http://glsl.heroku.com/e#883.0
 
//uniform float time;
//uniform vec2 resolution;
//
//float rand (float x) {
//	return fract(sin(x * 24614.63) * 36817.342);	
//}
//
//void main(void)
//{
//	float scale = sin(0.1 * time) * 0.5 + 5.0;
//	float distortion = resolution.y / resolution.x;
//
//	vec2 position = (((gl_FragCoord.xy * 0.8 / resolution) ) * scale) + scale*0.1;
//	position.y *= distortion;
//
//	float gradient = 0.0;
//	vec3 color = vec3(0.0);
// 
//	float fade = 0.0;
//	float z;
// 
//	vec2 centered_coord = position - vec2(2.0);
//
//	for (float i=1.0; i<=64.0; i++)
//	{
//		vec2 star_pos = vec2(sin(i) * 200.0, sin(i*i*i) * 300.0);
//		float z = mod(i*i - 200.0*time, 512.0);
//		float fade = (256.0 - z) /200.0;
//		vec2 blob_coord = star_pos / z;
//		gradient += ((fade / 1800.0) / pow(length(centered_coord - blob_coord ), 1.5)) * ( fade);
//	}
//
//	color = vec3( gradient * 3.0 , max( rand (gradient*1.0)*0.2 , 4.0*gradient) , gradient / 2.0 );
//
//	gl_FragColor = vec4(color, 1.0 );
//}



precision mediump float;
uniform vec2 resolution;
uniform float time;

float halfpi = asin(1.0);
#define cos(_theta_) sin((_theta_)+halfpi)

void main() {

	vec2 p = -1.0 + 2.0 * gl_FragCoord.xy / resolution.xy;
	float a = time*40.0;
	float d,e,f,g=1.0/40.0,h,i,r,q;
	e=400.0*(p.x*0.5+0.5);
	f=400.0*(p.y*0.5+0.5);
	i=200.0+sin(e*g+a/150.0)*20.0;
	d=200.0+cos(f*g/2.0)*18.0+cos(e*g)*7.0;
	r=sqrt(pow(i-e,2.0)+pow(d-f,2.0));
	q=f/r;
	e=(r*cos(q))-a/2.0;f=(r*sin(q))-a/2.0;
	d=sin(e*g)*176.0+sin(e*g)*164.0+r;
	h=((f+d)+a/2.0)*g;
	i=cos(h+r*p.x/1.3)*(e+e+a)+cos(q*g*6.0)*(r+h/3.0);
	h=sin(f*g)*144.0-sin(e*g)*212.0*p.x;
	h=(h+(f-e)*q+sin(r-(a+h)/7.0)*10.0+i/4.0)*g;
	i+=cos(h*2.3*sin(a/350.0-q))*184.0*sin(q-(r*4.3+a/12.0)*g)+tan(r*g+h)*184.0*cos(r*g+h);
	i=mod(i/5.6,256.0)/64.0;
	if(i<0.0) i+=4.0;
	if(i>=2.0) i=4.0-i;
	d=r/350.0;
	d+=sin(d*d*8.0)*0.52;
	f=(sin(a*g)+1.0)/2.0;
	gl_FragColor=vec4(vec3(f*i/1.6,i/2.0+d/13.0,i)*d*p.x+vec3(i,i/2.0+d/18.0,i)*d*(1.0-p.x),1.0);
}
