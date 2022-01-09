#include "Filesystem.hpp"

#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <unistd.h>
#include <iostream>

const int fontsize = 16;

Filesystem::Filesystem(InputManager &im) : inputManager{im} {
    u16 codes[] = {
        GLFW_KEY_0,
        GLFW_KEY_1,
        GLFW_KEY_2,
        GLFW_KEY_3,
        GLFW_KEY_4,
        GLFW_KEY_5,
        GLFW_KEY_6,
        GLFW_KEY_7,
        GLFW_KEY_8,
        GLFW_KEY_9,
        GLFW_KEY_A,
        GLFW_KEY_B,
        GLFW_KEY_C,
        GLFW_KEY_D,
        GLFW_KEY_E,
        GLFW_KEY_F,
        GLFW_KEY_G,
        GLFW_KEY_H,
        GLFW_KEY_I,
        GLFW_KEY_J,
        GLFW_KEY_K,
        GLFW_KEY_L,
        GLFW_KEY_M,
        GLFW_KEY_N,
        GLFW_KEY_O,
        GLFW_KEY_P,
        GLFW_KEY_Q,
        GLFW_KEY_R,
        GLFW_KEY_S,
        GLFW_KEY_T,
        GLFW_KEY_U,
        GLFW_KEY_V,
        GLFW_KEY_W,
        GLFW_KEY_X,
        GLFW_KEY_Y,
        GLFW_KEY_Z,
        GLFW_KEY_SPACE,
        GLFW_KEY_BACKSPACE,
        GLFW_KEY_ENTER,
        GLFW_KEY_PERIOD,
        GLFW_KEY_LEFT,
        GLFW_KEY_RIGHT,
        GLFW_KEY_HOME,
        GLFW_KEY_END
    };
    for (u16 i = 0; i < 44; i++) {
        inputManager.RegisterEvent(codes[i], this, ControlEvent);
    }
    activeFileName = "";
}

Filesystem::~Filesystem() {
    u16 codes[] = {
        GLFW_KEY_0,
        GLFW_KEY_1,
        GLFW_KEY_2,
        GLFW_KEY_3,
        GLFW_KEY_4,
        GLFW_KEY_5,
        GLFW_KEY_6,
        GLFW_KEY_7,
        GLFW_KEY_8,
        GLFW_KEY_9,
        GLFW_KEY_A,
        GLFW_KEY_B,
        GLFW_KEY_C,
        GLFW_KEY_D,
        GLFW_KEY_E,
        GLFW_KEY_F,
        GLFW_KEY_G,
        GLFW_KEY_H,
        GLFW_KEY_I,
        GLFW_KEY_J,
        GLFW_KEY_K,
        GLFW_KEY_L,
        GLFW_KEY_M,
        GLFW_KEY_N,
        GLFW_KEY_O,
        GLFW_KEY_P,
        GLFW_KEY_Q,
        GLFW_KEY_R,
        GLFW_KEY_S,
        GLFW_KEY_T,
        GLFW_KEY_U,
        GLFW_KEY_V,
        GLFW_KEY_W,
        GLFW_KEY_X,
        GLFW_KEY_Y,
        GLFW_KEY_Z,
        GLFW_KEY_SPACE,
        GLFW_KEY_BACKSPACE,
        GLFW_KEY_ENTER,
        GLFW_KEY_PERIOD,
        GLFW_KEY_LEFT,
        GLFW_KEY_RIGHT,
        GLFW_KEY_HOME,
        GLFW_KEY_END
    };
    for (u16 i = 0; i < 44; i++) {
        inputManager.UnRegisterEvent(codes[i], this, ControlEvent);
    }
    if (activeFileName != "") {
        Close();
    }
}

bool Filesystem::InitRenderer() {
    FT_Library library;
    if (FT_Init_FreeType(&library)) {
        printf("Failed to init freetype!\n");
        return false;
    }

    FT_Face face;
    if (FT_New_Face(library, "res/fonts/NotoSansMono-Regular-Nerd-Font-Complete.ttf", 0, &face)) {
        printf("Failed to load font!\n");
        return false;
    }

    FT_Set_Pixel_Sizes(face, 0, fontsize);
    uint8_t *cursor = (unsigned char*)malloc(sizeof(char) * fontsize * 4);
    memset(cursor, 0xff, fontsize * 4);
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
    uint8_t *font = (unsigned char*)malloc(sizeof(char) * width * height * 100);
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

        characters[(int)c] = character;
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

    FT_Done_Face(face);
    FT_Done_FreeType(library);

    return true;
}

