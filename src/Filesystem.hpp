#pragma once

#include "Defines.hpp"
#include "input/InputManager.hpp"
#include "container/TextBuffer.hpp"
#include "renderer/Shader.hpp"
#include "renderer/VertexBuffer.hpp"
#include "renderer/VertexArray.hpp"
#include "renderer/IndexBuffer.hpp"
#include "renderer/Renderer.hpp"

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

class Filesystem {
    public:
    Filesystem(InputManager &im);
    ~Filesystem();

    bool InitRenderer();
    bool PrepBuffers();

    void Open();
    void Close();
    void SaveFile();

    InputManager &inputManager;
    TextBuffer textBuffer;
    // std::string currentWorkingDirectory;
    std::string activeFileName;
    FILE *activeFile;
    EventContext context;


    Shader s;
    // buffers
    VertexBuffer vbo;
    VertexArray vao;
    IndexBuffer ibo;

    VertexBuffer cursorVBO;
    VertexArray cursorVAO;
    
    // textarea info
    glm::vec3 color;
    glm::uvec2 position;
    glm::uvec2 size;
    float fontScale = 1;
    float fontMargin = 1.618;
    int deltaX = 0;
    int deltaY = 0;

    // texture IDs
    uint32_t fontID;
    uint32_t cursorID;

    private:
    static bool ControlEvent(u16 code, void *sender, void *listener, EventData data);
    void FileContext(u16 code, EventData data);
    void TextContext(u16 code, EventData data);

    Character characters[256];
};