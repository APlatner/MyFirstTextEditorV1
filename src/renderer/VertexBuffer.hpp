#pragma once

#include "Defines.hpp"

class VertexBuffer {
	public:
	VertexBuffer();
	~VertexBuffer();

	void StoreData(const void *data, uint64_t size);
	void Bind() const;
	void UnBind() const;

	private:
	uint32_t vertexBufferID;
};
