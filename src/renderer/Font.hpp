#pragma once

#include "Defines.hpp"

struct Character {
  glm::vec2 Start;
  glm::vec2 End;
  glm::ivec2 Size;
  glm::ivec2 Bearing;
  long Advance;
};

class Font {
public:
  Font();
  ~Font();

  bool LoadFont(const char *filepath, uint32_t fontSize);
  void Bind();
  void UnBind();

  inline Character &GetChar(char c) { return characters[(int)c]; }

  uint32_t fontID;

private:
  Character characters[128];
};