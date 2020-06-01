#include <GRenderer.h>
#include <iostream>
#include <Windows.h>
#include "GLEW/include/GL/glew.h"

float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left
		 0.5f, -0.5f, 0.0f, // right
		 0.0f,  0.5f, 0.0f  // top
};

unsigned short index[] = {
	0, 1, 2
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

	GRenderer::Primitives::Shader frag("rsc/shader/frag.frag");
	GRenderer::Primitives::Shader vert("rsc/shader/vert.vert");

	GRenderer::ShaderProgram program({ &frag, &vert });
	program.link();
	LOG(program.getInfoMessage());

	GRenderer::Primitives::VertexBuffer v(vertices, 9);
	GRenderer::Primitives::IndexBuffer i(index, 3);
	GRenderer::Primitives::VertexArray::VertexArrayLayout l({ 3 }, GRenderer::Primitives::VertexTypes::FLOAT);
	GRenderer::Primitives::VertexArray vertex(v, i, l);

	vertex.bind();
	while (!w.getCloseRequest()) {
		program.bind();
		glClearColor(0.5, 0.5, 0.5, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, nullptr);
		GWindow::Window::fetchEvents();
		w.swapBuffers();
	}
	GGeneral::Logger::wait();
	GGeneral::Logger::terminateThread();
}