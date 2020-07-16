#include "../GRenderer.h"

GRenderer::ShaderProgram program;
GRenderer::Mesh cubeMesh;

const char* defaultVert = "//#shader vert \n #version 330\nlayout(location = 0) in vec3 pos;\n uniform vec4 u_globalColor;\n out vec4 o_globalColor; \n void main() { \n gl_Position = vec4(pos, 1); \n o_globalColor = u_globalColor;\n } \n";
const char* defaultFrag = "//#shader frag \n #version 330 \n out vec4 o_color; in vec4 o_globalColor; void main() { o_color = o_globalColor; }";

float cube[] = {
	// positions
	 0.5f,  0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	-0.5f,  0.5f, 0.0f
};

unsigned short cubeindex[] = {
	0, 1, 3,
	1, 2, 3
};

const bool GGraphics::init() {
	//GRenderer::Primitives::Shader v("src/core/graphics/shader/default.vert");
	//GRenderer::Primitives::Shader f("src/core/graphics/shader/default.frag");
	GRenderer::Primitives::Shader v;
	GRenderer::Primitives::Shader f;
	v.sourceShader(defaultVert, GRenderer::Primitives::ShaderTypes::VERTEX_SHADER);
	f.sourceShader(defaultFrag, GRenderer::Primitives::ShaderTypes::FRAGMENT_SHADER);
	v.compileShader();
	f.compileShader();

	program = *(new GRenderer::ShaderProgram({ &v, &f }));
	program.link();
	program.bind();
	GMath::vec4<float> vec(1);
	program.set("u_globalColor", vec);

	GRenderer::Primitives::VertexBuffer* vbuffer = new GRenderer::Primitives::VertexBuffer(cube, 36);
	GRenderer::Primitives::IndexBuffer* ibuffer = new GRenderer::Primitives::IndexBuffer(cubeindex, 6);
	GRenderer::Primitives::VertexArray::VertexArrayLayout layout({ 3 }, GRenderer::Primitives::VertexTypes::FLOAT);
	GRenderer::Primitives::VertexArray* vertex = new GRenderer::Primitives::VertexArray(*vbuffer, *ibuffer, layout);

	cubeMesh.vertex = vertex;
	return true;
}

void GGraphics::setColor(GGeneral::aColor c) {
	program.bind();
	GMath::vec4<float> v;
	v[0] = c[0] / 255.0f;
	v[1] = c[1] / 255.0f;
	v[2] = c[2] / 255.0f;
	v[3] = c[3] / 255.0f;
	program.set("u_globalColor", v);
}

void GGraphics::drawRect(GGeneral::Rectangle<int> r) {
	program.bind();
	GRenderer::draw(cubeMesh);
}