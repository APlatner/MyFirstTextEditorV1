#pragma once

#include "Defines.hpp"
#include "TextBuffer.hpp"

class TextArea {
	public:

	private:
	TextBuffer textBuffer;
	
	Shader s;
    VertexBuffer vbo;
    IndexBuffer ibo;
};
