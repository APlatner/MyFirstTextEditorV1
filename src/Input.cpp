#include "Input.hpp"

#include <unistd.h>

Button::Button(glm::uvec2 s, glm::uvec2 pos, glm::uvec2 mar, glm::uvec2 pad, glm::vec3 bg, glm::vec3 fg, Action a) : size{s}, position{pos}, margin{mar}, padding{pad}, background{bg}, foreground{fg}, action{a} {

}

Button::~Button() {

}

void Button::render(Shader &s, Renderer &r) {
    r.render(s, position, size, background);
    r.renderChar(s, text.c_str(), position, size, 2.0f, foreground, false, 1.0);
}

void TextArea::render(Shader &s, Renderer &r, bool cursor) {
    r.render(s, position, size, background);
    r.renderChar(s, text.c_str(), position, size, 1.0f, foreground, cursor, 1.618f);
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
    r.renderChar(s, text.c_str(), position, size, 1.0f, foreground, false, 1.618f);
}