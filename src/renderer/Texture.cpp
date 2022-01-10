#include "Texture.hpp"

#include <GL/glew.h>

Texture::Texture() {
	glGenTextures(1, &textureID);
}

Texture::~Texture() {
	glDeleteTextures(1, &textureID);
}

bool Texture::LoadFont(const char *filepath, uint32_t fontSize) {
	return true;	
}

void Texture::Bind() {
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::UnBind() {
	glBindTexture(GL_TEXTURE_2D, textureID);
}
