#include "GRenderer.h"
#include <GL/glew.h>

GRenderer::ShaderProgram recProgram;
GRenderer::ShaderProgram texProgram;
float recVertex[8];
float texVertex[16];

unsigned short recIndex[] = {
   0, 1, 2,
   2, 3, 0
};

const char* defaultVert =
"//#shader vert								  \n"
"#version 330                                 \n"
"											  \n"
"layout(location = 0) in vec2 vertex;         \n"
"											  \n"
"uniform vec2 u_size;						  \n"
"uniform vec4 u_globalColor;				  \n"
"											  \n"
"out vec4 o_color;							  \n"
"											  \n"
"void main() {								  \n"
"	vec2 o_vert;							  \n"
"	o_vert.x = (vertex.x / u_size.x) * 2 - 1; \n"
"	o_vert.y = (vertex.y / u_size.y) * 2 - 1; \n"
"	gl_Position = vec4(o_vert, 0, 1);		  \n"
"											  \n"
"	o_color = u_globalColor;				  \n"
"};										      \n";

const char* defaultFrag =
"//#shader frag			 \n"
"#version 330			 \n"
"						 \n"
"out vec4 fragcolor;	 \n"
"						 \n"
"in vec4 o_color;		 \n"
"						 \n"
"void main() {			 \n"
"	fragcolor = o_color; \n"
"}                       \n";

const char* textureVert =
"//#shader vert								  \n"
"#version 330								  \n"
"											  \n"
"layout(location = 0) in vec2 vertex;		  \n"
"layout(location = 1) in vec2 texturecoords;  \n"
"											  \n"
"out vec2 o_texc;							  \n"
"											  \n"
"uniform vec2 u_size;						  \n"
"											  \n"
"void main() {								  \n"
"	vec2 o_vert;							  \n"
"	o_vert.x = (vertex.x / u_size.x) * 2 - 1; \n"
"	o_vert.y = (vertex.y / u_size.y) * 2 - 1; \n"
"	gl_Position = vec4(o_vert, 0, 1);		  \n"
"											  \n"
"	o_texc = texturecoords;					  \n"
"};											  \n";

const char* textureFrag =
"//#shader frag                              \n"
"											 \n"
"#version 330								 \n"
"out vec4 fragcolor;						 \n"
"											 \n"
"in vec2 o_texc;							 \n"
"											 \n"
"uniform sampler2D _texture;				 \n"
"											 \n"
"void main() {								 \n"
"	fragcolor = texture(_texture, o_texc); \n"
"}											 \n";

GGeneral::Dimension<int> defaultViewportSize = {1280, 720};

const bool GGraphics::init() {
	GRenderer::Primitives::Shader v;
	GRenderer::Primitives::Shader f;
	v.sourceShader(defaultVert, GRenderer::Primitives::ShaderTypes::VERTEX_SHADER);
	f.sourceShader(defaultFrag, GRenderer::Primitives::ShaderTypes::FRAGMENT_SHADER);
	v.compileShader();
	f.compileShader();

	recProgram = *(new GRenderer::ShaderProgram({&v, &f}));
	recProgram.link();
	recProgram.bind();

	GMath::vec4<float> vec(1);
	recProgram.set("u_globalColor", vec);
	GMath::vec2<float> size;
	size[0] = defaultViewportSize.width;
	size[1] = defaultViewportSize.height;
	recProgram.set("u_size", size);

	v.sourceShader(textureVert, GRenderer::Primitives::ShaderTypes::VERTEX_SHADER);
	f.sourceShader(textureFrag, GRenderer::Primitives::ShaderTypes::FRAGMENT_SHADER);
	v.compileShader();
	f.compileShader();

	texProgram = *(new GRenderer::ShaderProgram({&v, &f}));
	texProgram.link();
	texProgram.bind();
	texProgram.set("u_size", size);
	return true;
}

