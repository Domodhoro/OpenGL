#include <iostream>
#include <memory>
#include <stdexcept>

using std::make_unique;
using std::cerr;
using std::cin;
using std::exception;
using std::runtime_error;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using glm::mat4;
using glm::vec3;

#include "camera.hpp"
#include "dragon.hpp"

GLFWwindow* createWindow(const char*, const int, const int, const int, const int);

void framebufferSizeCallback(GLFWwindow*, int, int), keyboardCallback(GLFWwindow*);

int main() {
    try {
        if (glfwInit() == GLFW_NOT_INITIALIZED) {
            throw runtime_error("Falha ao iniciar o GLFW.");
        }

        const int screenWidth = 500, screenHeight = 300;
        GLFWwindow* window = createWindow("Dragon", screenWidth, screenHeight, 100, 100);

        glewExperimental = true;
        if (glewInit() != GLEW_OK) {
            throw runtime_error("Falha ao iniciar GLEW.");
        }

        float aspect = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);
        auto camera = make_unique<Camera>(60.0f, aspect, 0.1f, 10.0f);

        const vec3 cameraPosition = vec3(0.0f, 0.0f, -2.5f);
        camera->setPosition(cameraPosition);

        auto dragon = make_unique<Dragon>();

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);

        float lastFrame = 0.0f, currentFrame = 0.0f, FPS = 60.0f;
        while (!glfwWindowShouldClose(window)) {
            currentFrame = static_cast<float>(glfwGetTime());

            if ((currentFrame - lastFrame) > (1.0f / FPS)) {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

                mat4 projectionMatrix = camera->getProjectionMatrix();
                mat4 viewMatrix = camera->getViewMatrix();
                dragon->render(projectionMatrix, viewMatrix, cameraPosition);

                glfwSwapBuffers(window);
                glfwPollEvents();

                lastFrame = currentFrame;
            }
            keyboardCallback(window);
        }

        glfwTerminate();

        return 0;
    } catch (const exception& e) {
        glfwTerminate();

        cerr << e.what();
        cin.get();

        return 1;
    }
}

GLFWwindow* createWindow(const char* title, const int width, const int height, const int x, const int y) {
    GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window == nullptr) {
        throw runtime_error("Falha ao criar a janela de visualiza????o.");
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetWindowPos(window, x, y);

    return window;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void keyboardCallback(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) || glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
