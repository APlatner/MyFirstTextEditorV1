#pragma once

#include "Defines.hpp"
#include "VertexBuffer.hpp"
#include "BufferLayout.hpp"

class VertexArray {
	public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void UnBind() const;
	void AddBuffer(const VertexBuffer &vertexBuffer, const BufferLayout &bufferLayout);
	private:
	uint32_t vertexArrayID;
};
