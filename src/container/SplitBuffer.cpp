#include "SplitBuffer.hpp"

#include <cstring>

static const int MAX_BUFFER_SIZE = 4096;

SplitBuffer::SplitBuffer() {
    buffer = new char[MAX_BUFFER_SIZE];
    buffer[0] = '\0';
    maxPreCursorIndex = 0;
    minPostCursorIndex = MAX_BUFFER_SIZE - 1;
}

SplitBuffer::~SplitBuffer() {
    delete buffer;
}

bool SplitBuffer::LoadText(const char *text) {
    strncpy(buffer, text, MAX_BUFFER_SIZE);
    maxPreCursorIndex = strnlen(buffer, MAX_BUFFER_SIZE);
    minPostCursorIndex = MAX_BUFFER_SIZE - 1;
    preCursorIndex = maxPreCursorIndex;
    postCursorIndex = minPostCursorIndex;
    buffer[minPostCursorIndex] = '\0';

    return true;
}

bool SplitBuffer::ClearText() {
    maxPreCursorIndex = 0;
    preCursorIndex = 0;
    postCursorIndex = minPostCursorIndex;
    buffer[0] = '\0';

    return true;
}

bool SplitBuffer::Append(char c) {
    buffer[preCursorIndex] = c;
    preCursorIndex++;
    buffer[preCursorIndex] = '\0';
    maxPreCursorIndex++;

    return true;
}

bool SplitBuffer::Delete() {
    if (preCursorIndex == 0) {
        return false;
    }
    preCursorIndex--;
    maxPreCursorIndex--;
    buffer[preCursorIndex] = '\0';
    return true;
}

bool SplitBuffer::Ascend(size_t distance) {
    return true;
}

bool SplitBuffer::Descend(size_t distance) {
    return true;
}

bool SplitBuffer::Advance(size_t distance) {
    if (preCursorIndex + distance > maxPreCursorIndex || postCursorIndex + distance > minPostCursorIndex) {
        return false;
    }

    memcpy(&buffer[preCursorIndex], &buffer[postCursorIndex], distance);

    preCursorIndex += distance;
    postCursorIndex += distance;
    buffer[preCursorIndex] = '\0';

    return true;
}

bool SplitBuffer::Retreat(size_t distance) {
    if (preCursorIndex - distance < 0) {
        return false;
    }

    memcpy(&buffer[postCursorIndex - distance], &buffer[preCursorIndex - distance], distance);
    preCursorIndex -= distance;
    postCursorIndex -= distance;
    buffer[preCursorIndex] = '\0';

    return true;
}

bool SplitBuffer::LineAdvance() {
    if (postCursorIndex == minPostCursorIndex) {
        return false;
    }
    while (buffer[postCursorIndex] != '\n' && postCursorIndex != minPostCursorIndex) {
        Advance();
    }

    return true;
}

bool SplitBuffer::LineRetreat() {
    if (preCursorIndex == 0) {
        return false;
    }
    while (buffer[preCursorIndex - 1] != '\n' && preCursorIndex != 0) {
        Retreat();
    }

    return true;
}

bool SplitBuffer::FullAdvance() {
    return Advance(maxPreCursorIndex - preCursorIndex);
}

bool SplitBuffer::FullRetreat() {
    return Retreat(preCursorIndex);
}

const size_t SplitBuffer::GetCursorPos() {
    return preCursorIndex;
}

const std::string SplitBuffer::ToString() {
    // TODO: optimize size constraint
    std::string text = "";
    if (maxPreCursorIndex != 0) {
        text += buffer;
        text += &buffer[postCursorIndex];
    }
    return text;
}
