#include <vector>
#include <stdexcept>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "box.hpp"

Box::Box(const unsigned int& texture) : m_shader(std::make_unique<Shader>("boxVertex.glsl", "boxFragment.glsl")), m_texture(texture) {
    mesh.setup();

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    unsigned int vertexBuffer = 0u, textureBuffer = 0u;

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, mesh.m_vertexCoords.size() * sizeof(glm::vec3), &mesh.m_vertexCoords.at(0), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(glm::vec3), (void*)(0 * sizeof(float)));

    mesh.m_vertexCoords.clear();

    glGenBuffers(1, &textureBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
    glBufferData(GL_ARRAY_BUFFER, mesh.m_textureCoords.size() * sizeof(glm::vec2), &mesh.m_textureCoords.at(0), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(glm::vec2), (void*)(0 * sizeof(float)));

    mesh.m_textureCoords.clear();

    if (!m_VAO) {
        throw std::runtime_error("Falha ao criar VAO.");
    }
}

Box::~Box() {
    glDeleteProgram(m_shader->use());
    glDeleteVertexArrays(1, &m_VAO);
}

void Box::render(glm::mat4& projectionMatrix, glm::mat4& viewMatrix) const {
    glCullFace(GL_FRONT);

    glUseProgram(m_shader->use());
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glBindVertexArray(m_VAO);

    glm::mat4 modelMatrix = glm::mat4(1.0f);

    modelMatrix = glm::rotate(modelMatrix, glm::radians(static_cast<float>(45.0f * glfwGetTime())), glm::vec3(1.0f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5f));

    m_shader->setUniformMatrix("model", modelMatrix);
    m_shader->setUniformMatrix("view", viewMatrix);
    m_shader->setUniformMatrix("projection", projectionMatrix);

    glDrawArrays(GL_TRIANGLES, 0, mesh.m_count);
    glBindVertexArray(0);
}

