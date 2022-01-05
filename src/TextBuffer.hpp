#pragma once

#include "Defines.hpp"

#include <string>
#include <vector>

static const int MAX_BUFFER_SIZE = 1024;

class TextBuffer {
    public:
    TextBuffer(std::string text);
    ~TextBuffer();

    bool Append(char c);
    bool Delete();
    bool Ascend(u16 distance = 1);
    bool Descend(u16 distance = 1);
    bool Advance(u16 distance = 1);
    bool Retreat(u16 distance = 1);
    bool LineAdvance();
    bool LineRetreat();
    bool FullAdvance();
    bool FullRetreat();
    u16 GetCursorPos();
    char *ToString();

    private:

    char buffer[MAX_BUFFER_SIZE];
    std::vector<u16> lines;
    u16 currentLine;
    u16 currentLineIndex;
    u16 preCursorIndex;
    u16 postCursorIndex;
    u16 maxPreCursorIndex;
    u16 minPostCursorIndex;
};