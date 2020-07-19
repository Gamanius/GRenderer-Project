#pragma once

#include <GRenderer.h>

float x = 0;
float y = 710;
float w = 10;
float h = 10;

float rectangle[] = {
	x, y,
	x, h + y,
	x + w, y + h,
	x + w, y,
};

unsigned short index[] = {
	0, 1, 2,
	2, 3, 0
};

float cube[] = {
	0.5, 0.5,
	-0.5, 0.5,
	0.5, -0.5
};

int main() {
	LOGI("Initiating!");
	GRenderer::init();

	GWindow::Window w("Test", { 50, 50 }, { 1280, 720 });
	w.createOpenGLcontext();
	w.setOpenGLContextActive(true);
	w.setState(GWindow::WindowState::NORMAL);
	LOGS("Initialed!");

	using namespace GRenderer;
	Primitives::Shader frag("rsc/shader/frag.frag");
	Primitives::Shader vert("rsc/shader/vert.vert");

	ShaderProgram program({ &frag, &vert });
	program.link();
	program.bind();
	GMath::vec2<float> size;
	size[0] = 1280;
	size[1] = 720;
	program.set("u_size", size);
	GMath::vec4<float> color(0.5);
	program.set("u_color", color);

	Primitives::VertexBuffer buffer(rectangle, 8, 4);
	Primitives::VertexArray::VertexArrayLayout layout({ 2 }, Primitives::VertexTypes::FLOAT);
	Primitives::IndexBuffer ibuf(index, 6);
	Primitives::VertexArray* array = new Primitives::VertexArray(buffer, ibuf, layout);
	array->bind();
	Mesh m(array, nullptr);

	while (!w.getCloseRequest()) {
		clear({ 100, 100, 100 });
		draw(m);
		w.swapBuffers();
		w.fetchEvents();
	}
}