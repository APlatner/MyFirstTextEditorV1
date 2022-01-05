#include "TextBuffer.hpp"

#include <cstring>

TextBuffer::TextBuffer(std::string text) {
    lineCount = 0;
    size_t loc = 0;
    loc = text.find('\n', loc);
    lineCount++;
    while (loc != std::string::npos) {
        loc = text.find('\n', loc + 1);
        lineCount++;
    }
    currentLine = lineCount - 1;
    lines = new u16[lineCount];
    loc = 0;
    // loc = text.find('\n', loc);
    lines[0] = 0;
    for (u16 i = 1; i < lineCount; i++) {
        loc = text.find('\n', loc) + 1;
        lines[i] = loc;
    }

    strncpy(buffer, text.c_str(), MAX_BUFFER_SIZE);
    maxPreCursorIndex = strnlen(buffer, MAX_BUFFER_SIZE);
    minPostCursorIndex = MAX_BUFFER_SIZE - 1;
    preCursorIndex = maxPreCursorIndex;
    postCursorIndex = minPostCursorIndex;
    buffer[minPostCursorIndex] = '\0';
}

TextBuffer::~TextBuffer() {
    delete lines;
}

TextBuffer& TextBuffer::operator+(const char &rside) {
    Append(rside);
}

TextBuffer& TextBuffer::operator+(const u16 &rside) {
    Advance(rside);
}

TextBuffer& TextBuffer::operator-(const u16 &rside) {
    Retreat(rside);
}

TextBuffer& TextBuffer::operator++() {
    Advance();
}

TextBuffer& TextBuffer::operator--() {
    Retreat();
}

bool TextBuffer::Append(char c) {
    buffer[preCursorIndex] = c;
    preCursorIndex++;
    buffer[preCursorIndex] = '\0';
    maxPreCursorIndex++;
    return true;
}

bool TextBuffer::Delete() {
    if (preCursorIndex == 0) {
        return false;
    }
    preCursorIndex--;
    maxPreCursorIndex--;
    buffer[preCursorIndex] = '\0';
    return true;
}

bool TextBuffer::Ascend(u16 distance) { 
    if (currentLine + distance > lineCount) {
        return false;
    }
    
    Advance(lines[currentLine + distance] - lines[currentLine]);
    currentLine += distance;

    return true;
}
bool TextBuffer::Descend(u16 distance) {
    if (currentLine - distance < 0) {
        return false;
    }

    Retreat(lines[currentLine] - lines[currentLine - distance]);
    currentLine -= distance;

    return true;
}

bool TextBuffer::Advance(u16 distance) {
    if (preCursorIndex + distance > maxPreCursorIndex || postCursorIndex + distance > minPostCursorIndex) {
        return false;
    }

    memcpy(&buffer[preCursorIndex], &buffer[postCursorIndex], distance);

    preCursorIndex += distance;
    postCursorIndex += distance;
    buffer[preCursorIndex] = '\0';

    return true;
}

bool TextBuffer::Retreat(u16 distance) {
    if (preCursorIndex - distance < 0 || postCursorIndex - distance < maxPreCursorIndex) {
        return false;
    }

    memcpy(&buffer[postCursorIndex - distance], &buffer[preCursorIndex - distance], distance);

    preCursorIndex -= distance;
    postCursorIndex -= distance;
    buffer[preCursorIndex] = '\0';

    return true;
}

bool TextBuffer::FullAdvance() {
    Advance(maxPreCursorIndex - preCursorIndex);
}

bool TextBuffer::FullRetreat() {
    Retreat(preCursorIndex);
}

u16 TextBuffer::GetCursorPos() {
    return preCursorIndex;
}

char *TextBuffer::ToString() {
    char *str = new char[1024];
    strncpy(str, buffer, 1024);
    strncat(str, &buffer[postCursorIndex], 1024 - postCursorIndex);
    return str;
}

void TextBuffer::Test() {
    printf("%s\n\n", buffer);
    printf("%s\n\n", &buffer[postCursorIndex]);
}