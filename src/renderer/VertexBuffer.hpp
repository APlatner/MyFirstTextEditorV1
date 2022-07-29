#pragma once

#include "Defines.hpp"

class VertexBuffer {
public:
  VertexBuffer();
  ~VertexBuffer();

  void StoreData(const void *data, uint64_t size);
  void Bind() const;
  void UnBind() const;
  inline uint64_t const GetCount() { return count; }

private:
  uint32_t vertexBufferID;
  uint64_t count;
};
