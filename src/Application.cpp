#include "Application.hpp"
#include "TextBuffer.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <stdexcept>
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>


Application::Application(int width, int height, const char *title, const char *font) :
    windowWidth{width}, windowHeight{height}, windowTitle{title}, fontPath{font} {
    initWindow();
    initRenderer();
    initFilesystem();
}

Application::~Application() {
    // glfwDestroyCursor(cursor);
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::initWindow() {
    if (glfwInit() != GLFW_TRUE) {
        throw std::runtime_error("Failed to initialize GLFW!");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, nullptr, nullptr);

    if (window == NULL) {
        glfwTerminate();
        throw std::runtime_error("Failed to create window!");
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, Renderer::WindowResizeCallback);
    glfwSetKeyCallback(window, Input::KeyCallback);
    glfwSetMouseButtonCallback(window, Input::MouseButtonCallback);

    if (glewInit() != GLEW_OK) {
        glfwDestroyWindow(window);
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLEW!");
    }
}

void Application::initRenderer() {
    renderer.initFreetype(fontPath);

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    shader.init("res/shaders/text_shader.vert", "res/shaders/text_shader.frag");
    shader.use();

    glm::mat4 projection = glm::ortho(0.0f, (float)windowWidth, (float)windowHeight, 0.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}

void Application::initFilesystem() {
    filesystem.open("test.txt");
    filesystem.activateFile();
}

void Application::run() {
    double lastTime = glfwGetTime();
    bool cursor = false;
    TextArea textArea;
    textArea.position = glm::uvec2{200, 0};
    textArea.size = glm::uvec2{600, 600};
    textArea.background = glm::vec3{0.5f, 0.5f, 0.5f};
    textArea.foreground = glm::vec3{1.0f, 1.0f, 1.0f};
    textArea.text = filesystem.precursorText;
    textArea.textBuffer = new TextBuffer(textArea.text);
    Input input;
    input.textArea = textArea;
    glfwSetWindowUserPointer(window, &input);

    FileDisplay fileDisplay(glm::uvec2{0, 0}, glm::uvec2{200, 25}, glm::uvec2{0,0}, glm::uvec2{0,0}, glm::vec3{0.5f, 0.5f, 0.5f}, glm::vec3{1.0f, 1.0f, 1.0f});
    
    while (!glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        
        if (currentTime - lastTime >= 0.5) {
            if (cursor) {
                cursor = false;
            } else {
                cursor = true;
            }
            lastTime += 0.5;
        }

        renderer.DrawFrame();

        textArea.render(shader, renderer, cursor);
        fileDisplay.render(shader, renderer);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    filesystem.precursorText = textArea.textBuffer->ToString();
    filesystem.close();
    glfwSetWindowUserPointer(window, NULL);
}
