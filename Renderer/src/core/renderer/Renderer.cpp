#include "../GRenderer.h"
#include <GL/glew.h>

const bool GRenderer::init() {
	GGeneral::Logger::init();
	GWindow::Monitor::init();
	return true;
}

GGeneral::String GRenderer::getCurentOpenGLVersion() {
	GGeneral::String r(glGetString(GL_VERSION));
	return r;
}

void GRenderer::clear(GGeneral::Color& color) {
	glClearColor(((float)color[0]) / 255, ((float)color[1]) / 255, ((float)color[2]) / 255, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}

void GRenderer::draw(Mesh& m) {
	m.tex.bind();
	m.vertex.bind();
	if (m.vertex.isOnlyVertex()) {
		glDrawArrays(GL_TRIANGLES, 0, m.vertex.getAmount());
	}
	else {
		GLenum type;
		switch (m.vertex.getIndexType()) {
		case GRenderer::Primitives::IndexTypes::UNSIGNED_BYTE:	 type = GL_UNSIGNED_BYTE;  break;
		case GRenderer::Primitives::IndexTypes::UNSIGNED_SHORT:	 type = GL_UNSIGNED_SHORT; break;
		case GRenderer::Primitives::IndexTypes::UNSIGNED_INT:	 type = GL_UNSIGNED_INT;   break;
		}
		glDrawElements(GL_TRIANGLES, m.vertex.getAmount(), type, nullptr);
	}
}