//#shader frag
#version 330

out vec4 fragcolor;

in vec4 o_color;

void main() {
	fragcolor = o_color;
}