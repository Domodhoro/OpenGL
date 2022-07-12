#include <iostream>
#include <memory>
#include <stdexcept>

using std::make_unique;
using std::cerr;
using std::cin;
using std::runtime_error;
using std::exception;

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using glm::mat4;
using glm::ortho;

#include "triangle.hpp"

const char* vertexSource =
"#version 300 es\n"
"layout(location = 0) in vec3 vertexCoords;\n"
"layout(location = 1) in vec3 colorCoords;\n"
"uniform mat4 model, projection;\n"
"out highp vec3 Color;\n"
"void main() {\n"
"   gl_Position = projection * model * vec4(vertexCoords, 1.0f);\n"
"   Color = colorCoords;\n"
"}\0";

const char* fragmentSource =
"#version 300 es\n"
"out highp vec4 FragColor;\n"
"in highp vec3 Color;\n"
"void main() {\n"
"   FragColor = vec4(Color, 1.0f);\n"
"}\0";

GLFWwindow* createWindow(const char*, const int, const int, const int, const int);

void framebufferSizeCallback(GLFWwindow*, int, int), keyboardCallback(GLFWwindow*);

int main() {
    try {
        if (glfwInit() == GLFW_NOT_INITIALIZED) {
            throw runtime_error("Falha ao iniciar o GLFW.");
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, false);

        const int screenWidth = 500, screenHeight = 300;
        GLFWwindow* window = createWindow("Window", screenWidth, screenHeight, 100, 100);

        glewExperimental = true;
        if (glewInit() != GLEW_OK) {
            throw runtime_error("Falha ao iniciar GLEW.");
        }

        auto triangle = make_unique<Triangle>(vertexSource, fragmentSource);

        glEnable(GL_DEPTH_TEST);

        float lastFrame = 0.0f, currentFrame = 0.0f, FPS = 60.0f, aspect = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);
        while (!glfwWindowShouldClose(window)) {
            currentFrame = static_cast<float>(glfwGetTime());

            if ((currentFrame - lastFrame) > (1.0f / FPS)) {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glClearColor(0.5f, 0.5f, 1.0f, 1.0f);

                mat4 projectionMatrix = ortho(-1.0f * aspect, 1.0f * aspect, -1.0f, 1.0f, -1.0f, 1.0f);
                triangle->render(projectionMatrix);

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
        throw runtime_error("Falha ao criar a janela de visualização.");
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
