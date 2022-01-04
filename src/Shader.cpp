#include "Shader.hpp"

#include <GL/glew.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>

char** readFile(const char *filename) {
    char **fileString = (char**)malloc(sizeof(char*));
    unsigned char bufferSize = 128;
    FILE *file = fopen(filename, "r");
    if (file != NULL) {
        fseek(file, 0, SEEK_END);
        unsigned long len = ftell(file);
        fseek(file, 0, SEEK_SET);

        char *buffer = (char*)malloc(sizeof(char) * bufferSize);
        *fileString = (char*)malloc(sizeof(char) * (len + 1));
        if (len > 0) {
            fgets(buffer, bufferSize, file);
            strcpy(*fileString, buffer);
        }
        while (!feof(file)) {
            fgets(buffer, bufferSize, file);
            strcat(*fileString, buffer);
        }

        free(buffer);
        buffer = NULL;
        fclose(file);
    }
    return fileString;
}

Shader::Shader() {}

void Shader::init(const char *vertexPath, const char *fragmentPath) {
    char **vertexCode = readFile(vertexPath);
    char **fragmentCode = readFile(fragmentPath);
    
    GLuint vertexShader, fragmentShader;
    int success;
    char infoLog[512];

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, vertexCode, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED:%s\n", infoLog);
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, fragmentCode, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED:%s\n", infoLog);
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED:%s\n", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() {
    glUseProgram(ID);
}

void Shader::setBool(const char *name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name), (int)value);
}

void Shader::setInt(const char *name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name), value);
}

void Shader::setFloat(const char *name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name), value);
}
