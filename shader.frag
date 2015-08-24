#version 330 core

// some often used snippets:
//
//#define EPS    1e-4
//#define TWOPI  6.283185307179586
//#define PI     3.141592653589793
//#define PIHALF 1.570796326794897
//
// vec2 uv = (2.*gl_FragCoord.xy - resolution.xy)/min(resolution.x, resolution.y);
//
// uniform float time; uniform vec2 resolution;
//
// float rand(vec2 c){ return fract(sin(c.x+2.4*sin(c.y))*34.1234); }
//
// vec3 rotateX(vec3 p, float phi) { float c = cos(phi); float s = sin(phi); return vec3(p.x, c*p.y - s*p.z, s*p.y + c*p.z); }
// vec3 rotateY(vec3 p, float phi) { float c = cos(phi); float s = sin(phi); return vec3(c*p.x + s*p.z, p.y, c*p.z - s*p.x); }
// vec3 rotateZ(vec3 p, float phi) { float c = cos(phi); float s = sin(phi); return vec3(c*p.x - s*p.y, s*p.x + c*p.y, p.z); }
//
//vec3 normal(vec3 p) {
//	vec2 e = vec2(EPS, 0);
//	float d = scene(p);
//	return normalize(vec3(d-scene(p+e.xyy), d-scene(p+e.yxy), d-scene(p+e.yyx)));
//}
//

#ifdef GL_ES
	precision highp int;
	precision highp float;
#endif

uniform vec2 resolution;
uniform float time;

const int iters = 130;

void main() {
	vec2 pos = (2.*gl_FragCoord.xy - resolution.xy)/min(resolution.x, resolution.y);
	pos.x -= .5;

	vec2 z = vec2(0);
	int n = 0;
	while (n < iters) {
		if(dot(z,z) > 10.) break;
		z = vec2(z.x*z.x - z.y*z.y + pos.x, 2.*z.x*z.y + pos.y);
		n++;
	}

	// smooth coloring from: http://linas.org/art-gallery/escape/smooth.html
	float c = float(n) + 1. - log(log(length(z)))/0.6931471805599453;
	gl_FragColor = vec4((-cos(.025*c+time)+1.)/2., (-cos(.08*c+time)+1.)/2., (-cos(.12*c+time)+1.)/2., 1);
}
