#pragma once

#include "Defines.hpp"

#include <string>
#include <vector>

class SplitBuffer {
    public:
    SplitBuffer();
    ~SplitBuffer();

    bool LoadText(const char *t);
    bool ClearText();
    bool Append(char c);
    bool Delete();
    bool Ascend(size_t distance = 1);
    bool Descend(size_t distance = 1);
    bool Advance(size_t distance = 1);
    bool Retreat(size_t distance = 1);
    bool LineAdvance();
    bool LineRetreat();
    bool FullAdvance();
    bool FullRetreat();
    const size_t GetCursorPos();
    const std::string ToString();

    private:
    char *buffer;
    size_t preCursorIndex;
    size_t postCursorIndex;
    size_t maxPreCursorIndex;
    size_t minPostCursorIndex;
};