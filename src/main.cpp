#include <glm/glm.hpp>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "Shader.h"
#include "Application.h"

int sizeVertices;
GLuint shader_programme;
GLuint vao;

const char *vertex_shader =
        "#version 400\n"
        "in vec3 vp;"
        "void main() {"
        "  gl_Position = vec4(vp, 1.0);"
        "}";
const char *fragment_shader =
        "#version 400\n"
        "out vec4 frag_colour;"
        "void main() {"
        "  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
        "}";

int main() {
    OpenGLApp::Application app(1024, 768);
    OpenGLApp::Shader Shader("screen");

    glm::vec3 vertices[]{
            glm::vec3(0.0f, 0.5f, 0.0f),
            glm::vec3(0.5f, -0.5f, 0.0f),
            glm::vec3(-0.5f, -0.5f, 0.0f)
    };
    sizeVertices = sizeof(vertices) / sizeof(glm::vec3);
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    GLuint triangleBuffer;
    glGenBuffers(1, &triangleBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, triangleBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);



    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);

    shader_programme = glCreateProgram();
    glAttachShader(shader_programme, fs);
    glAttachShader(shader_programme, vs);
    glLinkProgram(shader_programme);

    glEnable(GL_DEPTH_TEST);
    app.run([](float t, float dt) {
        glClearColor(glm::cos(t), glm::sin(t), 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader_programme);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    });
    return 0;
}
