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
        GLFW_KEY_ENTER,
        GLFW_KEY_PERIOD
    };
    for (u16 i = 0; i < 28; i++) {
        inputManager.RegisterEvent(codes[i], this, ControlEvent);
    }
    // inputManager.RegisterEvent(GLFW_KEY_O, this, ControlEvent);
    // inputManager.RegisterEvent(GLFW_KEY_ENTER, this, ControlEvent);
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
        GLFW_KEY_ENTER,
        GLFW_KEY_PERIOD
    };
    for (u16 i = 0; i < 28; i++) {
        inputManager.UnRegisterEvent(codes[i], this, ControlEvent);
    }
    // inputManager.UnRegisterEvent(GLFW_KEY_O, this, ControlEvent);
    // inputManager.UnRegisterEvent(GLFW_KEY_ENTER, this, ControlEvent);
    if (activeFile == NULL) {
        Close();
    }
}

void Filesystem::Open() {
    activeFile = fopen(activeFileName.c_str(), "r");
    std::string text = "";
    char buffer[256];
    while (!feof(activeFile)) {
        fgets(buffer, 256, activeFile);
        text += buffer;
    }
    textBuffer.LoadText(text.c_str());
    freopen(NULL, "w", activeFile);
    printf("%s\n", textBuffer.ToString());
}

void Filesystem::Close() {
    activeFileName = "";
    fclose(activeFile);
    printf("CLOSED\n");
}

void Filesystem::SaveFile() {

}

bool Filesystem::ControlEvent(u16 code, void *sender, void *listener, EventData data) {
    Filesystem *filesystem = (Filesystem*)listener;
    if (filesystem->inputManager.GetEventContext() == FILE_CONTEXT && code != GLFW_KEY_ENTER && data.action == GLFW_PRESS) {
        filesystem->activeFileName += (char)(code + 32 * !(data.mods & (GLFW_MOD_SHIFT ^ GLFW_MOD_CAPS_LOCK)));
        printf("%c", (char)(code + 32 * !(data.mods & (GLFW_MOD_SHIFT ^ GLFW_MOD_CAPS_LOCK))));
        fflush(stdout);
    } else if (filesystem->inputManager.GetEventContext() == FILE_CONTEXT && code == GLFW_KEY_ENTER && data.action == GLFW_PRESS) {
        printf("\n");
        filesystem->Open();
        filesystem->inputManager.SetEventContext(TEXT_CONTEXT);
        printf("TEXT_CONTEXT\n");
    } else if (code == GLFW_KEY_O && data.action == GLFW_PRESS && data.mods & GLFW_MOD_CONTROL) {
        filesystem->inputManager.SetEventContext(FILE_CONTEXT);
        printf("FILE_CONTEXT\n");
    } else if (code == GLFW_KEY_S && data.action == GLFW_PRESS && data.mods & GLFW_MOD_CONTROL) {
        filesystem->SaveFile();
    } else if (code == GLFW_KEY_Q && data.action == GLFW_PRESS && data.mods & GLFW_MOD_CONTROL) {
        filesystem->Close();
    }

    return true;
}
