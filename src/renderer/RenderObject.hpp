#pragma once

#include "BufferLayout.hpp"

#include <cstdint>
#include <vector>

struct Character {
  glm::vec2 Start;
  glm::vec2 End;
  glm::ivec2 Size;
  glm::ivec2 Bearing;
  long Advance;
};

class RenderObject {
public:
  RenderObject();
  ~RenderObject();

  void CreateBuffers(BufferLayout bufferLayout);
  void Render();

protected:
  void CreateVertexArray(BufferLayout bufferLayout);
  void CreateVertexBuffer();

  uint32_t m_VertexArrayObject;
  uint32_t m_VertexBufferObject;
  uint32_t m_ElementBufferObject;
  uint32_t m_ShaderObject;
  std::vector<uint32_t> m_Textures;
  uint32_t m_NumPoints;
};
