#version 330
//#shader vert

layout (location = 0) in vec2 vertex;

uniform vec2 u_size;
uniform vec4 u_color;

out vec4 o_color;

void main() {
	vec2 o_vert;
	o_vert.x = (vertex.x / u_size.x) * 2 - 1;
	o_vert.y = (vertex.y / u_size.y) * 2 - 1;
	gl_Position =  vec4(o_vert, 0, 1);

	o_color = u_color;
}