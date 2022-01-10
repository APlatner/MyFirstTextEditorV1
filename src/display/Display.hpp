#pragma once

#include "Defines.hpp"
#include "renderer/Renderer.hpp"

class Display {
	public:
	Display();
	~Display();

	virtual void Init();
	virtual void Update();
	virtual void Render();

	protected:
	Shader shader;
	VertexBuffer vbo;
	VertexArray vao;
	IndexBuffer ibo;

	glm::vec2 position;
	glm::vec2 size;
	glm::vec3 background = glm::vec3{0.3f};
	glm::vec3 foreground = glm::vec3{1.0f};
};
