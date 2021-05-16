#pragma once

#include <glm/glm.hpp>
#include <string>
#include <glad\glad.h>
#include <GLFW\glfw3.h>

namespace OpenGLApp  {
    class Shader {
    private:
        GLuint id;
        static GLint compileShader(std::string const &src, GLint type);
    public:
        Shader();
        Shader(std::string name);
        void use();
        void unuse();
        void bind(unsigned int location, float value);
        void bind(unsigned int location, glm::vec2 const & vec);
        void bind(unsigned int location, glm::vec3 const & vec);
        void bind(unsigned int location, glm::mat3 const & matrix);
        void bind(unsigned int location, glm::mat4 const & matrix);
        template<typename T> Shader & bind(std::string const & name, T&& value)
        {
            int location = glGetUniformLocation(id, name.c_str());
            if (location == -1) fprintf(stderr, "Missing Uniform: %s\n", name.c_str());
            else bind(location, std::forward<T>(value));
            return *this;
        }


    };
}
