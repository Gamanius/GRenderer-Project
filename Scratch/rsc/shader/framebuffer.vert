////#shader vert
//
//#version 330 
//layout (location = 0) in vec2 aPos;
//layout (location = 1) in vec2 aTexCoords;
//
//out vec2 TexCoords;
//
//void main() {
//    TexCoords = aTexCoords;
//    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0); 
//}  

//#shader vert								 
#version 330                                
											 
layout(location = 0) in vec2 vertex;        
layout(location = 1) in vec2 texturecoords;

out vec2 o_texc;			

uniform vec2 u_size;						 
											 
void main() {								 
	vec2 o_vert;							 
	o_vert.x = (vertex.x / u_size.x) * 2 - 1;
	o_vert.y = (vertex.y / u_size.y) * 2 - 1;
	gl_Position = vec4(o_vert, 0, 1);		
	
	o_texc = texturecoords;
};										     