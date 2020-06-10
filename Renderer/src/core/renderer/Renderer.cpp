#include "../GRenderer.h"
#include <GL/glew.h>

std::string GRenderer::getCurentOpenGLVersion() {
	auto c = glGetString(GL_VERSION);
	std::string r;
	for (unsigned int i = 0; c[i] != '\0'; i++) {
		r += c[i];
	}
	return r;
}

void GRenderer::clear(GGeneral::Color& color) {
	glClearColor(((float)color[0]) / 255, ((float)color[1]) / 255, ((float)color[2]) / 255, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}