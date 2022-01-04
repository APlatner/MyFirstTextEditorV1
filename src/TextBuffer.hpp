#pragma once

#include "Defines.hpp"

#include <string>

class TextBuffer {
    public:
    TextBuffer(std::string text);
    ~TextBuffer();



    private:
    char buffer[1024];
    u64 preCursorIndex;
    u64 postCursorIndex;
};