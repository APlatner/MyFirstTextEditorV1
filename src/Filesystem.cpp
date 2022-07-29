#include "Filesystem.hpp"

#include <GL/glew.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <unistd.h>

const int fontsize = 16;

Filesystem::Filesystem(InputManager &im) : inputManager{im} {
  u16 codes[] = {
      GLFW_KEY_0,       GLFW_KEY_1,         GLFW_KEY_2,     GLFW_KEY_3,
      GLFW_KEY_4,       GLFW_KEY_5,         GLFW_KEY_6,     GLFW_KEY_7,
      GLFW_KEY_8,       GLFW_KEY_9,         GLFW_KEY_A,     GLFW_KEY_B,
      GLFW_KEY_C,       GLFW_KEY_D,         GLFW_KEY_E,     GLFW_KEY_F,
      GLFW_KEY_G,       GLFW_KEY_H,         GLFW_KEY_I,     GLFW_KEY_J,
      GLFW_KEY_K,       GLFW_KEY_L,         GLFW_KEY_M,     GLFW_KEY_N,
      GLFW_KEY_O,       GLFW_KEY_P,         GLFW_KEY_Q,     GLFW_KEY_R,
      GLFW_KEY_S,       GLFW_KEY_T,         GLFW_KEY_U,     GLFW_KEY_V,
      GLFW_KEY_W,       GLFW_KEY_X,         GLFW_KEY_Y,     GLFW_KEY_Z,
      GLFW_KEY_SPACE,   GLFW_KEY_BACKSPACE, GLFW_KEY_ENTER, GLFW_KEY_PERIOD,
      GLFW_KEY_LEFT,    GLFW_KEY_RIGHT,     GLFW_KEY_HOME,  GLFW_KEY_END,
      GLFW_KEY_PAGE_UP, GLFW_KEY_PAGE_DOWN};
  for (u16 i = 0; i < 46; i++) {
    inputManager.RegisterEvent(codes[i], this, ControlEvent);
  }
  activeFileName = "";
}

Filesystem::~Filesystem() {
  u16 codes[] = {
      GLFW_KEY_0,       GLFW_KEY_1,         GLFW_KEY_2,     GLFW_KEY_3,
      GLFW_KEY_4,       GLFW_KEY_5,         GLFW_KEY_6,     GLFW_KEY_7,
      GLFW_KEY_8,       GLFW_KEY_9,         GLFW_KEY_A,     GLFW_KEY_B,
      GLFW_KEY_C,       GLFW_KEY_D,         GLFW_KEY_E,     GLFW_KEY_F,
      GLFW_KEY_G,       GLFW_KEY_H,         GLFW_KEY_I,     GLFW_KEY_J,
      GLFW_KEY_K,       GLFW_KEY_L,         GLFW_KEY_M,     GLFW_KEY_N,
      GLFW_KEY_O,       GLFW_KEY_P,         GLFW_KEY_Q,     GLFW_KEY_R,
      GLFW_KEY_S,       GLFW_KEY_T,         GLFW_KEY_U,     GLFW_KEY_V,
      GLFW_KEY_W,       GLFW_KEY_X,         GLFW_KEY_Y,     GLFW_KEY_Z,
      GLFW_KEY_SPACE,   GLFW_KEY_BACKSPACE, GLFW_KEY_ENTER, GLFW_KEY_PERIOD,
      GLFW_KEY_LEFT,    GLFW_KEY_RIGHT,     GLFW_KEY_HOME,  GLFW_KEY_END,
      GLFW_KEY_PAGE_UP, GLFW_KEY_PAGE_DOWN};
  for (u16 i = 0; i < 46; i++) {
    inputManager.UnRegisterEvent(codes[i], this, ControlEvent);
  }
  if (activeFileName != "") {
    Close();
  }
}

bool Filesystem::InitRenderer() {
  uint8_t *cursor = (unsigned char *)malloc(sizeof(char) * fontsize * 4);
  memset(cursor, 0xff, fontsize * 4);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glGenTextures(1, &cursorID);
  glBindTexture(GL_TEXTURE_2D, cursorID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, fontsize / 12, fontsize, 0, GL_RED,
               GL_UNSIGNED_BYTE, cursor);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glBindTexture(GL_TEXTURE_2D, 0);

  fontid.LoadFont("res/fonts/NotoSansMono-Regular-Nerd-Font-Complete.ttf", 16);

  s.init("res/shaders/text_shader.vert", "res/shaders/text_shader.frag");
  s.use();

  glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f);
  glUniformMatrix4fv(glGetUniformLocation(s.ID, "projection"), 1, GL_FALSE,
                     glm::value_ptr(projection));
  color = glm::vec3{1.0f, 1.0f, 1.0f};
  position = glm::uvec2{200, 10};
  size = glm::uvec2{600, 600};

  PrepBuffers();

  return true;
}

