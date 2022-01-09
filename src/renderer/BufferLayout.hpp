#pragma once

#include "Defines.hpp"

#include <vector>
#include <GL/glew.h>

struct BufferElement {
	uint32_t type;
	uint32_t count;
	uint8_t normalized;

	static uint32_t GetTypeSize(uint32_t type) {
		switch (type) {
			case GL_FLOAT:
				return 4;
			case GL_UNSIGNED_INT:
				return 4;
			case GL_UNSIGNED_BYTE:
				return 1;
		}
		return 0;
	}
};

class BufferLayout {
	public:
	BufferLayout() : stride(0) {}

	inline void Push(uint32_t count) {
		elements.push_back({GL_FLOAT, count, GL_FALSE});
		stride += BufferElement::GetTypeSize(GL_FLOAT) * count;
	}

	inline const std::vector<BufferElement>& GetElements() const { return elements; }
	inline uint32_t GetStride() const { return stride; }

	private:
	std::vector<BufferElement> elements;
	uint32_t stride;
};
