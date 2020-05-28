#include "../GRenderer.h"
#include <GL/glew.h>

GRenderer::Primitives::VertexBuffer::VertexBuffer(float data[], unsigned int size) {
	glCreateBuffers(1, &ID);
	bind();

	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW);
}

GRenderer::Primitives::VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &ID);
}

void GRenderer::Primitives::VertexBuffer::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void GRenderer::Primitives::VertexBuffer::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}