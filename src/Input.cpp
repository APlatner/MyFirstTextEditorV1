#include "Input.hpp"

#include <unistd.h>

TextArea::TextArea() {
    
}

void TextArea::render(Shader &s, Renderer &r, bool cursor) {
    r.render(s, position, size, background);
    r.renderChar(s, textBuffer->ToString(), position, size, 1.0f, foreground, cursor, textBuffer->GetCursorPos() - 1, 1.618f);
}

FileDisplay::FileDisplay(glm::uvec2 pos, glm::uvec2 s, glm::uvec2 mar, glm::uvec2 pad, glm::vec3 bg, glm::vec3 fg) : position{pos}, size{s}, margin{mar}, padding{pad}, background{bg}, foreground{fg} {
    text = std::string(get_current_dir_name());
    size_t bound = text.find_last_of("/\\");
    text = text.substr(bound + 1);
}

FileDisplay::~FileDisplay() {

}

void FileDisplay::render(Shader &s, Renderer &r) {
    r.render(s, position, size, background);
    r.renderChar(s, text.c_str(), position, size, 1.0f, foreground, false, 0, 1.618f);
}

Input::Input() {
}

void Input::ParseText(int key, int action, int mods) {
    if (action != GLFW_RELEASE) {
        bool caps = (mods & GLFW_MOD_SHIFT) ^ (mods & GLFW_MOD_CAPS_LOCK);
        switch (key) {
            case GLFW_KEY_ENTER: {
                textArea.textBuffer->Append('\n');
            } break;
            case GLFW_KEY_TAB: {
                textArea.textBuffer->Append('\t');
            } break;
            case GLFW_KEY_BACKSPACE: {
                textArea.textBuffer->Delete();
            } break;
            case GLFW_KEY_LEFT_SHIFT: 
            case GLFW_KEY_LEFT_CONTROL:
            case GLFW_KEY_RIGHT_SHIFT: 
            case GLFW_KEY_RIGHT_CONTROL: 
            case GLFW_KEY_LEFT_ALT:
            case GLFW_KEY_RIGHT_ALT: break;
            case GLFW_KEY_UP: {
                textArea.textBuffer->Descend();
            } break;
            case GLFW_KEY_DOWN: {
                textArea.textBuffer->Ascend();
            } break;
            case GLFW_KEY_LEFT: {
                textArea.textBuffer->Retreat();
            } break;
            case GLFW_KEY_RIGHT: {
                textArea.textBuffer->Advance();
            } break;
            case GLFW_KEY_HOME: {
                textArea.textBuffer->LineRetreat();
            } break;
            case GLFW_KEY_END: {
                textArea.textBuffer->LineAdvance();
            } break;
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
                textArea.textBuffer->Append((char)(key + 32 * !caps));
            } break;
            case GLFW_KEY_0:
                textArea.textBuffer->Append((char)(key - 7 * (mods & GLFW_MOD_SHIFT)));
                break;
            case GLFW_KEY_1:
                textArea.textBuffer->Append((char)(key - 16 * (mods & GLFW_MOD_SHIFT)));
                break;
            case GLFW_KEY_2:
                textArea.textBuffer->Append((char)(key + 14 * (mods & GLFW_MOD_SHIFT)));
                break;
            case GLFW_KEY_3:
                textArea.textBuffer->Append((char)(key - 16 * (mods & GLFW_MOD_SHIFT)));
                break;
            case GLFW_KEY_4:
            case GLFW_KEY_5:
            case GLFW_KEY_6:
            case GLFW_KEY_7:
            case GLFW_KEY_8:
            case GLFW_KEY_9: {
                textArea.textBuffer->Append((char)(key));
            } break;
            default: {
                textArea.textBuffer->Append((char)key);
            }
        }
    }
}

void Input::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    Input *input = (Input*)glfwGetWindowUserPointer(window);
    switch (key) {
        case GLFW_KEY_ESCAPE: {
            glfwSetWindowShouldClose(window, true);
            return;
        } break;
        case GLFW_KEY_LEFT_CONTROL: {

        } break;
    }
    input->ParseText(key, action, mods);
}

void Input::MouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    
}