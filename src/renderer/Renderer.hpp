#pragma once

#include "../Defines.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "input/InputManager.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <map>

struct Character {
    glm::vec2 Start;
    glm::vec2 End;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    long Advance;
};

class Renderer {
    public:
    Renderer(InputManager &im);
    ~Renderer();

    void DrawFrame();

    void render(Shader &shader, VertexArray &vertexArray, VertexBuffer &vertexBuffer, IndexBuffer &indexBuffer, uint32_t count, uint32_t &textureID);
    void renderChar(const char *text, glm::uvec2 pos, glm::uvec2 size, float scale, glm::vec3 color, bool showCursor, u32 cursorLoc, float margin);
    void initFreetype(const char *fontPath);
    
    static void WindowResizeCallback(GLFWwindow *window, int width, int height);

    int deltaX = 0;
    int deltaY = 0;

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