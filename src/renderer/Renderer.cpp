
#include "Renderer.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>


const int fontsize = 16;

Renderer::Renderer() {
    
}

Renderer::~Renderer() {

}

void Renderer::initFreetype(const char *fontPath) {
    FT_Library library;
    if (FT_Init_FreeType(&library)) {
        printf("Failed to init freetype!\n");
        return;
    }

    FT_Face face;
    if (FT_New_Face(library, fontPath, 0, &face)) {
        printf("Failed to load font!\n");
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, fontsize);
    cursor = (unsigned char*)malloc(sizeof(char) * fontsize * 4);
    memset(cursor, 0xff, fontsize * 4);
    button = (unsigned char*)malloc(sizeof(char) * 4);
    memset(button, 0xff, 4);
    u32 width = 0;
    u32 height = 0;
    for (char c = ' '; c < 127; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            printf("ERROR::FREETYPE:Failed to load glyph for %c\n", c);
            continue;
        }
        if (face->glyph->bitmap.rows > height) {
            height = face->glyph->bitmap.rows;
        }
        if (face->glyph->bitmap.width > width) {
            width = face->glyph->bitmap.width;
        }
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    font = (unsigned char*)malloc(sizeof(char) * width * height * 100);
    memset(font, 0x00, width * height * 100);
    glm::vec2 offset = glm::vec2(0.0f, 0.0f);
    glGenTextures(1, &fontID);
    glBindTexture(GL_TEXTURE_2D, fontID);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RED,
        width * 10,
        height * 10,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        font);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    u8 col = 0;
    u8 row = 0;
    for (char c = ' '; c < 127; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER) != FT_Err_Ok) {
            printf("ERROR::FREETYPE:Failed to load glyph for %c\n", c);
            continue;
        }
        if (col == 9) {
            col = 0;
            row++;
        } else {
            col++;
        }
        offset.x = width * col;
        offset.y = height * row;
        glTexSubImage2D(
            GL_TEXTURE_2D,
            0,
            (int)offset.x,
            (int)offset.y,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer);

        Character character = {
            glm::vec2(offset.x / (width * 10), offset.y / (height * 10)),
            glm::vec2((offset.x + face->glyph->bitmap.width) / (width * 10), (offset.y + face->glyph->bitmap.rows) / (height * 10)),
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        // printf("Character: %c, Start: (%f, %f), End: (%f, %f)\n", c, character.Start.x, character.Start.y, character.End.x, character.End.y);
        characters.insert(std::pair<char, Character>(c, character));
    }

    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(1, &cursorID);
    glBindTexture(GL_TEXTURE_2D, cursorID);
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RED, fontsize / 12,
        fontsize, 0, GL_RED, GL_UNSIGNED_BYTE,
        cursor
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(1, &buttonID);
    glBindTexture(GL_TEXTURE_2D, buttonID);
    glTexImage2D(
        GL_TEXTURE_2D, 0, GL_RED, 2,
        2, 0, GL_RED, GL_UNSIGNED_BYTE,
        button
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    FT_Done_Face(face);
    FT_Done_FreeType(library);

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::render(Shader &s, glm::uvec2 pos, glm::uvec2 size, glm::vec3 color) {
    glUniform3f(glGetUniformLocation(s.ID, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vao);

    float vertices[6][4] = {
        {(float)pos.x, (float)(pos.y + size.y), 0.0f, 1.0f},
        {(float)(pos.x + size.x), (float)pos.y, 1.0f, 0.0f},
        {(float)pos.x, (float)pos.y,            0.0f, 0.0f},

        {(float)pos.x, (float)(pos.y + size.y), 0.0f, 1.0f},
        {(float)(pos.x + size.x), (float)(pos.y + size.y), 1.0f, 1.0f},
        {(float)(pos.x + size.x), (float)pos.y, 1.0f, 0.0f}
    };

    glBindTexture(GL_TEXTURE_2D, buttonID);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::renderChar(Shader &s, const char *text, glm::uvec2 pos, glm::uvec2 size, float scale, glm::vec3 color, bool showCursor, u32 cursorLoc, float margin) {
    if (text == NULL) {
        return;
    }
    glUniform3f(glGetUniformLocation(s.ID, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vao);
    bool full = false;
    float x = (float)pos.x;
    float y = (float)pos.y;
    for (u32 i = 0; text[i] != '\0'; i++) {
        Character c = characters[text[i]];
        if (text[i] == '\n') {
            x = pos.x;
            if (y + characters['I'].Size.y * scale * margin < 0) {
                printf("Out of space\n");
                return;
            } else {
                y += characters['I'].Size.y * scale * margin;
            }
        } else if (text[i] == '\t') {
            x += (characters['a'].Advance >> 6) * scale * 4;
        } else if ((x < size.x + pos.x ) && (x >= pos.x) && (y < size.y + pos.y) && y >= pos.y) {
            float xpos = x + c.Bearing.x * scale;
            float ypos = y + (fontsize  - c.Bearing.y) * scale;

            float w = c.Size.x * scale;
            float h = c.Size.y * scale;

            float vertices[6][4] = {
                {xpos,      ypos + h,   c.Start.x, c.End.y },
                {xpos + w,  ypos,       c.End.x, c.Start.y },
                {xpos,      ypos,       c.Start.x, c.Start.y },
                
                {xpos,      ypos + h,   c.Start.x, c.End.y },
                {xpos + w,  ypos + h,   c.End.x, c.End.y },
                {xpos + w,  ypos,       c.End.x, c.Start.y }
            };

            if (!full) {
                glBindTexture(GL_TEXTURE_2D, fontID);
                glBindBuffer(GL_ARRAY_BUFFER, vbo);
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glDrawArrays(GL_TRIANGLES, 0, 6);
            }

            x += (c.Advance >> 6) * scale;
        }
        if (showCursor && i == cursorLoc) {
        float xpos = x;
        float ypos = y;

        float w = fontsize / 12 * scale;
        float h = fontsize * scale;

        float vertices[6][4] = {
            {xpos,      ypos + h,   0.0f, 1.0f },
            {xpos + w,  ypos,       1.0f, 0.0f },
            {xpos,      ypos,       0.0f, 0.0f },
            
            {xpos,      ypos + h,   0.0f, 1.0f },
            {xpos + w,  ypos + h,   1.0f, 1.0f },
            {xpos + w,  ypos,       1.0f, 0.0f }
        };

        glBindTexture(GL_TEXTURE_2D, cursorID);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::DrawFrame() {
    BeginFrame();
}

void Renderer::BeginFrame() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::WindowResizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}