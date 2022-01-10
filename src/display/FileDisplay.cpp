#include "FileDisplay.hpp"

#include <unistd.h>
#include <dirent.h>
#include <cstring>

FileDisplay::FileDisplay() :  Display() {
	position = glm::uvec2{0};
	size = glm::uvec2{200, 600};
}

FileDisplay::~FileDisplay() {
	
}

void FileDisplay::Init() {
	font.LoadFont("res/fonts/NotoSansMono-Regular-Nerd-Font-Complete.ttf", fontSize);

    shader.init("res/shaders/text_shader.vert", "res/shaders/text_shader.frag");
    shader.use();
	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	text = get_current_dir_name();
	text = text.substr(text.find_last_of("\\/") + 1);

	struct dirent *de;
	DIR *dr = opendir(".");

	if (dr == NULL) {
		printf("Could not open current directory\n");
		return;
	}

	while ((de = readdir(dr)) != NULL) {
		if (strcmp(de->d_name, "..") == 0 || strcmp(de->d_name, ".") == 0) {
			continue;
		}
		text += "\n\t";
		text += de->d_name;
	}
	closedir(dr);
}

void FileDisplay::Update() {
	vbo.StoreData(nullptr, (text.length()) * 6 * 4 * sizeof(float));
    BufferLayout layout;
    vao.AddBuffer(vbo, layout);
    glUniform3f(glGetUniformLocation(shader.ID, "textColor"), foreground.x, foreground.y, foreground.z);

    float x = position.x;
    float y = position.y;
    vbo.Bind();
    for (uint32_t i = 0; i < text.length(); i++) {
        Character c = font.GetChar(text[i]);
        if (text[i] == '\n') {
            x = position.x;
            y += font.GetChar('I').Size.y * fontScale * fontMargin;
        } else if (text[i] == '\t') {
            x += (font.GetChar('a').Advance >> 6) * fontScale * 4;
        } else if ((x < size.x + position.x ) && (x >= position.x) && (y < size.y + position.y)) {
            float xpos = x + c.Bearing.x * fontScale;
            float ypos = y + (fontSize  - c.Bearing.y) * fontScale;

            float w = c.Size.x * fontScale;
            float h = c.Size.y * fontScale;

            if (y >= position.y) {
                float vertices[6][4] {
                    {xpos, ypos + h, c.Start.x, c.End.y},
                    {xpos + w, ypos, c.End.x, c.Start.y},
                    {xpos, ypos, c.Start.x, c.Start.y},

                    {xpos, ypos + h, c.Start.x, c.End.y},
                    {xpos + w, ypos + h, c.End.x, c.End.y},
                    {xpos + w, ypos, c.End.x, c.Start.y}
                };
                
                glBufferSubData(GL_ARRAY_BUFFER, i * 24 * sizeof(float), sizeof(vertices), vertices);
            } else {
                float vertices[6][4] {
                    {xpos, ypos + h, 0.0f, 0.0f},
                    {xpos + w, ypos, 0.0f, 0.0f},
                    {xpos, ypos, 0.0f, 0.0f},

                    {xpos, ypos + h, 0.0f, 0.0f},
                    {xpos + w, ypos + h, 0.0f, 0.0f},
                    {xpos + w, ypos, 0.0f, 0.0f}
                };
                
                glBufferSubData(GL_ARRAY_BUFFER, i * 24 * sizeof(float), sizeof(vertices), vertices);
            }
            
            
            x += (c.Advance >> 6) * fontScale;
        }
    }
}

void FileDisplay::Render() {
	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	Renderer::render(shader, vao, vbo, ibo, (text.length()) * 6, font.fontID);
}