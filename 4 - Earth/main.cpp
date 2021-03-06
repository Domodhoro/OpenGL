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

using glm::vec3;
using glm::mat4;

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "camera.hpp"
#include "earth.hpp"

GLFWwindow* createWindow(const char*, const int, const int, const int, const int);

void framebufferSizeCallback(GLFWwindow*, int, int), keyboardCallback(GLFWwindow*);

unsigned int loadTexture(const char*);

int main() {
    try {
        if (glfwInit() == GLFW_NOT_INITIALIZED) {
            throw runtime_error("Falha ao iniciar o GLFW.");
        }

        const int screenWidth = 500, screenHeight = 300;
        GLFWwindow* window = createWindow("Earth", screenWidth, screenHeight, 100, 100);

        glewExperimental = true;
        if (glewInit() != GLEW_OK) {
            throw runtime_error("Falha ao iniciar GLEW.");
        }

        float aspect = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);
        auto camera = make_unique<Camera>(60.0f, aspect, 0.1f, 10.0f);
        camera->setPosition(vec3(0.0f, 0.0f, -2.5f));

        auto earth = make_unique<Earth>(loadTexture("earthTexture.png"));

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);

        float lastFrame = 0.0f, currentFrame = 0.0f, FPS = 60.0f;
        while (!glfwWindowShouldClose(window)) {
            currentFrame = static_cast<float>(glfwGetTime());

            if ((currentFrame - lastFrame) > (1.0f / FPS)) {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glClearColor(0.5f, 0.5f, 1.0f, 1.0f);

                mat4 projectionMatrix = camera->getProjectionMatrix();
                mat4 viewMatrix = camera->getViewMatrix();
                earth->render(projectionMatrix, viewMatrix);

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

unsigned int loadTexture(const char* texturePath) {
    unsigned int texture = 0u;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    int width = 0, height = 0, channels = 0;
    unsigned char* pixels = stbi_load(texturePath, &width, &height, &channels, 0);
    if (pixels == nullptr) {
        throw runtime_error("Falha ao abrir arquivo de textura.");
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(pixels);

    return texture;
}
