#include "../GRenderer.h"
#include <gl/glew.h>

GRenderer::FrameBuffer::FrameBuffer() {
	glGenFramebuffers(1, &ID);
}

GRenderer::FrameBuffer::~FrameBuffer() {
	glDeleteFramebuffers(1, &ID);
	delete boundTexture;
}

void GRenderer::FrameBuffer::attach(Texture& t) {
	t.bind();
	bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, t.getID(), 0);
}

void GRenderer::FrameBuffer::attachTex(GGeneral::Dimension<int> size) {
	bind();
	boundTexture = new Texture();
	boundTexture->createTexture(size);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, boundTexture->getID(), 0);
}

void GRenderer::FrameBuffer::bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, ID);
}

void GRenderer::FrameBuffer::unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}