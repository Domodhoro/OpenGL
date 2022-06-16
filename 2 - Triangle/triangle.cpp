#include <stdexcept>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include "triangle.hpp"

Triangle::Triangle(const char* vertex, const char* fragment) : m_shader(std::make_unique<Shader>(vertex, fragment)) {
    mesh();
    setup();

    m_vertexCoords.clear();
    m_colorCoords.clear();
}

Triangle::~Triangle() {
    glDeleteVertexArrays(1, &m_VAO);
}

void Triangle::render(glm::mat4& projectionMatrix) const {
    glUseProgram(m_shader->use());
    glBindVertexArray(m_VAO);

    glm::mat4 modelMatrix = glm::mat4(1.0f);

    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5f, -0.5f, 0.0f));

    m_shader->setUniformMatrix("model", modelMatrix);
    m_shader->setUniformMatrix("projection", projectionMatrix);

    glDrawArrays(GL_TRIANGLES, 0, m_count);
}

void Triangle::setup() {
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    unsigned int vertexBuffer = 0u, colorBuffer = 0u;

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_vertexCoords.size() * sizeof(glm::vec3), &m_vertexCoords.at(0), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(glm::vec3), (void*)(0 * sizeof(float)));

    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_colorCoords.size() * sizeof(glm::vec3), &m_colorCoords.at(0), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(glm::vec3), (void*)(0 * sizeof(float)));

    if (!m_VAO) {
        throw std::runtime_error("Falha ao criar VAO.");
    }
}

void Triangle::mesh() {
    m_vertexCoords.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f));
    m_vertexCoords.emplace_back(glm::vec3(0.5f, 1.0f, 0.0f));
    m_vertexCoords.emplace_back(glm::vec3(1.0f, 0.0f, 0.0f));

    m_colorCoords.emplace_back(glm::vec3(1.0f, 0.0f, 0.0f));
    m_colorCoords.emplace_back(glm::vec3(0.0f, 1.0f, 0.0f));
    m_colorCoords.emplace_back(glm::vec3(0.0f, 0.0f, 1.0f));

    m_count = 3;
}
