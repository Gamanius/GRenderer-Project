#pragma once

#include <GRenderer.h>
#include <iostream>

float vertices[] = {
   -0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f,  0.5f, 0.0f
};

float planeVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
};
GWindow::Window* w;

int main() {
	if (!GRenderer::init()) {
		LOGF("Couldn't init");
		GGeneral::ErrorHandler::printAll();
		GGeneral::Logger::wait();
		return -1;
	}
	LOGS("Initialized successfully");
	LOGI("Using GRenderer Version: ", G_RENDERER_VERSION);

	w = new GWindow::Window("Heyo", { 100, 100 }, { 1920, 1080 });
	auto window = *w;
	window.createOpenGLcontext();
	window.setOpenGLContextActive(true);
	window.setState(GWindow::WindowState::NORMAL);

	GRenderer::Primitives::Shader frag("rsc/shader/framebuffer.frag");
	GRenderer::Primitives::Shader vert("rsc/shader/framebuffer.vert");
	GRenderer::ShaderProgram program({ &frag, &vert });
	program.link();
	program.bind();

	GRenderer::Primitives::VertexBuffer buffer(planeVertices, 24, 6);
	GRenderer::Primitives::VertexArray array(buffer, GRenderer::Primitives::VertexArray::VertexArrayLayout({ 2, 2 }, GRenderer::Primitives::VertexTypes::FLOAT));
	array.bind();

	GGeneral::String filepath = "rsc/img/s.png";
	auto test = GFile::Graphics::isParseble(filepath);
	auto img = GFile::Graphics::loadImage(filepath);
	img->flip();
	auto tex = GRenderer::Texture(*img);

	GRenderer::Mesh mesh(&array, &tex);

	while (!window.getCloseRequest()) {
		GRenderer::clear({ 50 });
		GRenderer::draw(mesh);
		window.swapBuffers();
		window.fetchEvents();
	}

	mesh.vertex = nullptr;
	mesh.tex = nullptr;
	GGeneral::ErrorHandler::printAll();
	LOGS("Good bye");
	GGeneral::Logger::wait();
}