bool Filesystem::PrepBuffers() {
  std::string text;
  if (context == FILE_CONTEXT) {
    text = "SELECT A FILE TO OPEN\n" + activeFileName;
  } else if (context == TEXT_CONTEXT) {
    text = activeFileName + "\n\n" + textBuffer.ToString();
  } else {
    return true;
  }
  vbo.StoreData(nullptr, (text.length()) * 6 * 4 * sizeof(float));
  BufferLayout layout;
  vao.AddBuffer(vbo, layout);
  cursorVBO.StoreData(nullptr, 6 * 4 * sizeof(float));
  cursorVAO.AddBuffer(cursorVBO, layout);
  glUniform3f(glGetUniformLocation(s.ID, "textColor"), color.x, color.y,
              color.z);

  float x = position.x;
  float y = position.y;
  x += deltaX;
  y += deltaY;
  vbo.Bind();
  for (uint32_t i = 0; i < text.length(); i++) {
    Character c = fontid.GetChar(text[i]);
    if (text[i] == '\n') {
      x = position.x;
      y += fontid.GetChar('I').Size.y * fontScale * fontMargin;
    } else if (text[i] == '\t') {
      x += (fontid.GetChar('a').Advance >> 6) * fontScale * 4;
    } else if ((x < size.x + position.x) && (x >= position.x) &&
               (y < size.y + position.y)) {
      float xpos = x + c.Bearing.x * fontScale;
      float ypos = y + (fontsize - c.Bearing.y) * fontScale;

      float w = c.Size.x * fontScale;
      float h = c.Size.y * fontScale;

      if (y >= position.y) {
        float vertices[6][4]{{xpos, ypos + h, c.Start.x, c.End.y},
                             {xpos + w, ypos, c.End.x, c.Start.y},
                             {xpos, ypos, c.Start.x, c.Start.y},

                             {xpos, ypos + h, c.Start.x, c.End.y},
                             {xpos + w, ypos + h, c.End.x, c.End.y},
                             {xpos + w, ypos, c.End.x, c.Start.y}};

        glBufferSubData(GL_ARRAY_BUFFER, i * 24 * sizeof(float),
                        sizeof(vertices), vertices);
      } else {
        float vertices[6][4]{
            {xpos, ypos + h, 0.0f, 0.0f}, {xpos + w, ypos, 0.0f, 0.0f},
            {xpos, ypos, 0.0f, 0.0f},

            {xpos, ypos + h, 0.0f, 0.0f}, {xpos + w, ypos + h, 0.0f, 0.0f},
            {xpos + w, ypos, 0.0f, 0.0f}};

        glBufferSubData(GL_ARRAY_BUFFER, i * 24 * sizeof(float),
                        sizeof(vertices), vertices);
      }

      x += (c.Advance >> 6) * fontScale;
    }
    if (i == textBuffer.GetCursorPos() - 1 + activeFileName.length() + 2) {
      float xpos = x;
      float ypos = y;

      float w = fontsize / 12 * fontScale;
      float h = fontsize * fontScale;
      float vertices[6][4]{
          {xpos, ypos + h, 0.0f, 1.0f}, {xpos + w, ypos, 1.0f, 0.0f},
          {xpos, ypos, 0.0f, 0.0f},

          {xpos, ypos + h, 0.0f, 1.0f}, {xpos + w, ypos + h, 1.0f, 1.0f},
          {xpos + w, ypos, 1.0f, 0.0f}};
      cursorVBO.Bind();
      glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
      vbo.Bind();
    }
    if (text.length() == 0) {
      float xpos = x;
      float ypos = y;

      float w = fontsize / 12 * fontScale;
      float h = fontsize * fontScale;

      float vertices[6][4]{
          {xpos, ypos + h, 0.0f, 1.0f}, {xpos + w, ypos, 1.0f, 0.0f},
          {xpos, ypos, 0.0f, 0.0f},

          {xpos, ypos + h, 0.0f, 1.0f}, {xpos + w, ypos + h, 1.0f, 1.0f},
          {xpos + w, ypos, 1.0f, 0.0f}};
      cursorVBO.Bind();
      glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    }
  }

  return true;
}

void Filesystem::PrepCursor() {}

