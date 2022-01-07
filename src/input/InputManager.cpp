#include "InputManager.hpp"

#include <unistd.h>
#include <stdexcept>


InputManager::InputManager() {
    // registeredEvents = new EventCodeEntry[GLFW_KEY_LAST];
}

InputManager::~InputManager() {
    // delete registeredEvents;
}

bool InputManager::RegisterEvent() {

}

bool InputManager::UnRegisterEvent() {

}

bool InputManager::FireEvent() {

}

void InputManager::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    InputManager *inputManager = (InputManager*)glfwGetWindowUserPointer(window);
    if (key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, true);
    }
}

void InputManager::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    
}