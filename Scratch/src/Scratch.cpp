#include <GRenderer.h>
#include <iostream>
#include <Windows.h>
#include "GLEW/include/GL/glew.h"

float vertices[] = {
	// positions         // colors
	 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
	 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
};

float cube[] = {
	// positions          // colors           // texture coords
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
};

unsigned short index[] = {
	0, 1, 3,
	1, 2, 3
};

int main() {
	GGeneral::Logger::init();

	//GWindow::Window w;
	//GWindow::Monitor::init();
	//
	//w.setState(GWindow::WindowState::NORMAL);
	//w.initOpenGLContext();
	//w.setOpenGLContextActive(true);
	//glewInit();
	//LOGS("Everything initialized");
	//LOG(GGeneral::toString("OpenGL Version: ", glGetString(GL_VERSION)));
	//GGeneral::Logger::wait();
	//
	//GRenderer::Primitives::Shader frag("rsc/shader/frag.frag");
	//GRenderer::Primitives::Shader vert("rsc/shader/vert.vert");
	//
	//GRenderer::ShaderProgram program({ &frag, &vert });
	//program.link();
	//
	//GGeneral::Time::Timer timer;
	//auto img = GIO::Graphics::loadImage("rsc/img/color.bmp");
	//LOG(timer.stop());
	//GGeneral::Logger::wait();
	//GRenderer::Texture t(*img);
	//t.bind();
	////location = program.getUniformLocation("img");
	////glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//
	//GRenderer::Primitives::VertexBuffer v(cube, 36);
	//GRenderer::Primitives::IndexBuffer i(index, 6);
	//GRenderer::Primitives::VertexArray::VertexArrayLayout l({ 3, 3 , 2 }, GRenderer::Primitives::VertexTypes::FLOAT);
	//GRenderer::Primitives::VertexArray vertex(v, i, l);
	//
	//vertex.bind();
	//GGeneral::Color c(50, 50, 50);
	//while (!w.getCloseRequest()) {
	//	program.bind();
	//	GRenderer::clear(c);
	//	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
	//	//glDrawArrays(GL_TRIANGLES, 0, 3);
	//	GWindow::Window::fetchEvents();
	//	w.swapBuffers();
	//}

	GGeneral::Point3D<unsigned int>p(2, 3);
	GGeneral::Dimension3D<int> d(1);
	LOG(p, d);

	GGeneral::Logger::wait();
	GGeneral::Logger::terminateThread();
}