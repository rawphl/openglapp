#include <iostream>
#include <functional>

#include "Application.h"

namespace OpenGLApp {
    Application::Application() {
        width = 1024;
        height = 768;
    }

    Application::Application(int _width, int _height) {
        width = _width;
        height = _height;

        glfwSetErrorCallback([](int errorCode, const char *description) {
            perror(description);
        });

        if (!glfwInit()) {
            perror("glfwInit() failed");
            exit(-1);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, "Hello Modern GL!", nullptr, nullptr);

        if (!window) {
            perror("glfwCreateWindow() failed");
            glfwTerminate();
            exit(-1);
        }


        GLFWmonitor *monitor = glfwGetPrimaryMonitor();

        if (!monitor) {
            perror("glfwGetPrimaryMonitor() failed");
            glfwTerminate();
            exit(-1);
        }

        const GLFWvidmode *mode = glfwGetVideoMode(monitor);

        if (!mode) {
            perror("glfwGetVideoMode() failed");
            glfwTerminate();
            exit(-1);
        }

        int monitorX, monitorY;
        glfwGetMonitorPos(monitor, &monitorX, &monitorY);

        int windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);
        glfwSetWindowPos(window, monitorX + (mode->width - windowWidth) / 2,
                         monitorY + (mode->height - windowHeight) / 2);

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
            exit(-1);
        }

        glfwSwapInterval(1);
        glViewport(0, 0, width, height);
    }

    Application::~Application() {
        std::cout << "Application::~Application(()" << std::endl;
        glfwDestroyWindow(window);
    }

    void Application::loop() {
        std::cout << "Application::run()" << std::endl;
        float lastTime = static_cast<float>(glfwGetTime());
        float t = 0;
        float dt = 0.0f;

        while (!glfwWindowShouldClose(window)) {
            t = static_cast<float>(glfwGetTime());
            dt = t - lastTime;
            lastTime = t;
            run(t, dt);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        std::cout << "Application::teminate()" << std::endl;
        glfwTerminate();
    }
}

