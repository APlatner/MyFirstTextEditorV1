#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Filesystem.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "Input.hpp"

class Application {
    public:
    Application(int width, int height, const char *title, const char *font);
    ~Application();

    void run();

    private:
    // init functions
    void initWindow();
    void initRenderer();
    void initInput();
    void initFilesystem();

    // glfw callbacks
    static void windowSizeCallback(GLFWwindow *window, int width, int height);
    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

    Filesystem filesystem;

    // window related member variables
    GLFWwindow *window;
    int windowWidth, windowHeight;
    const char *windowTitle;

    Shader shader;
    Shader notShader;
    Renderer renderer;
    const char *fontPath;

    std::vector<Button> inputs;
    std::vector<TextArea> textAreas;
};