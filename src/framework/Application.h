#pragma once

#include <string>
#include <iostream>
#include <glad\glad.h>
#include <GLFW/glfw3.h>

namespace OpenGLApp  {
        class Application {
        private:
            int width;
            int height;
            GLFWwindow* window;
        public:
            Application();
            Application(int width, int height);
            ~Application();
            void loop();
            virtual void run(float t, float dt) = 0;
    };
}
