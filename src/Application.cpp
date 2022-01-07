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


Application::Application() {
    initRenderer();
}

Application::~Application() {
    
}

void Application::initRenderer() {
    renderer.initFreetype("res/fonts/NotoSansMono-Regular-Nerd-Font-Complete.ttf");

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    shader.init("res/shaders/text_shader.vert", "res/shaders/text_shader.frag");
    shader.use();

    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}

void Application::Run() {
    while (!window.ShouldClose()) {
        renderer.DrawFrame();
        renderer.renderChar(shader, filesystem.textBuffer.ToString().c_str(), glm::vec2{10, 10}, glm::vec2{600, 600}, 1, glm::vec3{1.0f}, true, filesystem.textBuffer.GetCursorPos(), 1.618);
        window.SwapBuffers();
        glfwPollEvents();
    }
}
