#include "Application.hpp"


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
    initInput();
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
    glfwSetWindowSizeCallback(window, windowSizeCallback);
    glfwSetKeyCallback(window, keyCallback);

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

void action() {
    
}

void Application::initInput() {
    Button start(glm::uvec2(0, 600), glm::uvec2(100, 100), glm::uvec2(10, 10), glm::uvec2(10, 10), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), action);
    inputs.push_back(start);
}

void Application::initFilesystem() {
    filesystem.open("src/Config.hpp");
    filesystem.activateFile();
}

void Application::run() {
    double lastTime = glfwGetTime();
    std::string display = "";
    bool cursor = false;
    TextArea textArea;
    textArea.position = glm::uvec2{200, 0};
    textArea.size = glm::uvec2{600, 600};
    textArea.background = glm::vec3{0.5f, 0.5f, 0.5f};
    textArea.foreground = glm::vec3{1.0f, 1.0f, 1.0f};
    textArea.text = filesystem.precursorText;
    glfwSetWindowUserPointer(window, &textArea.text);

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
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        for (Button &button : inputs) {
            button.render(shader, renderer);
        }
        textArea.render(shader, renderer, cursor);
        fileDisplay.render(shader, renderer);
        glfwSwapBuffers(window);
        glfwWaitEvents();
    }
    filesystem.precursorText = textArea.text;
    filesystem.close();
    glfwSetWindowUserPointer(window, NULL);
}

void Application::windowSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Application::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action != GLFW_RELEASE) {
        bool caps = (mods & GLFW_MOD_SHIFT) ^ (mods & GLFW_MOD_CAPS_LOCK);
        std::string *str = (std::string*)glfwGetWindowUserPointer(window);
        switch (key) {
            case GLFW_KEY_ESCAPE: {
                glfwSetWindowShouldClose(window, true);
                return;
            } break;
            case GLFW_KEY_ENTER: {
                *str += '\n';
            } break;
            case GLFW_KEY_TAB: {
                *str += '\t';
            } break;
            case GLFW_KEY_BACKSPACE: {
                if (str->length() > 0) {
                    str->pop_back();
                }
            } break;
            case GLFW_KEY_LEFT_SHIFT: 
            case GLFW_KEY_LEFT_CONTROL: 
            case GLFW_KEY_RIGHT_SHIFT: 
            case GLFW_KEY_RIGHT_CONTROL: 
            case GLFW_KEY_LEFT_ALT:
            case GLFW_KEY_RIGHT_ALT: break;
            case GLFW_KEY_A:
            case GLFW_KEY_B:
            case GLFW_KEY_C:
            case GLFW_KEY_D:
            case GLFW_KEY_E:
            case GLFW_KEY_F:
            case GLFW_KEY_G:
            case GLFW_KEY_H:
            case GLFW_KEY_I:
            case GLFW_KEY_J:
            case GLFW_KEY_K:
            case GLFW_KEY_L:
            case GLFW_KEY_M:
            case GLFW_KEY_N:
            case GLFW_KEY_O:
            case GLFW_KEY_P:
            case GLFW_KEY_Q:
            case GLFW_KEY_R:
            case GLFW_KEY_S:
            case GLFW_KEY_T:
            case GLFW_KEY_U:
            case GLFW_KEY_V:
            case GLFW_KEY_W:
            case GLFW_KEY_X:
            case GLFW_KEY_Y:
            case GLFW_KEY_Z: {
                *str += (char)(key + 32 * !caps);
            } break;
            case GLFW_KEY_0:
                *str += (char)(key - 7 * (mods & GLFW_MOD_SHIFT));
                break;
            case GLFW_KEY_1:
                *str += (char)(key - 16 * (mods & GLFW_MOD_SHIFT));
                break;
            case GLFW_KEY_2:
                *str += (char)(key + 14 * (mods & GLFW_MOD_SHIFT));
                break;
            case GLFW_KEY_3:
                *str += (char)(key - 16 * (mods & GLFW_MOD_SHIFT));
                break;
            case GLFW_KEY_4:
            case GLFW_KEY_5:
            case GLFW_KEY_6:
            case GLFW_KEY_7:
            case GLFW_KEY_8:
            case GLFW_KEY_9: {
                *str += (char)(key);
            } break;
            default: {
                *str += (char)key;
            }
        }
    }
}