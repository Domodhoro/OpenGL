#include <iostream>
#include <memory>
#include <stdexcept>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "camera.hpp"
#include "box.hpp"

void keyboardCallback(GLFWwindow*);

unsigned int loadTexture(const char*);

int main() {
    GLFWwindow* window = nullptr;
    
    try {
        if (glfwInit() == GLFW_NOT_INITIALIZED) {
            throw std::runtime_error("Falha ao iniciar o GLFW.");
        }

        glfwWindowHint(GLFW_RESIZABLE, false);

        const int screenWidth = 500, screenHeight = 300;

        window = glfwCreateWindow(screenWidth, screenHeight, "Box", nullptr, nullptr);
        
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
        camera->setPosition(glm::vec3(0.0f, 0.0f, -2.0f));

        unsigned int boxTexture = loadTexture("boxTexture.png");
        auto box = std::make_unique<Box>(boxTexture);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);

        const float FPS = 60.0f;
        float lastFrame = 0.0f, currentFrame = 0.0f;

        while (!glfwWindowShouldClose(window)) {
            currentFrame = static_cast<float>(glfwGetTime());

            if ((currentFrame - lastFrame) > (1.0f / FPS)) {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glClearColor(0.5f, 0.5f, 1.0f, 1.0f);

                glm::mat4 projectionMatrix = camera->getProjectionMatrix();
                glm::mat4 viewMatrix = camera->getViewMatrix();

                box->render(projectionMatrix, viewMatrix);

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
        throw std::runtime_error("Falha ao abrir arquivo de textura.");
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(pixels);

    return texture;
}