void Filesystem::Render(bool showCursor) {
  std::string text;
  glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f);
  glUniformMatrix4fv(glGetUniformLocation(s.ID, "projection"), 1, GL_FALSE,
                     glm::value_ptr(projection));
  if (context == FILE_CONTEXT) {
    text = "SELECT A FILE TO OPEN\n" + activeFileName;
    showCursor = false;
  } else if (context == TEXT_CONTEXT) {
    text = activeFileName + "\n\n" + textBuffer.ToString();
  }
  Renderer::render(s, vao, vbo, ibo, (text.length()) * 6, fontid.fontID);
  if (showCursor) {
    Renderer::render(s, cursorVAO, cursorVBO, ibo, 6, cursorID);
  }
}

void Filesystem::Open() {
  activeFile = fopen(activeFileName.c_str(), "r");
  std::string text = "";
  char buffer[256];
  while (!feof(activeFile)) {
    buffer[0] = '\0';
    fgets(buffer, 256, activeFile);
    text += buffer;
  }
  textBuffer.LoadText(text.c_str());
  PrepBuffers();
}

void Filesystem::Close() {
  activeFileName = "";
  fclose(activeFile);
  textBuffer.ClearText();
}

void Filesystem::SaveFile() {
  freopen(NULL, "w", activeFile);
  fprintf(activeFile, "%s", textBuffer.ToString().c_str());
  printf("SAVED\n");
}

bool Filesystem::ControlEvent(u16 code, void *sender, void *listener,
                              EventData data) {
  Filesystem *filesystem = (Filesystem *)listener;
  if (code == GLFW_KEY_O && data.action == GLFW_PRESS &&
      data.mods & GLFW_MOD_CONTROL) {
    filesystem->context = FILE_CONTEXT;
  } else if (code == GLFW_KEY_S && data.action == GLFW_PRESS &&
             data.mods & GLFW_MOD_CONTROL) {
    filesystem->SaveFile();
  } else if (code == GLFW_KEY_Q && data.action == GLFW_PRESS &&
             data.mods & GLFW_MOD_CONTROL) {
    filesystem->Close();
    filesystem->context = NULL_CONTEXT;
  } else if (filesystem->context == FILE_CONTEXT &&
             data.action != GLFW_RELEASE) {
    filesystem->FileContext(code, data);
  } else if (filesystem->context == TEXT_CONTEXT &&
             data.action != GLFW_RELEASE) {
    filesystem->TextContext(code, data);
  }
  filesystem->PrepBuffers();

  return true;
}

void Filesystem::FileContext(u16 code, EventData data) {
  switch (code) {
  case GLFW_KEY_BACKSPACE:
    activeFileName.pop_back();
    break;
  case GLFW_KEY_ENTER: {
    context = TEXT_CONTEXT;
    Open();
  } break;
  case GLFW_KEY_PERIOD: {
    activeFileName += '.';
  } break;
  default: {
    activeFileName += (char)(code + 32 * !(data.mods & (GLFW_MOD_SHIFT ^
                                                        GLFW_MOD_CAPS_LOCK)));
  }
  }
  PrepBuffers();
}

void Filesystem::TextContext(u16 code, EventData data) {
  switch (code) {
  case GLFW_KEY_HOME:
    textBuffer.LineRetreat();
    break;
  case GLFW_KEY_END:
    textBuffer.LineAdvance();
    break;
  case GLFW_KEY_PAGE_UP:
    deltaY -= 16;
    break;
  case GLFW_KEY_PAGE_DOWN:
    deltaY += 16;
    break;
  case GLFW_KEY_BACKSPACE:
    textBuffer.Delete();
    break;
  case GLFW_KEY_ENTER:
    textBuffer.Append('\n');
    break;
  case GLFW_KEY_LEFT:
    textBuffer.Retreat();
    break;
  case GLFW_KEY_RIGHT:
    textBuffer.Advance();
    break;
  case GLFW_KEY_SPACE:
    textBuffer.Append(' ');
    break;
  case GLFW_KEY_PERIOD:
    textBuffer.Append('.');
    break;
  case GLFW_KEY_0:
    textBuffer.Append((char)(code + 32 * !(data.mods & (GLFW_MOD_SHIFT ^
                                                        GLFW_MOD_CAPS_LOCK))));
    break;
  case GLFW_KEY_1:
  case GLFW_KEY_2:
  case GLFW_KEY_3:
  case GLFW_KEY_4:
  case GLFW_KEY_5:
  case GLFW_KEY_6:
  case GLFW_KEY_7:
  case GLFW_KEY_8:
  case GLFW_KEY_9:
    textBuffer.Append((char)(code + 32 * !(data.mods & (GLFW_MOD_SHIFT ^
                                                        GLFW_MOD_CAPS_LOCK))));
    break;
  default: {
    textBuffer.Append((char)(code + 32 * !(data.mods & (GLFW_MOD_SHIFT ^
                                                        GLFW_MOD_CAPS_LOCK))));
  }
  }
  PrepBuffers();
}