#include "GRenderer.h"
#include <GL/glew.h>

GRenderer::Primitives::VertexBuffer::VertexBuffer(float data[], unsigned int amount, unsigned int count) {
	glGenBuffers(1, &ID);
	bind();

	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(float), data, GL_STATIC_DRAW);

	this->amount = count;
}

GRenderer::Primitives::VertexBuffer::VertexBuffer(char data[], unsigned int amount, unsigned int count) {
	glCreateBuffers(1, &ID);
	bind();
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(float), data, GL_STATIC_DRAW);

	this->amount = count;
}

GRenderer::Primitives::VertexBuffer::VertexBuffer(short data[], unsigned int amount, unsigned int count) {
	glCreateBuffers(1, &ID);
	bind();
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(float), data, GL_STATIC_DRAW);

	this->amount = count;
}

GRenderer::Primitives::VertexBuffer::VertexBuffer(int data[], unsigned int amount, unsigned int count) {
	glGenBuffers(1, &ID);
	bind();
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(float), data, GL_STATIC_DRAW);

	this->amount = count;
}

GRenderer::Primitives::VertexBuffer::VertexBuffer(double data[], unsigned int amount, unsigned int count) {
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