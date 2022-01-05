#pragma once

#include <glm/glm.hpp>
#include <string>

class Shader {
    public:
    unsigned int ID;

    Shader();
    void init(const char *vertexPath, const char *fragmentPath);
    void use();
    void setBool(const char *name, bool value) const;
    void setInt(const char *name, int value) const;
    void setFloat(const char *name, float value) const;
};