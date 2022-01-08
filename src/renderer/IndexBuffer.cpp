#include "IndexBuffer.hpp"

#include <GL/glew.h>

IndexBuffer::IndexBuffer() {
	glGenBuffers(1, &indexBufferID);
}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &indexBufferID);
}

void IndexBuffer::StoreData(const uint32_t *data, uint32_t count) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_DYNAMIC_DRAW);
}

void IndexBuffer::Bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
}

void IndexBuffer::UnBind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
