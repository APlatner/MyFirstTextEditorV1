#include "VertexArray.hpp"

#include <GL/glew.h>

VertexArray::VertexArray() {
	glGenVertexArrays(1, &vertexArrayID);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &vertexArrayID);
}

void VertexArray::Bind() const {
	glBindVertexArray(vertexArrayID);
}

void VertexArray::UnBind() const {
	glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer &vertexBuffer, const BufferLayout &bufferLayout) {
	Bind();
	vertexBuffer.Bind();
	// const auto &elements = bufferLayout.GetElements();
	// intptr_t offset = 0;
	// for (uint32_t i = 0; i < elements.size(); i++) {
	// 	const auto &element = elements[i];
	// 	glEnableVertexAttribArray(i);
	// 	glVertexAttribPointer(i, element.count, element.type, element.normalized, bufferLayout.GetStride(), (const void*)offset);
	// 	offset += element.count * BufferElement::GetTypeSize(element.type);
	// }
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
}