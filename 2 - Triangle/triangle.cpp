#include <stdexcept>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

using glm::radians;

#include "triangle.hpp"

Triangle::Triangle(const char* vertex, const char* fragment) : m_shader(make_unique<Shader>(vertex, fragment)) {
    m_vertexCoords.emplace_back(vec3(0.0f, 0.0f, 0.0f));
    m_vertexCoords.emplace_back(vec3(0.5f, 1.0f, 0.0f));
    m_vertexCoords.emplace_back(vec3(1.0f, 0.0f, 0.0f));

    m_colorCoords.emplace_back(vec3(1.0f, 0.0f, 0.0f));
    m_colorCoords.emplace_back(vec3(0.0f, 1.0f, 0.0f));
    m_colorCoords.emplace_back(vec3(0.0f, 0.0f, 1.0f));

    m_count = 3;

    setup();

    m_vertexCoords.clear();
    m_colorCoords.clear();
}

Triangle::~Triangle() {
    glDeleteVertexArrays(1, &m_VAO);
}

void Triangle::render(mat4& projectionMatrix) const {
    glUseProgram(m_shader->use());
    glBindVertexArray(m_VAO);

    mat4 modelMatrix = mat4(1.0f);
    modelMatrix = translate(modelMatrix, vec3(-0.5f, -0.5f, 0.0f));
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
    glBufferData(GL_ARRAY_BUFFER, m_vertexCoords.size() * sizeof(vec3), &m_vertexCoords.at(0), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vec3), (void*)(0 * sizeof(float)));

    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_colorCoords.size() * sizeof(vec3), &m_colorCoords.at(0), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(vec3), (void*)(0 * sizeof(float)));

    if (!m_VAO) {
        throw runtime_error("Falha ao criar VAO.");
    }
}
