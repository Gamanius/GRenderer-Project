#include "GRenderer.h"
#include <GL/glew.h>

byte getSize(GRenderer::Primitives::IndexTypes t) {
	switch (t) {
	case GRenderer::Primitives::IndexTypes::UNSIGNED_BYTE:  return sizeof(byte);
	case GRenderer::Primitives::IndexTypes::UNSIGNED_SHORT: return sizeof(uint16_t);
	case GRenderer::Primitives::IndexTypes::UNSIGNED_INT:   return sizeof(uint32_t);
	}
	return 0;
}

GRenderer::Primitives::VertexArray::VertexArrayLayout::VertexArrayLayout(std::initializer_list<byte> data, GRenderer::Primitives::VertexTypes type) {
	for (auto l : data) {
		this->layout.push_back(l);
	}

	switch (type) {
	case GRenderer::Primitives::VertexTypes::BYTE:	 size = sizeof(byte);   break;
	case GRenderer::Primitives::VertexTypes::SHORT:	 size = sizeof(short);  break;
	case GRenderer::Primitives::VertexTypes::INT:	 size = sizeof(int);    break;
	case GRenderer::Primitives::VertexTypes::FLOAT:	 size = sizeof(float);  break;
	case GRenderer::Primitives::VertexTypes::DOUBLE: size = sizeof(double); break;
	default:                                         size = 0;
	}
}

const uint32_t GRenderer::Primitives::VertexArray::VertexArrayLayout::getStride() const {
	int stride = 0;
	for (uint32_t i = 0; i < layout.size(); i++) {
		stride += layout[i];
	}
	return stride * size;
}

const uint32_t GRenderer::Primitives::VertexArray::VertexArrayLayout::getOffset(const uint32_t index) const {
	if (index == 0)
		return 0;
	int offset = 0;
	for (uint32_t i = 0; i < index; i++) {
		offset += layout[i] * size;
	}
	return offset;
}

GRenderer::Primitives::VertexArray::VertexArray() {
	amount = 0;
	ID = 0;
}

GRenderer::Primitives::VertexArray::VertexArray(VertexBuffer vertex, IndexBuffer index, VertexArrayLayout layout) {
	glGenVertexArrays(1, &ID);
	bind();
	index.bind();
	vertex.bind();
	amount = index.amount;
	isOnlyVertexBuffer = false;

	for (uint32_t i = 0; i < layout.layout.size(); i++) {
		glVertexAttribPointer(i, layout.layout[i], GL_FLOAT, GL_FALSE, layout.getStride(), (void*)layout.getOffset(i));
		glEnableVertexAttribArray(i);
	}

	type = index.element;

	unbind();
	index.unbind();
	vertex.unbind();
}

GRenderer::Primitives::VertexArray::VertexArray(VertexBuffer vertex, VertexArrayLayout layout) {
	glGenVertexArrays(1, &ID);
	bind();
	vertex.bind();
	amount = vertex.amount;
	isOnlyVertexBuffer = true;

	for (uint32_t i = 0; i < layout.layout.size(); i++) {
		glVertexAttribPointer(i, layout.layout[i], GL_FLOAT, GL_FALSE, layout.getStride(), (void*)layout.getOffset(i));
		glEnableVertexAttribArray(i);
	}

	unbind();
	vertex.unbind();
}

GRenderer::Primitives::VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &ID);
}

void GRenderer::Primitives::VertexArray::bind() {
	glBindVertexArray(ID);
}

void GRenderer::Primitives::VertexArray::unbind() {
	glBindVertexArray(0);
}