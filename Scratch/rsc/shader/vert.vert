#version 330
//#shader vert

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;
layout (location = 2) in vec2 texc;

out vec2 tex;
out vec3 vcol;

uniform mat4 mat;

void main() {
	gl_Position =  mat * vec4(pos, 1);
	tex = texc;
	vcol = col; 
}