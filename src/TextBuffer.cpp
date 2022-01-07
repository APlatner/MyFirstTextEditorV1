#include "TextBuffer.hpp"

#include <cstring>

static const int MAX_BUFFER_SIZE = 1024;

TextBuffer::TextBuffer() {
    buffer = new char[MAX_BUFFER_SIZE];
}

TextBuffer::~TextBuffer() {
    delete buffer;
}

bool TextBuffer::LoadText(const char *text) {
    strncpy(buffer, text, MAX_BUFFER_SIZE);
    maxPreCursorIndex = strnlen(buffer, MAX_BUFFER_SIZE);
    minPostCursorIndex = MAX_BUFFER_SIZE - 1;
    preCursorIndex = maxPreCursorIndex;
    postCursorIndex = minPostCursorIndex;
    buffer[minPostCursorIndex] = '\0';

    return true;
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
    return true;
}

bool TextBuffer::Descend(u16 distance) {
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
    if (preCursorIndex - distance < 0) {
        return false;
    }

    memcpy(&buffer[postCursorIndex - distance], &buffer[preCursorIndex - distance], distance);
    preCursorIndex -= distance;
    postCursorIndex -= distance;
    buffer[preCursorIndex] = '\0';

    return true;
}

bool TextBuffer::LineAdvance() {
    if (postCursorIndex == minPostCursorIndex) {
        return false;
    }
    while (buffer[postCursorIndex] != '\n' && postCursorIndex != minPostCursorIndex) {
        Advance();
    }

    return true;
}

bool TextBuffer::LineRetreat() {
    if (preCursorIndex == 0) {
        return false;
    }
    while (buffer[preCursorIndex - 1] != '\n' && preCursorIndex != 0) {
        Retreat();
    }

    return true;
}

bool TextBuffer::FullAdvance() {
    return Advance(maxPreCursorIndex - preCursorIndex);
}

bool TextBuffer::FullRetreat() {
    return Retreat(preCursorIndex);
}

u16 TextBuffer::GetCursorPos() {
    return preCursorIndex;
}

char *TextBuffer::ToString() {
    // TODO: optimize size constraint
    char *str = new char[MAX_BUFFER_SIZE];
    strncpy(str, buffer, MAX_BUFFER_SIZE);
    strncat(str, &buffer[postCursorIndex], MAX_BUFFER_SIZE - postCursorIndex);
    return str;
}
