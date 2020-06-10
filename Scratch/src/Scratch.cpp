#include <GRenderer.h>
#include <iostream>
#include <Windows.h>
#include "GLEW/include/GL/glew.h"

float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left
		 0.5f, -0.5f, 0.0f, // right
		 0.5f,  0.5f, 0.0f, // top
		-0.5f,  0.5f, 0.0f
};

float cube[] = {
	// positions // colors // texture coords
	0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	// top right
	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	// bottom right
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	// bottom left
	-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f
	// top left
};

unsigned short index[] = {
	0, 1, 3,
	1, 2, 3
};

int main() {
	GGeneral::Logger::init();

	GWindow::Window w;
	GWindow::Monitor::init();

	w.setState(GWindow::WindowState::NORMAL);
	LOG(w.initOpenGLContext());
	w.setOpenGLContextActive(true);
	LOG(glewInit());
	LOG(GGeneral::toString("OpenGL Version: ", glGetString(GL_VERSION)));
	GGeneral::Logger::wait();
	LOG(GGeneral::OS::getUserName());
	LOGI(GIO::getWorkingDirectionary());

	GRenderer::Primitives::Shader frag("rsc/shader/frag.frag");
	GRenderer::Primitives::Shader vert("rsc/shader/vert.vert");

	GRenderer::ShaderProgram program({ &frag, &vert });
	program.link();
	LOG(program.getInfoMessage());

	program.bind();
	GMath::vec3<float> color(0.3);
	auto location = program.getUniformLocation("color");
	glUniform3fv(location, 1, color.memadd());

	auto img = GIO::Graphics::loadImage("rsc/img/color.bmp");
	GRenderer::Texture t(*img);
	t.bind();
	//location = program.getUniformLocation("img");

	GRenderer::Primitives::VertexBuffer v(cube, 32);
	GRenderer::Primitives::IndexBuffer i(index, 6);
	GRenderer::Primitives::VertexArray::VertexArrayLayout l({ 3, 3, 2 }, GRenderer::Primitives::VertexTypes::FLOAT);
	GRenderer::Primitives::VertexArray vertex(v, i, l);

	vertex.bind();
	GGeneral::Color c(50, 50, 50);
	while (!w.getCloseRequest()) {
		program.bind();
		GRenderer::clear(c);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
		GWindow::Window::fetchEvents();
		w.swapBuffers();
	}
	GGeneral::Logger::wait();
	GGeneral::Logger::terminateThread();
}