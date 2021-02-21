#include "GRenderer.h"
#include <GL/glew.h>

unsigned long lastDeltaT = 0;
unsigned long lastDDeltaT = 0;

const bool GRenderer::init() {
	if (!GGeneral::Logger::init()) {
		THROWW("Couldn't init Logger");
		return false;
	}
	if (!GWindow::init()) {
		THROWF("Couldn't init window class and OpenGL");
		return false;
	}
	if (!GWindow::Monitor::init()) {
		THROWW("Couldn't init Monitor namespace");
		return false;
	}
	if (!GNetworking::init()) {
		THROWF("Couldn't init networking namespace");
		return false;
	}
	//if (!GGraphics::init())
	//	return false;
	return true;
}

const GGeneral::String GRenderer::getVersion() {
	return GGeneral::String(G_RENDERER_VERSION);
}

GGeneral::String GRenderer::getCurentOpenGLVersion() {
	GGeneral::String r(glGetString(GL_VERSION));
	return r;
}

void GRenderer::enableBlend() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

double GRenderer::delta() {
	if (lastDeltaT == 0) {
		lastDeltaT = GGeneral::Time::getNanoTime() / 1000000;
		return 0;
	}
	unsigned long t = GGeneral::Time::getNanoTime() / 1000000;
	auto temp = t - lastDeltaT;
	lastDeltaT = t;
	return temp;
}

double GRenderer::ddelta() {
	unsigned long t = GGeneral::Time::getNanoTime() / 1000000;
	auto temp = t - lastDDeltaT;
	return temp;
}

GGeneral::String GRenderer::getGLString(GLString s) {
	const GLubyte* string;
	switch (s) {
	case GRenderer::GLString::VENDOR:		  string = glGetString(GL_VENDOR);					 break;
	case GRenderer::GLString::RENDERER:		  string = glGetString(GL_RENDERER);				 break;
	case GRenderer::GLString::VERSION:		  string = glGetString(GL_VERSION);					 break;
	case GRenderer::GLString::SHADER_VERSION: string = glGetString(GL_SHADING_LANGUAGE_VERSION); break;
	default: return GGeneral::String("UNKNOWN");
	}
	if (string == 0)
		return GGeneral::String("UNKNOWN");
	return string;
}

void GRenderer::clear(GGeneral::RGBColor color) {
	glClearColor(((float)color[0]) / 255, ((float)color[1]) / 255, ((float)color[2]) / 255, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}

void GRenderer::setWireFrameMode(bool b) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE + !b);
}

void GRenderer::draw(Mesh& m, GRenderer::FrameBuffer* buffer) {
	if (m.tex != nullptr)
		m.tex->bind();
	if (buffer == nullptr)
		GRenderer::FrameBuffer::unbind();
	else
		buffer->bind();
	m.vertex->bind();
	if (m.vertex->isOnlyVertex()) {
		glDrawArrays(GL_TRIANGLES, 0, m.vertex->getAmount());
	}
	else {
		GLenum type;
		switch (m.vertex->getIndexType()) {
		case GRenderer::Primitives::IndexTypes::UNSIGNED_BYTE:	 type = GL_UNSIGNED_BYTE;  break;
		case GRenderer::Primitives::IndexTypes::UNSIGNED_SHORT:	 type = GL_UNSIGNED_SHORT; break;
		default:	                                             type = GL_UNSIGNED_INT;   break;
		}
		glDrawElements(GL_TRIANGLES, m.vertex->getAmount(), type, nullptr);
	}
	//Unbind any buffer
	GRenderer::FrameBuffer::unbind();

	//Time
	lastDDeltaT = GGeneral::Time::getNanoTime() / 1000000;
}