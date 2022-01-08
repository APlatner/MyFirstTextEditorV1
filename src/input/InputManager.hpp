#pragma once

#include "Defines.hpp"

#include <functional>
#include <vector>
#include <string>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

enum EventContext {
    NULL_CONTEXT = 0,
    CONTROL_CONTEXT,
    TEXT_CONTEXT,
    FILE_CONTEXT,
    MAX_CONTEXT
};

struct EventData {
    int action;
    int mods;
};

typedef std::function<bool(u16, void*, void*, EventData)> Callback;

struct RegisteredEvent {
    void *listener;
    Callback callback;
};

struct EventCodeEntry {
    std::vector<RegisteredEvent> events;
};

class InputManager {
    public:
    InputManager();
    ~InputManager();

    bool RegisterEvent(u16 code, void *listener, Callback onEvent);
    bool UnRegisterEvent(u16 code, void *listener, Callback onEvent);

    bool FireEvent(u16 code, void *sender, EventData data);
    const EventContext GetEventContext() { return context; }
    void SetEventContext(EventContext c) { context = c; }

    static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
    static void ScrollCallback(GLFWwindow *window, double xOffset, double yOffset);
    private:
    static bool ControlCallback(u16 code, void *sender, void *listener, EventData data);
    EventContext context = NULL_CONTEXT;
    EventCodeEntry *registeredEvents;
};