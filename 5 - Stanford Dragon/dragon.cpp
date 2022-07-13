#include <stdexcept>
#include <memory>

using std::make_unique;
using std::runtime_error;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

using glm::radians;
using glm::vec4;

#include "dragon.hpp"

Dragon::Dragon() : m_shader(make_unique<Shader>("dragonVertex.glsl", "dragonFragment.glsl")), m_mesh(make_unique<Mesh>("Dragon.obj")) {
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    unsigned int vertexBuffer = 0u, normalBuffer = 0u;

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_mesh->getVertexCoords().size() * sizeof(vec3), &m_mesh->getVertexCoords().at(0), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vec3), (void*)(0 * sizeof(float)));

    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, m_mesh->getNormalCoords().size() * sizeof(vec3), &m_mesh->getNormalCoords().at(0), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(vec3), (void*)(0 * sizeof(float)));

    if (!m_VAO) {
        throw runtime_error("Falha ao criar VAO");
    }
}

Dragon::~Dragon() {
    glDeleteVertexArrays(1, &m_VAO);
}

void Dragon::render(const mat4& projectionMatrix, const mat4& viewMatrix, const vec3& cameraPosition) const {
    glCullFace(GL_FRONT);

    glUseProgram(m_shader->use());
	glBindVertexArray(m_VAO);

	mat4 modelMatrix = mat4(1.0f), compensation = mat4(1.0f);
	modelMatrix = rotate(modelMatrix, radians(static_cast<float>(glfwGetTime() * 30.0)), vec3(0.0f, 1.0f, 0.0f));
	compensation = rotate(compensation, radians(static_cast<float>(glfwGetTime() * -1.0 * m_rotationSpeed)), vec3(0.0f, 1.0f, 0.0f));

    vec3 color = vec3(0.3f, 0.8f, 0.4f), lightPosition = vec3(-3.0f, 4.0f, -5.0f);

	lightPosition = compensation * vec4(lightPosition, 1.0f);

	const float ambientLight = 0.0f, specularStrength = 10.0f, shininess = 32.0f;

    m_shader->setUniformMatrix("model", modelMatrix);
    m_shader->setUniformMatrix("view", viewMatrix);
    m_shader->setUniformMatrix("projection", projectionMatrix);
    m_shader->setUniformVec3f("color", color);
    m_shader->setUniformVec3f("cameraPosition", cameraPosition);
    m_shader->setUniformVec3f("lightPosition", lightPosition);
	m_shader->setUniformFloat("ambientLight", ambientLight);
	m_shader->setUniformFloat("specularStrength", specularStrength);
	m_shader->setUniformFloat("shininess", shininess);

    glDrawArrays(GL_TRIANGLES, 0, m_mesh->getCount());
    glBindVertexArray(0);
}
