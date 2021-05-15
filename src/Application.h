#pragma once

#include <GLFW/glfw3.h>

namespace OpenGLApp  {
    class Application {
        private:
            int width;
            int height;
            GLFWwindow* window;
        public:
            Application(int width, int height);
            ~Application();
            void run(void (*fn) (float t, float dt));
    };
}
