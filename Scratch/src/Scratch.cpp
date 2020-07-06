#pragma once

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

//float cube[] = {
//	// positions          // colors           // texture coords
//	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
//	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
//};

float cube[] = {
	// positions          // colors           // texture coords
	 50.0f,  50.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
	 50.0f, -50.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	-50.0f, -50.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	-50.0f,  50.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
};

unsigned short index[] = {
	0, 1, 3,
	1, 2, 3
};

/*
int main() {
	using namespace GGeneral;
	GRenderer::init();
	for (unsigned int i = 0; i < 10; i++) {
		auto s = new String("dawe");
		if (i % 2 == 0)
			delete s;
	}
	auto info = GMemory::getAllocInfo();
	auto j = GMemory::getCurrentAllocationCount();
	for (size_t i = 0; i < j; i++) {
		LOGI("Adress: ", info[i]->address, " Signature: ", info[i]->functionSig);
	}

	GGeneral::Logger::wait();
	GGeneral::Logger::terminateThread();
}*/

//#undef LOG
//#define LOG(...) std::cout << GGeneral::toString(__VA_ARGS__) << "\n"

int main() {
	GRenderer::init();
	GWindow::Window w;
	w.setState(GWindow::WindowState::NORMAL);
	w.initOpenGLContext();
	w.setOpenGLContextActive(true);
	glewInit();
	LOG("Everything initialized");
	LOG(GGeneral::toString("OpenGL Version: ", glGetString(GL_VERSION)));
	GGeneral::Logger::wait();

	GRenderer::Primitives::Shader frag("rsc/shader/frag.frag");
	GRenderer::Primitives::Shader vert("rsc/shader/vert.vert");

	GRenderer::ShaderProgram program({ &frag, &vert });
	program.link();

	auto img2 = GIO::Graphics::loadImage("rsc/img/smile.bmp");

	GGeneral::Logger::wait();
	GRenderer::Texture t2(*img2);

	auto mat = GMath::mat4x4Identity<float>();
	//mat.translate(GMath::vec3(1, 0, 0));
	double angle = G_PI / 4;
	mat[0][0] = cos(angle);
	mat[0][1] = -sin(angle);
	mat[1][0] = sin(angle);
	mat[1][1] = cos(angle);

	auto ortho = GMath::mat4x4Identity<float>();
#undef near
#undef far
	double right = 1280, left = -1280, up = 720, down = -720, far = 100, near = 0.1;
	ortho[0][0] = 2 / (right - left);
	ortho[1][1] = 2 / (up - down);
	ortho[2][2] = 2 / (far - near);
	ortho[0][3] = -((right + left) / (right - left));
	ortho[1][3] = -((up + down) / (up - down));
	ortho[2][3] = -((far + near) / (far - near));

	GRenderer::Primitives::VertexBuffer v(cube, 36, 6);
	GRenderer::Primitives::IndexBuffer i(index, 6);
	GRenderer::Primitives::VertexArray::VertexArrayLayout l({ 3, 3, 2 }, GRenderer::Primitives::VertexTypes::FLOAT);
	GRenderer::Primitives::VertexArray vertex(v, i, l);
	GRenderer::Mesh m;
	m.tex = t2;
	m.vertex = vertex;

	vertex.bind();
	program.bind();
	auto d = program.getUniformLocation("mat");
	glUniformMatrix4fv(d, 1, false, ortho.memadd());
	GGeneral::Color c(50, 50, 50);

	auto info = GMemory::getAllocInfo();
	auto alloccount = GET_ALLOC_INFO_COUNT(info);
	for (size_t i = 0; i < alloccount; i++) {
		LOG(PRINT_VAR(info[i]->functionSig, info[i]->line, info[i]->size));
	}

	while (!w.getCloseRequest()) {
		GRenderer::clear(c);
		GRenderer::draw(m);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
		GWindow::Window::fetchEvents();
		w.swapBuffers();
	}
	GGeneral::Logger::wait();
	GGeneral::Logger::terminateThread();
}