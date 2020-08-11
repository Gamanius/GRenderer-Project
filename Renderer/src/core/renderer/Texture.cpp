#include "../GRenderer.h"
#include <GL/glew.h>

GRenderer::Texture::Texture(const Texture& t) {
	ID = t.ID;
	textureSlot = t.textureSlot;
}

GRenderer::Texture::Texture(Texture&& t) noexcept {
	ID = t.ID;
	textureSlot = t.textureSlot;

	t.ID = 0;
	t.textureSlot = 0;
}

GRenderer::Texture::Texture(GFile::Graphics::Image& i) {
	createTexture(i);
}

GRenderer::Texture& GRenderer::Texture::operator=(const Texture& other) {
	textureSlot = other.textureSlot;
	ID = other.ID;
	return *this;
}

GRenderer::Texture& GRenderer::Texture::operator=(Texture&& t) noexcept {
	if (t.ID == ID)
		return *this;

	ID = t.ID;
	textureSlot = t.textureSlot;

	t.ID = 0;
	t.textureSlot = 0;
	return *this;
}

const bool GRenderer::Texture::createTexture(GFile::Graphics::Image& i) {
	glGenTextures(1, &ID);
	bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	if (!i.hasAlpha) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, i.dim.width, i.dim.height, 0, GL_BGR, GL_UNSIGNED_BYTE, i.data);
	}
	else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, i.dim.width, i.dim.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, i.data);
	}
	glGenerateMipmap(GL_IMAGE_2D);
	return true;
}

void GRenderer::Texture::createTexture(GGeneral::Dimension<int> size, bool alpha) {
	glGenTextures(1, &ID);
	bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	//GL_RGB = 0x1907 GL_RGBA = 0x1908 -> GL_RGB + 1 = GL_RGBA
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB + alpha, size.width, size.height, 0, GL_BGR, GL_UNSIGNED_BYTE, nullptr);
}

void GRenderer::Texture::bind(unsigned int slot) {
	textureSlot = GL_TEXTURE0 + slot;
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void GRenderer::Texture::bind() {
	glActiveTexture(textureSlot);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void GRenderer::Texture::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void GRenderer::Texture::setTextureSlot(unsigned int slot) {
	textureSlot = GL_TEXTURE0 + slot;
}

GRenderer::Texture::~Texture() {
	glDeleteTextures(1, &ID);
}