#include "Application.hpp"

#include <stdexcept>
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>


Application::Application() {}

Application::~Application() {}

void Application::Run() {
    double startTime = glfwGetTime();
    double currentTime;
    bool showCursor = true;
    while (!window.ShouldClose()) {
        currentTime = glfwGetTime();
        if ((currentTime - startTime) > 0.5f) {
            startTime = currentTime;
            showCursor = !showCursor;
        }

        renderer.DrawFrame();
        renderer.renderChar(filesystem.textBuffer.ToString().c_str(), glm::uvec2{10, 10}, glm::vec2{600, 600}, 1, glm::vec3{1.0f}, showCursor, filesystem.textBuffer.GetCursorPos() - 1, 1.618);
        window.SwapBuffers();
        glfwPollEvents();
    }
}
