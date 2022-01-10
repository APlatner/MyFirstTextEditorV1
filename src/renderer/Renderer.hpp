#pragma once

#include "../Defines.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "Font.hpp"
#include "input/InputManager.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <map>

class Renderer {
    public:
    Renderer(InputManager &im);
    ~Renderer();

    void DrawFrame();

    static void render(Shader &shader, VertexArray &vertexArray, VertexBuffer &vertexBuffer, IndexBuffer &indexBuffer, uint32_t count, uint32_t &textureID);
    static void WindowResizeCallback(GLFWwindow *window, int width, int height);

    private:
    void BeginFrame();
    static bool RendererCallback(u16 code, void *sender, void *listener, EventData data);
    static void GLDebugMessageCallback(uint32_t source, uint32_t type, uint32_t id, uint32_t severity, int32_t length, const char *message, const void *userParam);
    InputManager &inputManager;
    u32 vbo, vao;
    u8 *font;
    u32 fontID;
    unsigned char *cursor;
    u32 cursorID;
    unsigned char *button;
    u32 buttonID;
    std::map<char, Character> characters;
    Shader s;
};