void Box::Mesh::setup() {
    m_vertexCoords.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f));
    m_vertexCoords.emplace_back(glm::vec3(1.0f, 0.0f, 0.0f));
    m_vertexCoords.emplace_back(glm::vec3(1.0f, 1.0f, 0.0f));
    m_vertexCoords.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f));
    m_vertexCoords.emplace_back(glm::vec3(1.0f, 1.0f, 0.0f));
    m_vertexCoords.emplace_back(glm::vec3(0.0f, 1.0f, 0.0f));

    m_vertexCoords.emplace_back(glm::vec3(0.0f, 0.0f, 1.0f));
    m_vertexCoords.emplace_back(glm::vec3(1.0f, 1.0f, 1.0f));
    m_vertexCoords.emplace_back(glm::vec3(1.0f, 0.0f, 1.0f));
    m_vertexCoords.emplace_back(glm::vec3(0.0f, 1.0f, 1.0f));
    m_vertexCoords.emplace_back(glm::vec3(1.0f, 1.0f, 1.0f));
    m_vertexCoords.emplace_back(glm::vec3(0.0f, 0.0f, 1.0f));

    m_vertexCoords.emplace_back(glm::vec3(1.0f, 0.0f, 0.0f));
    m_vertexCoords.emplace_back(glm::vec3(1.0f, 0.0f, 1.0f));
    m_vertexCoords.emplace_back(glm::vec3(1.0f, 1.0f, 1.0f));
    m_vertexCoords.emplace_back(glm::vec3(1.0f, 0.0f, 0.0f));
    m_vertexCoords.emplace_back(glm::vec3(1.0f, 1.0f, 1.0f));
    m_vertexCoords.emplace_back(glm::vec3(1.0f, 1.0f, 0.0f));

    m_vertexCoords.emplace_back(glm::vec3(0.0f, 0.0f, 1.0f));
    m_vertexCoords.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f));
    m_vertexCoords.emplace_back(glm::vec3(0.0f, 1.0f, 1.0f));
    m_vertexCoords.emplace_back(glm::vec3(0.0f, 1.0f, 0.0f));
    m_vertexCoords.emplace_back(glm::vec3(0.0f, 1.0f, 1.0f));
    m_vertexCoords.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f));

    m_vertexCoords.emplace_back(glm::vec3(1.0f, 1.0f, 0.0f));
    m_vertexCoords.emplace_back(glm::vec3(1.0f, 1.0f, 1.0f));
    m_vertexCoords.emplace_back(glm::vec3(0.0f, 1.0f, 1.0f));
    m_vertexCoords.emplace_back(glm::vec3(1.0f, 1.0f, 0.0f));
    m_vertexCoords.emplace_back(glm::vec3(0.0f, 1.0f, 1.0f));
    m_vertexCoords.emplace_back(glm::vec3(0.0f, 1.0f, 0.0f));

    m_vertexCoords.emplace_back(glm::vec3(0.0f, 0.0f, 1.0f));
    m_vertexCoords.emplace_back(glm::vec3(1.0f, 0.0f, 1.0f));
    m_vertexCoords.emplace_back(glm::vec3(1.0f, 0.0f, 0.0f));
    m_vertexCoords.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f));
    m_vertexCoords.emplace_back(glm::vec3(0.0f, 0.0f, 1.0f));
    m_vertexCoords.emplace_back(glm::vec3(1.0f, 0.0f, 0.0f));

    m_textureCoords.emplace_back(glm::vec2(1.0f, 0.0f));
    m_textureCoords.emplace_back(glm::vec2(0.0f, 0.0f));
    m_textureCoords.emplace_back(glm::vec2(0.0f, 1.0f));
    m_textureCoords.emplace_back(glm::vec2(1.0f, 0.0f));
    m_textureCoords.emplace_back(glm::vec2(0.0f, 1.0f));
    m_textureCoords.emplace_back(glm::vec2(1.0f, 1.0f));

    m_textureCoords.emplace_back(glm::vec2(0.0f, 0.0f));
    m_textureCoords.emplace_back(glm::vec2(1.0f, 1.0f));
    m_textureCoords.emplace_back(glm::vec2(1.0f, 0.0f));
    m_textureCoords.emplace_back(glm::vec2(0.0f, 1.0f));
    m_textureCoords.emplace_back(glm::vec2(1.0f, 1.0f));
    m_textureCoords.emplace_back(glm::vec2(0.0f, 0.0f));

    m_textureCoords.emplace_back(glm::vec2(1.0f, 0.0f));
    m_textureCoords.emplace_back(glm::vec2(0.0f, 0.0f));
    m_textureCoords.emplace_back(glm::vec2(0.0f, 1.0f));
    m_textureCoords.emplace_back(glm::vec2(1.0f, 0.0f));
    m_textureCoords.emplace_back(glm::vec2(0.0f, 1.0f));
    m_textureCoords.emplace_back(glm::vec2(1.0f, 1.0f));

    m_textureCoords.emplace_back(glm::vec2(1.0f, 0.0f));
    m_textureCoords.emplace_back(glm::vec2(0.0f, 0.0f));
    m_textureCoords.emplace_back(glm::vec2(1.0f, 1.0f));
    m_textureCoords.emplace_back(glm::vec2(0.0f, 1.0f));
    m_textureCoords.emplace_back(glm::vec2(1.0f, 1.0f));
    m_textureCoords.emplace_back(glm::vec2(0.0f, 0.0f));

    m_textureCoords.emplace_back(glm::vec2(0.0f, 1.0f));
    m_textureCoords.emplace_back(glm::vec2(1.0f, 1.0f));
    m_textureCoords.emplace_back(glm::vec2(1.0f, 0.0f));
    m_textureCoords.emplace_back(glm::vec2(0.0f, 1.0f));
    m_textureCoords.emplace_back(glm::vec2(1.0f, 0.0f));
    m_textureCoords.emplace_back(glm::vec2(0.0f, 0.0f));

    m_textureCoords.emplace_back(glm::vec2(1.0f, 1.0f));
    m_textureCoords.emplace_back(glm::vec2(1.0f, 0.0f));
    m_textureCoords.emplace_back(glm::vec2(0.0f, 0.0f));
    m_textureCoords.emplace_back(glm::vec2(0.0f, 1.0f));
    m_textureCoords.emplace_back(glm::vec2(1.0f, 1.0f));
    m_textureCoords.emplace_back(glm::vec2(0.0f, 0.0f));

    m_count += 36;
}
