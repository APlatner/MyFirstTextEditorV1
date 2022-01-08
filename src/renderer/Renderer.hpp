#pragma once

#include "../Defines.hpp"
#include "Shader.hpp"
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

    void render(Shader &s, glm::uvec2 pos, glm::uvec2 size, glm::vec3 color);
    void renderChar(Shader &s, const char *text, glm::uvec2 pos, glm::uvec2 size, float scale, glm::vec3 color, bool showCursor, u32 cursorLoc, float margin);
    void initFreetype(const char *fontPath);
    
    static void WindowResizeCallback(GLFWwindow *window, int width, int height);

    int deltaX = 0;
    int deltaY = 0;

    private:
    void BeginFrame();
    static bool RendererCallback(u16 code, void *sender, void *listener, EventData data);

    InputManager &inputManager;
    EventContext context = NULL_CONTEXT;
    u32 vbo, vao;
    u8 *font;
    u32 fontID;
    unsigned char *cursor;
    u32 cursorID;
    unsigned char *button;
    u32 buttonID;
    std::map<char, Character> characters;
};