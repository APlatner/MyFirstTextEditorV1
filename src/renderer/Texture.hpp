#pragma once

#include "Defines.hpp"

class Texture {
	public:
	Texture();
	~Texture();

	bool LoadFont(const char *filepath, uint32_t fontSize);
	void Bind();
	void UnBind();

	private:
	uint32_t textureID;
};