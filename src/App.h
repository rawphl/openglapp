#pragma once

#include "framework/Shader.h"
#include "framework/Application.h"

namespace App {
    class App : public OpenGLApp::Application {
    public:
        OpenGLApp::Shader shader;
        GLuint vao;
        int sizeVertices;
        App(int width, int height) : OpenGLApp::Application(width, height), shader("screen") {

            glm::vec3 vertices[]{
                    glm::vec3(0.0f, 0.5f, 0.0f),
                    glm::vec3(0.5f, -0.5f, 0.0f),
                    glm::vec3(-0.5f, -0.5f, 0.0f)
            };

            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);
            GLuint triangleBuffer;
            glGenBuffers(1, &triangleBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, triangleBuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
            glEnableVertexAttribArray(0);
            glBindVertexArray(0);
            glEnable(GL_DEPTH_TEST);
            glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        };
        void run(float t, float dt) override;
    };
}
