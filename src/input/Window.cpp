#include "Window.hpp"
#include "renderer/Renderer.hpp"

#include <stdexcept>

Window::Window(InputManager &im) : inputManager{im} {
	if (glfwInit() != GLFW_TRUE) {
        throw std::runtime_error("Failed to initialize GLFW!");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    window = glfwCreateWindow(800, 600, "Hello Text Editor!", nullptr, nullptr);

    if (window == NULL) {
        glfwTerminate();
        throw std::runtime_error("Failed to create window!");
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, Renderer::WindowResizeCallback);
    glfwSetKeyCallback(window, InputManager::KeyCallback);
    glfwSetMouseButtonCallback(window, InputManager::MouseButtonCallback);
    glfwSetScrollCallback(window, InputManager::ScrollCallback);
    glfwSetWindowUserPointer(window, &inputManager);
}

Window::~Window() {
	glfwSetWindowUserPointer(window, NULL);
    glfwTerminate();
}