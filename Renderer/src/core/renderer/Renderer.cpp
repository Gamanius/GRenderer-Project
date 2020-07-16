#include "../GRenderer.h"
#include <GL/glew.h>

const bool GRenderer::init() {
	GGeneral::Logger::init();
	if (!GWindow::init())
		return false;
	if (!GWindow::Monitor::init())
		return false;
	//if (!GGraphics::init())
	//	return false;
	return true;
}

GGeneral::String GRenderer::getCurentOpenGLVersion() {
	GGeneral::String r(glGetString(GL_VERSION));
	return r;
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

void GRenderer::clear(GGeneral::Color color) {
	glClearColor(((float)color[0]) / 255, ((float)color[1]) / 255, ((float)color[2]) / 255, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}

void GRenderer::draw(Mesh& m) {
	if (m.tex != nullptr)
		m.tex->bind();
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
}