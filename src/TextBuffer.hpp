#pragma once

#include "Defines.hpp"

#include <string>
#include <vector>

class TextBuffer {
    public:
    TextBuffer();
    ~TextBuffer();

    bool LoadText(const char *t);
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
    const u16 GetCursorPos();
    const std::string ToString();

    private:
    char *buffer;
    std::string text;
    std::vector<u16> lines;
    u16 preCursorIndex;
    u16 postCursorIndex;
    u16 maxPreCursorIndex;
    u16 minPostCursorIndex;
};