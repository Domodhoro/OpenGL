#include <iostream>
#include <stdexcept>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void keyboardCallback(GLFWwindow*);

int main()
{
    try
    {
        if(glfwInit() == GLFW_NOT_INITIALIZED)
        {
            throw std::runtime_error("Falha ao iniciar o GLFW.");
        }

        glfwWindowHint(GLFW_RESIZABLE, false);

        GLFWwindow* window = glfwCreateWindow(500, 300, "Window", nullptr, nullptr);
        if(window == nullptr)
        {
            throw std::runtime_error("Falha ao criar a janela de visualização.");
        }

        glfwMakeContextCurrent(window);
        glfwSetWindowPos(window, 100, 100);

        glewExperimental = true;
        if(glewInit() != GLEW_OK)
        {
            throw std::runtime_error("Falha ao iniciar GLEW.");
        }

        const float FPS = 60.0f;
        float lastFrame = 0.0f, currentFrame = 0.0f;

        while(!glfwWindowShouldClose(window))
        {
            currentFrame = static_cast<float>(glfwGetTime());

            if((currentFrame - lastFrame) > (1.0f / FPS))
            {
                glClear(GL_COLOR_BUFFER_BIT);
                glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
                glfwSwapBuffers(window);
                glfwPollEvents();

                lastFrame = currentFrame;

                keyboardCallback(window);
            }
        }

        glfwTerminate();
        return 0;
    }
    catch(const std::exception& e)
    {
        glfwTerminate();

        std::cerr << e.what();
        std::cin.get();
        return 1;
    }
}

void keyboardCallback(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}
