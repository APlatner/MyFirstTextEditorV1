#pragma once

#include "Defines.hpp"

class IndexBuffer {
	public:
	IndexBuffer();
	~IndexBuffer();

	void StoreData(const uint32_t *data, uint32_t count);
	void Bind() const;
	void UnBind() const;
	inline uint32_t GetCount() const { return count; }

	private:
	uint32_t indexBufferID;
	uint32_t count;
};