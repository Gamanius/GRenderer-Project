#include "../../GRenderer.h"
#include <GL/glew.h>

GRenderer::Primitives::IndexBuffer::IndexBuffer(unsigned int data[], unsigned int amount) : amount(amount) {
	glCreateBuffers(1, &ID);
	bind();

	element = IndexTypes::UNSIGNED_INT;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, amount * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

GRenderer::Primitives::IndexBuffer::IndexBuffer(byte data[], unsigned int amount) : amount(amount) {
	glCreateBuffers(1, &ID);
	bind();

	element = IndexTypes::UNSIGNED_BYTE;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, amount * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

GRenderer::Primitives::IndexBuffer::IndexBuffer(unsigned short data[], unsigned int amount) : amount(amount) {
	glGenBuffers(1, &ID);
	bind();

	element = IndexTypes::UNSIGNED_SHORT;
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, amount * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

GRenderer::Primitives::IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &ID);
}

void GRenderer::Primitives::IndexBuffer::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void GRenderer::Primitives::IndexBuffer::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}