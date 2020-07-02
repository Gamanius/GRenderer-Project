#pragma once

#include <iostream>
#include <GRenderer.h>
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
	GRenderer::init();
	GWindow::Window w;

	w.setState(GWindow::WindowState::NORMAL);
	w.initOpenGLContext();
	w.setOpenGLContextActive(true);
	glewInit();
	LOGS("Everything initialized");
	LOG(GGeneral::toString("OpenGL Version: ", glGetString(GL_VERSION)));
	GGeneral::Logger::wait();

	GRenderer::Primitives::Shader frag("rsc/shader/frag.frag");
	GRenderer::Primitives::Shader vert("rsc/shader/vert.vert");

	GRenderer::ShaderProgram program({ &frag, &vert });
	program.link();

	auto img = GIO::Graphics::loadImage("rsc/img/color.bmp");
	auto img2 = GIO::Graphics::loadImage("rsc/img/smile.bmp");

	GGeneral::Logger::wait();
	GRenderer::Texture t2(*img2);
	t2.bind();

	auto mat = GMath::mat4x4Identity<float>();
	//mat.translate(GMath::vec3(1, 0, 0));
	double angle = G_PI;
	mat[0][0] = cos(angle);
	mat[0][1] = -sin(angle);
	mat[1][0] = sin(angle);
	mat[1][1] = cos(angle);

	GRenderer::Primitives::VertexBuffer v(cube, 36);
	GRenderer::Primitives::IndexBuffer i(index, 6);
	GRenderer::Primitives::VertexArray::VertexArrayLayout l({ 3, 3 , 2 }, GRenderer::Primitives::VertexTypes::FLOAT);
	GRenderer::Primitives::VertexArray vertex(v, i, l);

	vertex.bind();
	program.bind();
	auto d = program.getUniformLocation("mat");
	glUniformMatrix4fv(d, 1, false, mat.memadd());
	GGeneral::Color c(50, 50, 50);
	while (!w.getCloseRequest()) {
		GRenderer::clear(c);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		GWindow::Window::fetchEvents();
		w.swapBuffers();
	}
	GGeneral::Logger::wait();
	GGeneral::Logger::terminateThread();
}