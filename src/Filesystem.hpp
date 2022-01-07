#pragma once

#include "Defines.hpp"
#include "input/InputManager.hpp"
#include "TextBuffer.hpp"

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

class Filesystem {
    public:
    Filesystem(InputManager &im);
    ~Filesystem();

    void Open();
    void Close();
    void SaveFile();

    InputManager &inputManager;
    TextBuffer textBuffer;
    // std::string currentWorkingDirectory;
    std::string activeFileName;
    FILE *activeFile;
    std::string precursorText;
    std::string postcursorText;

    private:
    static bool ControlEvent(u16 code, void *sender, void *listener, EventData data);
};