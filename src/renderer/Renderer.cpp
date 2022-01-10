
#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>

Renderer::Renderer(InputManager &im) : inputManager{im} {
    if (glewInit() != GLEW_OK) {
        std::runtime_error("Failed to init GLEW!");
    }

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(GLDebugMessageCallback, NULL);

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Renderer::~Renderer() {
    
}

void Renderer::render(Shader &shader, VertexArray &vertexArray, VertexBuffer &vertexBuffer, IndexBuffer &indexBuffer, uint32_t count, uint32_t &textureID) {
    shader.use();
    vertexArray.Bind();
    vertexBuffer.Bind();
    glBindTexture(GL_TEXTURE_2D, textureID);
    glDrawArrays(GL_TRIANGLES, 0, count);
}

void Renderer::DrawFrame() {
    BeginFrame();
}

void Renderer::BeginFrame() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::WindowResizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Renderer::GLDebugMessageCallback(uint32_t source, uint32_t type, uint32_t id, uint32_t severity, int32_t length, const char *message, const void *userParam) {
    const char *_source;
    const char *_type;
    const char *_severity;
    switch (source) {
        case GL_DEBUG_SOURCE_API:
            _source = "API";
            break;
        case GL_DEBUG_SOURCE_APPLICATION:
            _source = "Application";
            break;
        case GL_DEBUG_SOURCE_OTHER:
            _source = "Other";
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            _source = "Shader Compiler";
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            _source = "Third Party";
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            _source = "Window System";
            break;
        default:
            _source = "Unknown";
    }
    switch (type) {
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            _type = "Depreciated Behavior";
            break;
        case GL_DEBUG_TYPE_ERROR:
            _type = "Error";
            break;
        case GL_DEBUG_TYPE_MARKER:
            _type = "Marker";
            break;
        case GL_DEBUG_TYPE_OTHER:
            _type = "Other";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            _type = "Performance";
            break;
        case GL_DEBUG_TYPE_POP_GROUP:
            _type = "Pop Group";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            _type = "Portability";
            break;
        case GL_DEBUG_TYPE_PUSH_GROUP:
            _type = "Push Group";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            _type = "Undefined Behavior";
            break;
        default:
            _type = "Unknown";
    }
    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH: {
        _severity = "High";
        // glfwSetWindowShouldClose((GLFWwindow *)userParam, GLFW_TRUE);
    } break;
    case GL_DEBUG_SEVERITY_MEDIUM: {
        _severity = "Medium";
        // glfwSetWindowShouldClose((GLFWwindow *)userParam, GLFW_TRUE);
    } break;
    case GL_DEBUG_SEVERITY_LOW: {
        _severity = "Low";
        // glfwSetWindowShouldClose((GLFWwindow *)userParam, GLFW_TRUE);
    } break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        _severity = "Notification";
        break;
    default:
        _severity = "Unknown";
        break;
    }

    if (severity != GL_DEBUG_SEVERITY_NOTIFICATION) {
        printf("Source: %s, Type: %s, ID: %u, Severity: %s, Message: %s\n", _source, _type, id, _severity, message);
    }
}
