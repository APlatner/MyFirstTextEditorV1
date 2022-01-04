#pragma once

#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

class Filesystem {
    public:
    Filesystem();
    ~Filesystem();

    void open(const char *filepath);
    void close();
    void activateFile();

    std::string currentWorkingDirectory;
    FILE *activeFile;
    std::string precursorText;
    std::string postcursorText;
};