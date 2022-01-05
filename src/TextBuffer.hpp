#pragma once

#include "Defines.hpp"

#include <string>

static const int MAX_BUFFER_SIZE = 1024;

class TextBuffer {
    public:
    TextBuffer(std::string text);
    ~TextBuffer();

    TextBuffer& operator+(const char &rside);
    TextBuffer& operator+(const u16 &rside);
    TextBuffer& operator-(const u16 &rside);
    TextBuffer& operator++();
    TextBuffer& operator--();

    bool Append(char c);
    bool Delete();
    bool Ascend(u16 distance = 1);
    bool Descend(u16 distance = 1);
    bool Advance(u16 distance = 1);
    bool Retreat(u16 distance = 1);
    bool FullAdvance();
    bool FullRetreat();
    u16 GetCursorPos();

    char *ToString();
    void Test();

    private:
    char buffer[MAX_BUFFER_SIZE];
    u16 *lines;
    u16 lineCount;
    u16 currentLine;
    u16 preCursorIndex;
    u16 postCursorIndex;
    u16 maxPreCursorIndex;
    u16 minPostCursorIndex;
};