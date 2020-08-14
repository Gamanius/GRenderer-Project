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

static void callback(GWindow::Window* w, bool pressed, GWindow::VK key) {
	LOGI(key);
	if (key == GWindow::VK::ESCAPE)
		w->forceCloseRequest();
}

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

	w = new GWindow::Window();
	auto window = *w;
	window.createOpenGLcontext();
	window.setOpenGLContextActive(true);
	window.setState(GWindow::WindowState::NORMAL);
	GEventWrapper::Windowhandler handler(w);
	handler.addCallback(callback);

	GRenderer::Primitives::VertexBuffer vertexbuffer(vertices, 9);
	GRenderer::Primitives::VertexArray varray(vertexbuffer, GRenderer::Primitives::VertexArray::VertexArrayLayout({ 3 }, GRenderer::Primitives::VertexTypes::FLOAT));
	GRenderer::Mesh m(&varray, nullptr);

	GRenderer::Primitives::VertexBuffer planevertexbuffer(planeVertices, 24, 6);
	GRenderer::Primitives::VertexArray planevarray(planevertexbuffer, GRenderer::Primitives::VertexArray::VertexArrayLayout({ 2, 2 }, GRenderer::Primitives::VertexTypes::FLOAT));
	GRenderer::Mesh m2(&planevarray, nullptr);

	GRenderer::Primitives::Shader frag("rsc/shader/frag.frag");
	GRenderer::Primitives::Shader vert("rsc/shader/vert.vert");
	GRenderer::ShaderProgram program({ &vert, &frag });
	program.link();

	GRenderer::FrameBuffer fbuffer;
	fbuffer.attachTex(window.getWindowDrawSize());
	fbuffer.unbind();
	m2.tex = const_cast<GRenderer::Texture*>(fbuffer.getBoundTexture());

	GRenderer::Primitives::Shader framebuffervert("rsc/shader/framebuffer.frag");
	GRenderer::Primitives::Shader framebufferfrag("rsc/shader/framebuffer.vert");
	GRenderer::ShaderProgram program2({ &framebuffervert, &framebufferfrag });
	program2.link();

	GGamepad::Gamepad pad(0);
	pad.vibrate(1, GAMEPAD_LEFT_MOTOR);

	while (!window.getCloseRequest()) {
		program.bind();
		fbuffer.bind();
		GRenderer::clear({ 50, 50, 50 });
		GRenderer::draw(m, &fbuffer);

		program2.bind();
		GRenderer::draw(m2);

		window.swapBuffers();
		window.fetchEvents();
	}

	//Don't call the destructor twice!
	m.vertex = nullptr;
	m2.tex = nullptr;
	m2.vertex = nullptr;
	GGeneral::ErrorHandler::printAll();
	LOGS("Good bye");
	GGeneral::Logger::wait();
}