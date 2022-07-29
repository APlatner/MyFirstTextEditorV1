#include "RenderObject.hpp"

RenderObject::RenderObject() {}

RenderObject::~RenderObject() {
  glBindVertexArray(0);
  glDeleteVertexArrays(1, &m_VertexArrayObject);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &m_VertexBufferObject);
}

void RenderObject::CreateBuffers(BufferLayout bufferLayout) {
  CreateVertexBuffer();
  CreateVertexArray(bufferLayout);
}

void RenderObject::Render() {
  glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject);
  glBindVertexArray(m_VertexArrayObject);

  glDrawArrays(GL_TRIANGLES, 0, m_NumPoints);
}

void RenderObject::CreateVertexArray(BufferLayout bufferLayout) {
  glGenVertexArrays(1, &m_VertexArrayObject);
  glBindVertexArray(m_VertexArrayObject);
  intptr_t offset = 0;
  for (int i = 0; i < bufferLayout.GetElements().size(); ++i) {
    glVertexAttribPointer(i, bufferLayout.GetElements()[i].count,
                          bufferLayout.GetElements()[i].type,
                          bufferLayout.GetElements()[i].normalized,
                          bufferLayout.GetStride(), (void *)offset);
    glEnableVertexAttribArray(i);
    offset += bufferLayout.GetElements()[i].count *
              BufferElement::GetTypeSize(bufferLayout.GetElements()[i].type);
  }
}

void RenderObject::CreateVertexBuffer() {
  glGenBuffers(1, &m_VertexBufferObject);
  glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject);
}
