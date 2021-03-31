#include "GRenderer.h"
#include <GL/glew.h>

GRenderer::Primitives::VertexBuffer::VertexBuffer(float data[], uint32_t amount, uint32_t count) {
	glGenBuffers(1, &ID);
	bind();

	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(float), data, GL_STATIC_DRAW);

	this->amount = count;
}

GRenderer::Primitives::VertexBuffer::VertexBuffer(char data[], uint32_t amount, uint32_t count) {
	glCreateBuffers(1, &ID);
	bind();
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(float), data, GL_STATIC_DRAW);

	this->amount = count;
}

GRenderer::Primitives::VertexBuffer::VertexBuffer(short data[], uint32_t amount, uint32_t count) {
	glCreateBuffers(1, &ID);
	bind();
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(float), data, GL_STATIC_DRAW);

	this->amount = count;
}

GRenderer::Primitives::VertexBuffer::VertexBuffer(int data[], uint32_t amount, uint32_t count) {
	glGenBuffers(1, &ID);
	bind();
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(float), data, GL_STATIC_DRAW);

	this->amount = count;
}

GRenderer::Primitives::VertexBuffer::VertexBuffer(double data[], uint32_t amount, uint32_t count) {
	glCreateBuffers(1, &ID);
	bind();
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(float), data, GL_STATIC_DRAW);

	this->amount = count;
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