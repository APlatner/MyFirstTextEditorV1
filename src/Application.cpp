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
    filesystem.InitRenderer();
    while (!window.ShouldClose()) {
        currentTime = glfwGetTime();
        if ((currentTime - startTime) > 0.5f) {
            startTime = currentTime;
            showCursor = !showCursor;
        }

        renderer.DrawFrame();
        renderer.render(filesystem.s, filesystem.vao, filesystem.vbo, filesystem.ibo, (filesystem.textBuffer.ToString().length()) * 6, filesystem.fontID);
        if (showCursor) {
            renderer.render(filesystem.s, filesystem.cursorVAO, filesystem.cursorVBO, filesystem.ibo, 6, filesystem.cursorID);
        }
        window.SwapBuffers();
        glfwPollEvents();
    }
}
