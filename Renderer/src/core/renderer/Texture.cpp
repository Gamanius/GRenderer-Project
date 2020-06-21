#include "../GRenderer.h"
#include <GL/glew.h>

GRenderer::Texture::Texture(GIO::Graphics::Image& i) {
	createShader(i);
}

const bool GRenderer::Texture::createShader(GIO::Graphics::Image& i) {
	glGenTextures(1, &ID);
	bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	if (!i.hasAlpha) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, i.dim.width, i.dim.height, 0, GL_RGB, GL_UNSIGNED_BYTE, i.data);
	}
	else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, i.dim.width, i.dim.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, i.data);
	}
	glGenerateMipmap(GL_IMAGE_2D);
	return true;
}

void GRenderer::Texture::bind(unsigned int slot) {
	textureSlot = GL_TEXTURE0 + slot;
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void GRenderer::Texture::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

GRenderer::Texture::~Texture() {
	glDeleteTextures(1, &ID);
}