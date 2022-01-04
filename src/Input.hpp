#pragma once

#include "Shader.hpp"
#include "Renderer.hpp"

#include <glm/glm.hpp>
#include <functional>
#include <vector>
#include <string>


enum InputType {
    INPUT_TITLE = 0,
    INPUT_BUTTON,
    INPUT_TEXTAREA,
    INPUT_CHECKBOX,
    INPUT_RADIO
};

enum EventType {
    EVENT_ON_CLICK = 0,
    EVENT_ON_RELEASE
};

typedef std::function<void()> Action;

class Button {
    public:
    Button(glm::uvec2 s, glm::uvec2 pos, glm::uvec2 mar, glm::uvec2 pad, glm::vec3 bg, glm::vec3 fg, Action a);
    ~Button();

    void render(Shader &s, Renderer &r);

    glm::uvec2 size;
    glm::uvec2 position;
    glm::uvec2 margin;
    glm::uvec2 padding;
    glm::vec3 background;
    glm::vec3 foreground;
    Action action;
    std::string text;
};

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

    void render(Shader &s, Renderer &r, bool cursor);

    glm::uvec2 size;
    glm::uvec2 position;
    glm::uvec2 margin;
    glm::uvec2 padding;
    glm::vec3 background;
    glm::vec3 foreground;
    Action action;
    u64 textCursorColumn;
    u64 textCursorRow;
    std::string text;
};