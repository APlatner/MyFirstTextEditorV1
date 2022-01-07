#include "Filesystem.hpp"

#include <unistd.h>
#include <iostream>

Filesystem::Filesystem(InputManager &im) : inputManager{im} {
    inputManager.RegisterEvent(GLFW_KEY_O, this, ControlEvent);
    inputManager.RegisterEvent(GLFW_KEY_ENTER, this, ControlEvent);
    activeFileName = "";
}

Filesystem::~Filesystem() {
    inputManager.UnRegisterEvent(GLFW_KEY_O, this, ControlEvent);
    inputManager.UnRegisterEvent(GLFW_KEY_ENTER, this, ControlEvent);
    Close();
}

void Filesystem::Open() {
    activeFileName = "test.txt";
    activeFile = fopen(activeFileName.c_str(), "r");
    std::string text = "";
    char buffer[256];
    while (!feof(activeFile)) {
        fgets(buffer, 256, activeFile);
        text += buffer;
    }
    textBuffer.LoadText(text.c_str());
    freopen(NULL, "w", activeFile);
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
        filesystem->activeFileName += (char)code;
    } else if (filesystem->inputManager.GetEventContext() == FILE_CONTEXT && code == GLFW_KEY_ENTER && data.action == GLFW_PRESS) {
        filesystem->Open();
        printf("Opened %s\n", filesystem->activeFileName.c_str());
        filesystem->inputManager.SetEventContext(NULL_CONTEXT);
        printf("NULL_CONTEXT\n");
    } else if (code == GLFW_KEY_O && data.action == GLFW_PRESS && data.mods & GLFW_MOD_CONTROL) {
        filesystem->inputManager.SetEventContext(FILE_CONTEXT);
        printf("FILE_CONTEXT\n");
    } else if (code == GLFW_KEY_S && data.action == GLFW_PRESS && data.mods & GLFW_MOD_CONTROL) {
        filesystem->SaveFile();
    }

    return true;
}