#include "../../GRenderer.h"
#include <GL/glew.h>

byte getSize(GRenderer::Primitives::IndexTypes t) {
	switch (t) {
	case GRenderer::Primitives::IndexTypes::UNSIGNED_BYTE:  return sizeof(byte);
	case GRenderer::Primitives::IndexTypes::UNSIGNED_SHORT: return sizeof(unsigned short);
	case GRenderer::Primitives::IndexTypes::UNSIGNED_INT:   return sizeof(unsigned int);
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

const unsigned int GRenderer::Primitives::VertexArray::VertexArrayLayout::getStride() const {
	int stride = 0;
	for (unsigned int i = 0; i < layout.size(); i++) {
		stride += layout[i];
	}
	return stride * size;
}

const unsigned int GRenderer::Primitives::VertexArray::VertexArrayLayout::getOffset(const unsigned int index) const {
	if (index == 0)
		return 0;
	int offset = 0;
	for (unsigned int i = 0; i < index; i++) {
		offset += layout[i] * size;
	}
	return offset;
}

GRenderer::Primitives::VertexArray::VertexArray(VertexBuffer vertex, IndexBuffer index, VertexArrayLayout layout) {
	glGenVertexArrays(1, &ID);
	bind();
	index.bind();
	vertex.bind();
	amount = index.amount;
	isOnlyVertexBuffer = false;

	for (unsigned int i = 0; i < layout.layout.size(); i++) {
		glVertexAttribPointer(i, layout.layout[i], GL_FLOAT, GL_FALSE, layout.getStride(), (void*)layout.getOffset(i));
		glEnableVertexAttribArray(i);
	}

	type = index.element;

	unbind();
	index.unbind();
	vertex.unbind();
}

void GRenderer::Primitives::VertexArray::bind() {
	glBindVertexArray(ID);
}

void GRenderer::Primitives::VertexArray::unbind() {
	glBindVertexArray(0);
}