#include <iostream>
#include <memory>
#include <stdexcept>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "triangle.hpp"

const char* vertexSource =
"#version 300 es\n"
"layout(location = 0) in vec3 vertexCoords;\n"
"layout(location = 1) in vec3 colorCoords;\n"
"uniform mat4 model, projection;\n"
"out highp vec3 Color;\n"
"void main()\n"
"{\n"
"   gl_Position = projection * model * vec4(vertexCoords, 1.0f);\n"
"   Color = colorCoords;\n"
"}\0";

const char* fragmentSource =
"#version 300 es\n"
"out highp vec4 FragColor;\n"
"in highp vec3 Color;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(Color, 1.0f);\n"
"}\0";

void keyboardCallback(GLFWwindow*);

int main() {
    GLFWwindow* window = nullptr;
    
    try {
        if (glfwInit() == GLFW_NOT_INITIALIZED) {
            throw std::runtime_error("Falha ao iniciar o GLFW.");
        }

        glfwWindowHint(GLFW_RESIZABLE, false);

        const int screenWidth = 500, screenHeight = 300;

        window = glfwCreateWindow(screenWidth, screenHeight, "Triangle", nullptr, nullptr);
        if (window ==  nullptr) {
            throw std::runtime_error("Falha ao criar a janela de visualização.");
        }

        glfwMakeContextCurrent(window);
        glfwSetWindowPos(window, 100, 100);

        glewExperimental = true;
        if (glewInit() != GLEW_OK) {
            throw std::runtime_error("Falha ao iniciar GLEW.");
        }

        auto triangle = std::make_unique<Triangle>(vertexSource, fragmentSource);

        const float aspect = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);

        glEnable(GL_DEPTH_TEST);

        const float FPS = 60.0f;
        float lastFrame = 0.0f, currentFrame = 0.0f;

        while (!glfwWindowShouldClose(window)) {
            currentFrame = static_cast<float>(glfwGetTime());

            if ((currentFrame - lastFrame) > (1.0f / FPS)) {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

                glm::mat4 projectionMatrix = glm::ortho(-1.0f * aspect, 1.0f * aspect, -1.0f, 1.0f, -1.0f, 1.0f);

                triangle->render(projectionMatrix);

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
