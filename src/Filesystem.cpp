#include "Filesystem.hpp"

#include <GL/glew.h>
#include <unistd.h>
#include <iostream>

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
    s.init("res/shaders/text_shader.vert", "res/shaders/text_shader.frag");
}

bool Filesystem::PrepBuffers() {
    // if (text == NULL) {
    //     return;
    // }
    // glUniform3f(glGetUniformLocation(s.ID, "textColor"), color.x, color.y, color.z);
    // glActiveTexture(GL_TEXTURE0);
    // glBindVertexArray(vao);
    // bool full = false;
    // float x = pos.x;
    // float y = pos.y;
    // x -= deltaX;
    // y -= deltaY;
    // for (uint32_t i = 0; text[i] != '\0'; i++) {
    //     Character c = characters[text[i]];
    //     if (text[i] == '\n') {
    //         x = pos.x;
    //         y += characters['I'].Size.y * scale * margin;
    //     } else if (text[i] == '\t') {
    //         x += (characters['a'].Advance >> 6) * scale * 4;
    //     } else if ((x < size.x + pos.x ) && (x >= pos.x) && (y < size.y + pos.y) && y >= pos.y) {
    //         float xpos = x + c.Bearing.x * scale;
    //         float ypos = y + (fontsize  - c.Bearing.y) * scale;

    //         float w = c.Size.x * scale;
    //         float h = c.Size.y * scale;

    //         float vertices[6][4] = {
    //             {xpos,      ypos + h,   c.Start.x, c.End.y },
    //             {xpos + w,  ypos,       c.End.x, c.Start.y },
    //             {xpos,      ypos,       c.Start.x, c.Start.y },
                
    //             {xpos,      ypos + h,   c.Start.x, c.End.y },
    //             {xpos + w,  ypos + h,   c.End.x, c.End.y },
    //             {xpos + w,  ypos,       c.End.x, c.Start.y }
    //         };

    //         if (!full) {
    //             glBindTexture(GL_TEXTURE_2D, fontID);
    //             glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //             glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    //             glBindBuffer(GL_ARRAY_BUFFER, 0);
    //             glDrawArrays(GL_TRIANGLES, 0, 6);
    //         }

    //         x += (c.Advance >> 6) * scale;
    //     }
    //     if (showCursor && i == cursorLoc && y > 0) {
    //     float xpos = x;
    //     float ypos = y;

    //     float w = fontsize / 12 * scale;
    //     float h = fontsize * scale;

    //     float vertices[6][4] = {
    //         {xpos,      ypos + h,   0.0f, 1.0f },
    //         {xpos + w,  ypos,       1.0f, 0.0f },
    //         {xpos,      ypos,       0.0f, 0.0f },
            
    //         {xpos,      ypos + h,   0.0f, 1.0f },
    //         {xpos + w,  ypos + h,   1.0f, 1.0f },
    //         {xpos + w,  ypos,       1.0f, 0.0f }
    //     };

    //     glBindTexture(GL_TEXTURE_2D, cursorID);
    //     glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //     glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    //     glBindBuffer(GL_ARRAY_BUFFER, 0);
    //     glDrawArrays(GL_TRIANGLES, 0, 6);
    // }
    // }
    // glBindVertexArray(0);
    // glBindTexture(GL_TEXTURE_2D, 0);
    // vbo.StoreData();
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
            break;
        case GLFW_KEY_ENTER:
            textBuffer.Append('\n');
            break;
        case GLFW_KEY_LEFT:
            textBuffer.Retreat();
            break;
        case GLFW_KEY_RIGHT:
            textBuffer.Advance();
            break;
        case GLFW_KEY_SPACE:
            textBuffer.Append(' ');
            break;
        case GLFW_KEY_PERIOD:
            textBuffer.Append('.');
            break;
        default: {
            textBuffer.Append((char)(code + 32 * !(data.mods & (GLFW_MOD_SHIFT ^ GLFW_MOD_CAPS_LOCK))));
        }
    }
}