#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <fstream>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Assets.h"

namespace OpenGLApp {
    GLint Shader::compileShader(std::string const &src, GLint type) {
        GLint status, length;
        auto shaderId = glCreateShader(type);
        const char* c_str = src.c_str();
        glShaderSource(shaderId, 1, &c_str, nullptr);
        glCompileShader(shaderId);
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);

        if (status == false) {
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
            std::unique_ptr<char[]> buffer(new char[length]);
            glGetShaderInfoLog(shaderId, length, nullptr, buffer.get());
            fprintf(stderr, "SHADER COMPILE ERROR: %s\n%s", src.c_str(), buffer.get());
        }
        return shaderId;
    }

    Shader::Shader(std::string name) {
        id = glCreateProgram();
        auto paths = OpenGLApp::Assets::shaderNameToFilePaths(name);
        auto vsSource = OpenGLApp::Assets::readFile(std::get<0>(paths));
        auto fsSource = OpenGLApp::Assets::readFile(std::get<1>(paths));
        auto vertexShaderId = compileShader(vsSource, GL_VERTEX_SHADER);
        auto fragmentShaderId = compileShader(fsSource, GL_FRAGMENT_SHADER);
        glAttachShader(id, vertexShaderId);
        glDeleteShader(vertexShaderId);
        glAttachShader(id, fragmentShaderId);
        glDeleteShader(fragmentShaderId);
        glLinkProgram(id);

        GLint status, length;
        glGetProgramiv(id, GL_LINK_STATUS, &status);

        if (status == false) {
            glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
            std::unique_ptr<char[]> buffer(new char[length]);
            glGetProgramInfoLog(id, length, nullptr, buffer.get());
            fprintf(stderr, "PROGRAM LINK ERROR: %s", buffer.get());
        }
    }

    void Shader::use() {
        glUseProgram(id);
    }

    void Shader::unuse() {
        glUseProgram(0);
    }

    void Shader::bind(unsigned int location, float value) {
        glUniform1f(location, value);
    }

    void Shader::bind(unsigned int location, glm::vec2 const &vec) {
        glUniform2fv(location, 1, glm::value_ptr(vec));
    }

    void Shader::bind(unsigned int location, glm::vec3 const &vec) {
        glUniform3fv(location, 1, glm::value_ptr(vec));
    }

    void Shader::bind(unsigned int location, glm::mat3 const &matrix) {
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Shader::bind(unsigned int location, glm::mat4 const &matrix) {
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }
}