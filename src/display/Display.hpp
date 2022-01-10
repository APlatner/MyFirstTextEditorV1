#pragma once

#include "Defines.hpp"
#include "renderer/Renderer.hpp"

class Display {
	public:
	Display();
	~Display();

	virtual void Init();
	virtual void Render();

	private:
	Shader s;
	VertexBuffer vbo;
	VertexArray vao;
	IndexBuffer ibo;

	glm::vec2 position;
	glm::vec2 size;
	glm::vec3 background = glm::vec3{0.3f};
	glm::vec3 foreground = glm::vec3{0.7f};
	float fontScale = 1;
    float fontMargin = 1.618;
};
