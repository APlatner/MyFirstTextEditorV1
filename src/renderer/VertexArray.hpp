#pragma once

#include "Defines.hpp"

class VertexArray {
	public:
	VertexArray();
	~VertexArray();

	void Bind();
	void UnBind();
	private:
	uint32_t vertexArrayID;
};
