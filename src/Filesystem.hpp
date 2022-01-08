#pragma once

#include "Defines.hpp"
#include "input/InputManager.hpp"
#include "container/TextBuffer.hpp"
#include "renderer/Shader.hpp"
#include "renderer/VertexBuffer.hpp"
#include "renderer/IndexBuffer.hpp"

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
    VertexBuffer vbo;
    IndexBuffer ibo;

    private:
    static bool ControlEvent(u16 code, void *sender, void *listener, EventData data);
    void FileContext(u16 code, EventData data);
    void TextContext(u16 code, EventData data);
};