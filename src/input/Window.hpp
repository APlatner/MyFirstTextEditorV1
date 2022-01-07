#pragma once

#include "input/InputManager.hpp"

class Window {
	public:
	Window(InputManager &im);
	~Window();

	bool ShouldClose() { return glfwWindowShouldClose(window); }
    void SwapBuffers() { glfwSwapBuffers(window); }

	Window(Window const&) = delete;
	Window& operator=(Window const&) = delete;

	private:
	InputManager &inputManager;
	GLFWwindow *window;
};