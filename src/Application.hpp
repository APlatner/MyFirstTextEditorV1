#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Filesystem.hpp"
#include "renderer/Renderer.hpp"
#include "renderer/Shader.hpp"
#include "input/Window.hpp"

class Application {
    public:
    Application();
    ~Application();

    void Run();

    private:
    // init functions
    void initRenderer();

    InputManager inputManager;
    Window window{inputManager};
    Filesystem filesystem{inputManager};

    Renderer renderer;
    Shader shader;
};