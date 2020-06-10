//#shader frag
#version 330

out vec4 fragcolor;

in vec2 tex;
in vec3 vcol;

uniform vec3 color;
uniform sampler2D img;

void main() {
	//fragcolor = vec4(color, 1);
	fragcolor =  texture(img, tex);
	fragcolor = vec4(vcol, 1);
}