//#shader frag

#version 330 
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

void main()
{    
	FragColor = vec4(vec3(1.0 - texture(texture1, TexCoords)), 1.0);
}