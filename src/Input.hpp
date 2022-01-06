#pragma once

#include "renderer/Shader.hpp"
#include "renderer/Renderer.hpp"
#include "TextBuffer.hpp"

#include <glm/glm.hpp>
#include <functional>
#include <vector>
#include <string>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

enum EventType {
    EVENT_ON_CLICK = 0,
    EVENT_ON_RELEASE
};

typedef std::function<void()> Action;

class FileDisplay {
    public:
    FileDisplay(glm::uvec2 s, glm::uvec2 pos, glm::uvec2 mar, glm::uvec2 pad, glm::vec3 bg, glm::vec3 fg);
    ~FileDisplay();

    void render(Shader &s, Renderer &r);

    glm::uvec2 position;
    glm::uvec2 size;
    glm::uvec2 margin;
    glm::uvec2 padding;
    glm::vec3 background;
    glm::vec3 foreground;
    std::string text;
};

class TextArea {
    public:
    TextArea();

    void render(Shader &s, Renderer &r, bool cursor);

    glm::uvec2 size;
    glm::uvec2 position;
    glm::uvec2 margin;
    glm::uvec2 padding;
    glm::vec3 background;
    glm::vec3 foreground;
    Action action;
    std::string text;
    TextBuffer *textBuffer;
};

class Input {
    public:
    Input();

    void ParseText(int key, int action, int mods);

    static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

    TextArea textArea;
};