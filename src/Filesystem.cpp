#include "Filesystem.hpp"

#include <unistd.h>
#include <iostream>

Filesystem::Filesystem(InputManager &im) : inputManager{im} {
    u16 codes[] = {
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
        GLFW_KEY_BACKSPACE,
        GLFW_KEY_ENTER,
        GLFW_KEY_PERIOD,
        GLFW_KEY_LEFT,
        GLFW_KEY_RIGHT
    };
    for (u16 i = 0; i < 31; i++) {
        inputManager.RegisterEvent(codes[i], this, ControlEvent);
    }
    activeFileName = "";
}

Filesystem::~Filesystem() {
    u16 codes[] = {
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
        GLFW_KEY_BACKSPACE,
        GLFW_KEY_ENTER,
        GLFW_KEY_PERIOD,
        GLFW_KEY_LEFT,
        GLFW_KEY_RIGHT
    };
    for (u16 i = 0; i < 31; i++) {
        inputManager.UnRegisterEvent(codes[i], this, ControlEvent);
    }
    if (activeFile == NULL) {
        Close();
    }
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
    printf("CLOSED\n");
}

void Filesystem::SaveFile() {
    freopen(NULL, "w", activeFile);
    fprintf(activeFile, "%s", textBuffer.ToString().c_str());
    printf("SAVED\n");
}

bool Filesystem::ControlEvent(u16 code, void *sender, void *listener, EventData data) {
    Filesystem *filesystem = (Filesystem*)listener;
    if (filesystem->context == FILE_CONTEXT && data.action == GLFW_PRESS) {
        filesystem->FileContext(code, data);
    } else if (filesystem->context == TEXT_CONTEXT && data.action == GLFW_PRESS) {
        filesystem->TextContext(code, data);
    } else if (code == GLFW_KEY_O && data.action == GLFW_PRESS && data.mods & GLFW_MOD_CONTROL) {
        filesystem->context = FILE_CONTEXT;
        printf("FILE_CONTEXT\n");
    } else if (code == GLFW_KEY_S && data.action == GLFW_PRESS && data.mods & GLFW_MOD_CONTROL) {
        filesystem->SaveFile();
    } else if (code == GLFW_KEY_Q && data.action == GLFW_PRESS && data.mods & GLFW_MOD_CONTROL) {
        filesystem->Close();
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
        case GLFW_KEY_BACKSPACE:
            printf("deleting\n");
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
        case GLFW_KEY_PERIOD:
            textBuffer.Append('.');
            break;
        default: {
            textBuffer.Append((char)(code + 32 * !(data.mods & (GLFW_MOD_SHIFT ^ GLFW_MOD_CAPS_LOCK))));
        }
    }
}