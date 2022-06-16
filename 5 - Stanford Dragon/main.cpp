#include <iostream>
#include <memory>
#include <stdexcept>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "camera.hpp"
#include "dragon.hpp"

void keyboardCallback(GLFWwindow*);

int main() {
    GLFWwindow* window = nullptr;

    try {
        if (glfwInit() == GLFW_NOT_INITIALIZED) {
            throw std::runtime_error("Falha ao iniciar o GLFW.");
        }

        glfwWindowHint(GLFW_RESIZABLE, false);

        const int screenWidth = 500, screenHeight = 300;

        window = glfwCreateWindow(screenWidth, screenHeight, "Dragon", nullptr, nullptr);
        
        if (window == nullptr) {
            throw std::runtime_error("Falha ao criar a janela de visualização.");
        }

        glfwMakeContextCurrent(window);
        glfwSetWindowPos(window, 100, 100);

        glewExperimental = true;
        
        if (glewInit() != GLEW_OK) {
            throw std::runtime_error("Falha ao iniciar GLEW.");
        }

        float aspect = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);
        auto camera = std::make_unique<Camera>(60.0f, aspect, 0.1f, 10.0f);

        const glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, -2.5f);
        camera->setPosition(cameraPosition);

        auto dragon = std::make_unique<Dragon>();

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);

        const float FPS = 60.0f;
        float lastFrame = 0.0f, currentFrame = 0.0f;

        while (!glfwWindowShouldClose(window)) {
            currentFrame = static_cast<float>(glfwGetTime());

            if ((currentFrame - lastFrame) > (1.0f / FPS)) {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

                glm::mat4 projectionMatrix = camera->getProjectionMatrix();
                glm::mat4 viewMatrix = camera->getViewMatrix();

                dragon->render(projectionMatrix, viewMatrix, cameraPosition);

                glfwSwapBuffers(window);
                glfwPollEvents();

                lastFrame = currentFrame;

                keyboardCallback(window);
            }
        }

        glfwDestroyWindow(window);
        glfwTerminate();
        return 0;
    } catch (const std::exception& e) {
        glfwDestroyWindow(window);
        glfwTerminate();

        std::cerr << e.what();
        std::cin.get();
        return 1;
    }
}

void keyboardCallback(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}
