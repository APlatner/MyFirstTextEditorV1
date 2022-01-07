#pragma once

#include "Defines.hpp"

#include <functional>
#include <vector>
#include <string>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

struct EventCodeEntry {
    // std::vector<u16> events;
};

class InputManager {
    public:
    InputManager();
    ~InputManager();

    bool RegisterEvent();
    bool UnRegisterEvent();

    bool FireEvent();

    static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
    private:

    // EventCodeEntry *registeredEvents;
};