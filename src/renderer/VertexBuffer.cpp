#include "VertexBuffer.hpp"

#include <GL/glew.h>

VertexBuffer::VertexBuffer() {
	glGenBuffers(1, &vertexBufferID);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &vertexBufferID);
}

void VertexBuffer::StoreData(const void *data, uint64_t size) {
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
	count = size;
}

void VertexBuffer::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
}

void VertexBuffer::UnBind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}