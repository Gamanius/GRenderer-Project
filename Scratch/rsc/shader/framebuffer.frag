//#shader frag

#version 330 
out vec4 fragcolor;

in vec2 texcoord;

uniform sampler2D _texture;

void main() {    
	fragcolor = texture(_texture, texcoord);
}