#include "Font.hpp"

#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H

Font::Font() { glGenTextures(1, &fontID); }

Font::~Font() { glDeleteTextures(1, &fontID); }

bool Font::LoadFont(const char *filepath, uint32_t fontSize) {
  Bind();
  FT_Library library;
  if (FT_Init_FreeType(&library)) {
    printf("Failed to init freetype!\n");
    return false;
  }

  FT_Face face;
  if (FT_New_Face(library, filepath, 0, &face)) {
    printf("Failed to load font!\n");
    return false;
  }

  FT_Set_Pixel_Sizes(face, 0, fontSize);

  uint32_t width = 0;
  uint32_t height = 0;
  for (char c = ' '; c < 127; c++) {
    if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
      printf("ERROR::FREETYPE:Failed to load glyph for %c\n", c);
      continue;
    }
    if (face->glyph->bitmap.rows > height) {
      height = face->glyph->bitmap.rows;
    }
    if (face->glyph->bitmap.width > width) {
      width = face->glyph->bitmap.width;
    }
  }
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  uint8_t *font = (uint8_t *)malloc(sizeof(char) * width * height * 100);
  memset(font, 0x00, width * height * 100);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width * 10, height * 10, 0, GL_RED,
               GL_UNSIGNED_BYTE, font);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  u8 col = 0;
  u8 row = 0;
  glm::vec2 offset = glm::vec2(0.0f, 0.0f);
  for (char c = ' '; c < 127; c++) {
    if (FT_Load_Char(face, c, FT_LOAD_RENDER) != FT_Err_Ok) {
      printf("ERROR::FREETYPE:Failed to load glyph for %c\n", c);
      continue;
    }
    if (col == 9) {
      col = 0;
      row++;
    } else {
      col++;
    }
    offset.x = width * col;
    offset.y = height * row;
    glTexSubImage2D(GL_TEXTURE_2D, 0, (int)offset.x, (int)offset.y,
                    face->glyph->bitmap.width, face->glyph->bitmap.rows, GL_RED,
                    GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

    Character character = {
        glm::vec2(offset.x / (width * 10), offset.y / (height * 10)),
        glm::vec2((offset.x + face->glyph->bitmap.width) / (width * 10),
                  (offset.y + face->glyph->bitmap.rows) / (height * 10)),
        glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
        glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        face->glyph->advance.x};

    characters[(int)c] = character;
  }

  FT_Done_Face(face);
  FT_Done_FreeType(library);

  return true;
}

void Font::Bind() { glBindTexture(GL_TEXTURE_2D, fontID); }

void Font::UnBind() { glBindTexture(GL_TEXTURE_2D, 0); }