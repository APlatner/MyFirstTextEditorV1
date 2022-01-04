#include "Filesystem.hpp"

#include <unistd.h>
#include <iostream>

Filesystem::Filesystem() {
    currentWorkingDirectory = std::string(get_current_dir_name());
}

Filesystem::~Filesystem() {
    
}

void Filesystem::open(const char *filepath) {
    activeFile = fopen(filepath, "r");
}

void Filesystem::close() {
    freopen(NULL, "w", activeFile);
    fprintf(activeFile, "%s", precursorText.c_str());
    fclose(activeFile);
    precursorText = "";
}

void Filesystem::activateFile() {
    precursorText = "";
    postcursorText = "";
    char buffer[256];
    while (!feof(activeFile)) {
        fgets(buffer, 256, activeFile);
        precursorText += buffer;
    }
}