void GGraphics::setColor(GGeneral::aRGBColor c) {
	recProgram.bind();
	GMath::vec4<float> v;
	v[0] = c[0] / 255.0f;
	v[1] = c[1] / 255.0f;
	v[2] = c[2] / 255.0f;
	v[3] = c[3] / 255.0f;
	recProgram.set("u_globalColor", v);
}

void GGraphics::setViewport(GGeneral::Dimension<int> s) {
	defaultViewportSize = s;
	GMath::vec2<float> size;
	size[0] = defaultViewportSize.width;
	size[1] = defaultViewportSize.height;
	glViewport(0, 0, size[0], size[1]);
	recProgram.bind();
	recProgram.set("u_size", size);
	texProgram.bind();
	texProgram.set("u_size", size);
}

void GGraphics::drawRect(GGeneral::Rectangle<int> r) {
	recProgram.bind();

	//Prepare the buffer
	recVertex[0] = (float)r.position.x;
	recVertex[1] = (float)r.position.y;
	recVertex[2] = (float)r.position.x;
	recVertex[3] = (float)r.dimension.height + r.position.y;
	recVertex[4] = (float)r.dimension.width + r.position.x;
	recVertex[5] = (float)r.dimension.height + r.position.y;
	recVertex[6] = (float)r.position.x + r.dimension.width;
	recVertex[7] = (float)r.position.y;

	GRenderer::Primitives::VertexBuffer vbuffer(recVertex, 8);
	GRenderer::Primitives::IndexBuffer ibuffer(recIndex, 6);
	GRenderer::Primitives::VertexArray::VertexArrayLayout layout({2}, GRenderer::Primitives::VertexTypes::FLOAT);
	GRenderer::Primitives::VertexArray vertex = GRenderer::Primitives::VertexArray(vbuffer, ibuffer, layout);

	GRenderer::Mesh m(&vertex, nullptr);
	GRenderer::draw(m);
	//Becuase of automatic destruction the destructor of Mesh is not needed
	m.vertex = nullptr;
}

void GGraphics::drawImg(GGeneral::Point<int> pos, const GFile::Graphics::Image& img, GGeneral::Dimension<unsigned int> dim) {
	auto t = GRenderer::Texture(img);
	drawImg(pos, t, dim);
}

void GGraphics::drawImg(GGeneral::Point<int> pos, GRenderer::Texture& tex, GGeneral::Dimension<unsigned int> dim) {
	texProgram.bind();

	GGeneral::Rectangle<int> r;
	if (dim.width + dim.height == 0) {
		r = GGeneral::Rectangle<int>(pos, tex.getSize().width, tex.getSize().height);
	}
	else
		r = GGeneral::Rectangle<int>(pos, dim.width, dim.height);

	//Prepare the buffer
	texVertex[0] = r.position.x;
	texVertex[1] = r.position.y;
	texVertex[2] = 0;
	texVertex[3] = 0;

	texVertex[4] = r.position.x;
	texVertex[5] = r.dimension.height + r.position.y;
	texVertex[6] = 0;
	texVertex[7] = 1;

	texVertex[8] = r.dimension.width + r.position.x;
	texVertex[9] = r.dimension.height + r.position.y;
	texVertex[10] = 1;
	texVertex[11] = 1;

	texVertex[12] = r.position.x + r.dimension.width;
	texVertex[13] = r.position.y;
	texVertex[14] = 1;
	texVertex[15] = 0;

	GRenderer::Primitives::VertexBuffer vbuffer(texVertex, 16);
	GRenderer::Primitives::IndexBuffer ibuffer(recIndex, 6);
	GRenderer::Primitives::VertexArray::VertexArrayLayout layout({2, 2}, GRenderer::Primitives::VertexTypes::FLOAT);
	GRenderer::Primitives::VertexArray vertex = GRenderer::Primitives::VertexArray(vbuffer, ibuffer, layout);

	GRenderer::Mesh m(&vertex, &tex);
	GRenderer::draw(m);
	//Becuase of automatic destruction the destructor of Mesh is not needed
	m.vertex = nullptr;
	m.tex = nullptr;
}