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