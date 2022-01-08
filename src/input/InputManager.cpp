#include "InputManager.hpp"

#include <unistd.h>
#include <stdexcept>


InputManager::InputManager() {
    registeredEvents = new EventCodeEntry[GLFW_KEY_LAST];
    // RegisterEvent(GLFW_KEY_LEFT_CONTROL, NULL, ControlCallback);
}

InputManager::~InputManager() {
    // UnRegisterEvent(GLFW_KEY_LEFT_CONTROL, NULL, ControlCallback);
    delete[] registeredEvents;
}

bool InputManager::RegisterEvent(u16 code, void *listener, Callback onEvent) {
    RegisteredEvent event{listener, onEvent};
    registeredEvents[code].events.push_back(event);

    return true;
}

bool InputManager::UnRegisterEvent(u16 code, void *listener, Callback onEvent) {
    for (auto i = registeredEvents[code].events.begin(); i != registeredEvents[code].events.end(); i++) {
        if (i->listener == listener) {
            registeredEvents[code].events.erase(i);
            return true;
        }
    }

    return false;
}

bool InputManager::FireEvent(u16 code, void *sender, EventData data) {
    if (registeredEvents[code].events.size() == 0) {
        return false;
    }

    for (RegisteredEvent &event : registeredEvents[code].events) {
        if (event.callback(code, sender, event.listener, data)) {
            return true;
        }
    }

    return false;
}

void InputManager::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    InputManager *inputManager = (InputManager*)glfwGetWindowUserPointer(window);
    if (key == GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose(window, true);
        glfwSetWindowUserPointer(window, NULL);
        return;
    }

    EventData data{action, mods};
    inputManager->FireEvent(key, inputManager, data);
}

void InputManager::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    
}

void InputManager::ScrollCallback(GLFWwindow *window, double xOffset, double yOffset) {
    
}

bool InputManager::ControlCallback(u16 code, void *sender, void *listener, EventData data) {
    if (((InputManager*)sender)->context == NULL_CONTEXT && code == GLFW_KEY_LEFT_CONTROL && data.action == GLFW_PRESS) {
        ((InputManager*)sender)->context = CONTROL_CONTEXT;
        printf("CONTROL_CONTEXT\n");
        return true;
    } else if (((InputManager*)sender)->context == CONTROL_CONTEXT && code == GLFW_KEY_LEFT_CONTROL && data.action == GLFW_RELEASE) {
        ((InputManager*)sender)->context = NULL_CONTEXT;
        printf("NULL_CONTEXT\n");
        return true;
    }
    printf("NO_CONTEXT_CHANGE\n");
    return false;
}