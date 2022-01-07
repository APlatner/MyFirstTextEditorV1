
#include "Application.hpp"

#include <cstdio>

int main() {
    Application app;
    
    try {
        app.Run();
    } catch (const std::exception& e) {
        fprintf(stderr, "%s\n", e.what());
        return 1;
    }

    return 0;
}