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

float cube[] = {
	// positions          // colors           // texture coords
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
};

//float cube[] = {
//	// positions          // colors           // texture coords
//	 500.0f,  500.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
//	 500.0f, -500.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
//	-500.0f, -500.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
//	-500.0f,  500.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
//};

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

void test(GWindow::WindowEvent e, void* data) {
	LOG(e);
	if (e == GWindow::WindowEvent::WINDOW_RESIZE) {
		auto rect = *(GGeneral::Rectangle<int>*)data;
		//LOGI(rect);
	}
}

int main() {
	GRenderer::init();
	GWindow::Window w;
	w.setState(GWindow::WindowState::NORMAL);
	w.createOpenGLcontext();
	w.setOpenGLContextActive(true);
	w.addCallbackFunction(test);

	LOGS("Everything initialized");
	LOGI(GGeneral::toString("OpenGL Version: ", glGetString(GL_VERSION)));
	GGeneral::Logger::wait();

	GRenderer::Primitives::Shader frag("rsc/shader/frag.frag");
	GRenderer::Primitives::Shader vert("rsc/shader/vert.vert");

	GRenderer::ShaderProgram program({ &frag, &vert });
	program.link();

	auto img2 = GIO::Graphics::loadImage("rsc/img/smile.bmp");

	GGeneral::Logger::wait();
	GRenderer::Texture t2(*img2);

	auto mat = GMath::mat4x4Identity<float>();
	mat.translate(GMath::vec3<float>(0, 0, -3));

	//auto ortho = GMath::perpective<float>(45, 1280 / 720, 0.1, 100);
	auto ortho = GMath::ortho<float>(0, 1280, 0, 720, 0.1, 100);
	ortho = GMath::perpective<float>(45, 1280.0f / 720.0f, 0.1, 100);
	//ortho = GMath::mat4x4Identity<float>();

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
	glUniformMatrix4fv(d, 1, true, ortho.memadd());
	d = program.getUniformLocation("cam");
	glUniformMatrix4fv(d, 1, true, mat.memadd());
	GGeneral::Color c(50, 50, 50);

	auto info = GMemory::getAllocInfo();
	auto alloccount = GET_ALLOC_INFO_COUNT(info);
	for (size_t i = 0; i < alloccount; i++) {
#ifdef EXTENDED_MEMORYTRACKING
		LOG(PRINT_VAR(info[i]->functionSig, info[i]->line, info[i]->size));
#endif
	}

	while (!w.getCloseRequest()) {
		GRenderer::clear(c);
		GRenderer::draw(m);
		GWindow::Window::fetchEvents();
		w.swapBuffers();
	}

	info = GMemory::getAllocInfo();
	alloccount = GET_ALLOC_INFO_COUNT(info);
	for (size_t i = 0; i < alloccount; i++) {
#ifdef EXTENDED_MEMORYTRACKING
		LOG(PRINT_VAR(info[i]->functionSig, info[i]->line, info[i]->size));
#endif
	}
	GGeneral::Logger::wait();
	GGeneral::Logger::terminateThread();
}