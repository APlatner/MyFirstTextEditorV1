
#include "Application.hpp"

#include <cstdio>

int main() {
    Application app(800, 600, "Hello Text Editor!", "res/fonts/NotoSansMono-Regular-Nerd-Font-Complete.ttf");
    
    try {
        app.run();
    } catch (const std::exception& e) {
        fprintf(stderr, "%s\n", e.what());
        return 1;
    }

    return 0;
}