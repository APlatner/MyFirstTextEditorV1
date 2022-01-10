#include "Application.hpp"
#include "display/FileDisplay.hpp"

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
    FileDisplay fsDisplay;
    fsDisplay.Init();
    fsDisplay.Update();

    filesystem.InitRenderer();
    while (!window.ShouldClose()) {
        currentTime = glfwGetTime();
        if ((currentTime - startTime) > 0.5f) {
            startTime = currentTime;
            showCursor = !showCursor;
        }

        renderer.DrawFrame();
        fsDisplay.Render();
        filesystem.Render(showCursor);
        window.SwapBuffers();
        glfwPollEvents();
    }
}
