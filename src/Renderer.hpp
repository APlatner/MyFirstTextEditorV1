#pragma once

#include "Defines.hpp"
#include "Shader.hpp"

#include <GL/glew.h>
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
    Renderer();
    ~Renderer();

    void render(Shader &s, glm::uvec2 pos, glm::uvec2 size, glm::vec3 color);
    void renderChar(Shader &s, const char *text, glm::uvec2 pos, glm::uvec2 size, float scale, glm::vec3 color, bool showCursor, float margin);
    void initFreetype(const char *fontPath);
    
    private:
    u32 vbo, vao;
    u8 *font;
    u32 fontID;
    unsigned char *cursor;
    u32 cursorID;
    unsigned char *button;
    u32 buttonID;
    std::map<char, Character> characters;
};