bool Filesystem::PrepBuffers() {
    s.init("res/shaders/text_shader.vert", "res/shaders/text_shader.frag");
    s.use();
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f);
    glUniformMatrix4fv(glGetUniformLocation(s.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    std::string text = textBuffer.ToString();
    vbo.StoreData(nullptr, (text.length()) * 6 * 4 * sizeof(float));
    BufferLayout layout;
    vao.AddBuffer(vbo, layout);
    color  = glm::vec3{1.0f, 1.0f, 1.0f};
    position = glm::uvec2{10, 10};
    size = glm::uvec2{600, 600};
    glUniform3f(glGetUniformLocation(s.ID, "textColor"), color.x, color.y, color.z);

    float x = position.x;
    float y = position.y;
    // if (text.length() == 0) {
    //     float xpos = x;
    //     float ypos = y;

    //     float w = fontsize / 12 * fontScale;
    //     float h = fontsize * fontScale;

    //     float vertices[6][4] {
    //         {xpos, ypos + h, 0.0f, 1.0f},
    //         {xpos + w, ypos, 1.0f, 0.0f},
    //         {xpos, ypos, 0.0f, 0.0f},

    //         {xpos, ypos + h, 0.0f, 1.0f},
    //         {xpos + w, ypos + h, 1.0f, 1.0f},
    //         {xpos + w, ypos, 1.0f, 0.0f}
    //     };
    //     glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    // }
    for (uint32_t i = 0; i < text.length(); i++) {
        Character c = characters[(int)text[i]];
        if (text[i] == '\n') {
            x = position.x;
            y += characters[(int)'I'].Size.y * fontScale * fontMargin;
        } else if (text[i] == '\t') {
            x += (characters[(int)'a'].Advance >> 6) * fontScale * 4;
        } else if ((x < size.x + position.x ) && (x >= position.x) && (y < size.y + position.y) && y >= position.y) {
            float xpos = x + c.Bearing.x * fontScale;
            float ypos = y + (fontsize  - c.Bearing.y) * fontScale;

            float w = c.Size.x * fontScale;
            float h = c.Size.y * fontScale;

            float vertices[6][4] {
                {xpos, ypos + h, c.Start.x, c.End.y},
                {xpos + w, ypos, c.End.x, c.Start.y},
                {xpos, ypos, c.Start.x, c.Start.y},

                {xpos, ypos + h, c.Start.x, c.End.y},
                {xpos + w, ypos + h, c.End.x, c.End.y},
                {xpos + w, ypos, c.End.x, c.Start.y}
            };
            glBufferSubData(GL_ARRAY_BUFFER, i * 24 * sizeof(float), sizeof(vertices), vertices);
            // printf("buffer sub data offset: %lu\n", i * 24 * sizeof(float));
            // printf("xpos: %f, ypos: %f, texX: %f, texY: %f\n", vertices[0][0], vertices[0][1], vertices[0][2], vertices[0][3]);
            // vertices[0 + i * 24] = xpos;
            // vertices[1 + i * 24] = ypos + h;
            // vertices[2 + i * 24] = c.Start.x;
            // vertices[3 + i * 24] = c.End.y;
            // vertices[4 + i * 24] = xpos + w;
            // vertices[5 + i * 24] = ypos;
            // vertices[6 + i * 24] = c.End.x;
            // vertices[7 + i * 24] = c.Start.y;
            // vertices[8 + i * 24] = xpos;
            // vertices[9 + i * 24] = ypos;
            // vertices[10 + i * 24] = c.Start.x;
            // vertices[11 + i * 24] = c.Start.y;
            // vertices[12 + i * 24] = xpos;
            // vertices[13 + i * 24] = ypos + h;
            // vertices[14 + i * 24] = c.Start.x;
            // vertices[15 + i * 24] = c.End.y;
            // vertices[16 + i * 24] = xpos + w;
            // vertices[17 + i * 24] = ypos + h;
            // vertices[18 + i * 24] = c.End.x;
            // vertices[19 + i * 24] = c.End.y;
            // vertices[20 + i * 24] = xpos + w;
            // vertices[21 + i * 24] = ypos;
            // vertices[22 + i * 24] = c.End.x;
            // vertices[23 + i * 24] = c.Start.y;

            x += (c.Advance >> 6) * fontScale;
        }
        if (true && i == textBuffer.GetCursorPos() - 1) {
            float xpos = x;
            float ypos = y;

            float w = fontsize / 12 * fontScale;
            float h = fontsize * fontScale;

            float vertices[6][4] {
                {xpos, ypos + h, 0.0f, 1.0f},
                {xpos + w, ypos, 1.0f, 0.0f},
                {xpos, ypos, 0.0f, 0.0f},

                {xpos, ypos + h, 0.0f, 1.0f},
                {xpos + w, ypos + h, 1.0f, 1.0f},
                {xpos + w, ypos, 1.0f, 0.0f}
            };

            // vertices[0 + i * 24] = xpos;
            // vertices[1 + i * 24] = ypos + h;
            // vertices[2 + i * 24] = 0.0f;
            // vertices[3 + i * 24] = 1.0f;
            // vertices[4 + i * 24] = xpos + w;
            // vertices[5 + i * 24] = ypos;
            // vertices[6 + i * 24] = 1.0f;
            // vertices[7 + i * 24] = 0.0f;
            // vertices[8 + i * 24] = xpos;
            // vertices[9 + i * 24] = ypos;
            // vertices[10 + i * 24] = 0.0f;
            // vertices[11 + i * 24] = 0.0f;
            // vertices[12 + i * 24] = xpos;
            // vertices[13 + i * 24] = ypos + h;
            // vertices[14 + i * 24] = 0.0f;
            // vertices[15 + i * 24] = 1.0f;
            // vertices[16 + i * 24] = xpos + w;
            // vertices[17 + i * 24] = ypos + h;
            // vertices[18 + i * 24] = 1.0f;
            // vertices[19 + i * 24] = 1.0f;
            // vertices[20 + i * 24] = xpos + w;
            // vertices[21 + i * 24] = ypos;
            // vertices[22 + i * 24] = 1.0f;
            // vertices[23 + i * 24] = 0.0f;
            // glBufferSubData(GL_ARRAY_BUFFER, i * 24 * sizeof(float), sizeof(vertices), vertices);
        }
    }

    return true;
}

void Filesystem::Open() {
    activeFile = fopen(activeFileName.c_str(), "r");
    std::string text = "";
    char buffer[256];
    while (!feof(activeFile)) {
        buffer[0] = '\0';
        fgets(buffer, 256, activeFile);
        text += buffer;
    }
    textBuffer.LoadText(text.c_str());
    PrepBuffers();
}

void Filesystem::Close() {
    activeFileName = "";
    fclose(activeFile);
    textBuffer.ClearText();
    printf("CLOSED\n");
}

void Filesystem::SaveFile() {
    freopen(NULL, "w", activeFile);
    fprintf(activeFile, "%s", textBuffer.ToString().c_str());
    printf("SAVED\n");
}

bool Filesystem::ControlEvent(u16 code, void *sender, void *listener, EventData data) {
    Filesystem *filesystem = (Filesystem*)listener;
    if (code == GLFW_KEY_O && data.action == GLFW_PRESS && data.mods & GLFW_MOD_CONTROL) {
        filesystem->context = FILE_CONTEXT;
        printf("FILE_CONTEXT\n");
    } else if (code == GLFW_KEY_S && data.action == GLFW_PRESS && data.mods & GLFW_MOD_CONTROL) {
        filesystem->SaveFile();
    } else if (code == GLFW_KEY_Q && data.action == GLFW_PRESS && data.mods & GLFW_MOD_CONTROL) {
        filesystem->Close();
        filesystem->context = NULL_CONTEXT;
    } else if (filesystem->context == FILE_CONTEXT && data.action != GLFW_RELEASE) {
        filesystem->FileContext(code, data);
    } else if (filesystem->context == TEXT_CONTEXT && data.action != GLFW_RELEASE) {
        filesystem->TextContext(code, data);
    }

    return true;
}

void Filesystem::FileContext(u16 code, EventData data) {
    switch (code) {
        case GLFW_KEY_BACKSPACE:
            activeFileName.pop_back();
            break;
        case GLFW_KEY_ENTER: {
            printf("\n");
            Open();
            context = TEXT_CONTEXT;
            printf("TEXT_CONTEXT\n");
        } break;
        case GLFW_KEY_PERIOD: {
            activeFileName += '.';
            printf("%c", '.');
            fflush(stdout);
        } break;
        default: {
            activeFileName += (char)(code + 32 * !(data.mods & (GLFW_MOD_SHIFT ^ GLFW_MOD_CAPS_LOCK)));
            printf("%c", (char)(code + 32 * !(data.mods & (GLFW_MOD_SHIFT ^ GLFW_MOD_CAPS_LOCK))));
            fflush(stdout);
        }
    }
}

void Filesystem::TextContext(u16 code, EventData data) {
    switch (code) {
        case GLFW_KEY_HOME:
            textBuffer.LineRetreat();
            break;
        case GLFW_KEY_END:
            textBuffer.LineAdvance();
            break;
        case GLFW_KEY_BACKSPACE:
            textBuffer.Delete();
            PrepBuffers();
            break;
        case GLFW_KEY_ENTER:
            textBuffer.Append('\n');
            PrepBuffers();
            break;
        case GLFW_KEY_LEFT:
            textBuffer.Retreat();
            break;
        case GLFW_KEY_RIGHT:
            textBuffer.Advance();
            break;
        case GLFW_KEY_SPACE:
            textBuffer.Append(' ');
            PrepBuffers();
            break;
        case GLFW_KEY_PERIOD:
            textBuffer.Append('.');
            PrepBuffers();
            break;
        default: {
            textBuffer.Append((char)(code + 32 * !(data.mods & (GLFW_MOD_SHIFT ^ GLFW_MOD_CAPS_LOCK))));
            PrepBuffers();
        }
    }
}