#include <memory>
#include <cmath>
#include <stdexcept>

using std::make_unique;
using std::runtime_error;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using glm::radians;

#include "earth.hpp"

Earth::Earth(const unsigned int& texture) : m_shader(make_unique<Shader>("earthVertex.glsl", "earthFragment.glsl")), m_texture(texture) {
    mesh(32u, 64u);

    glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

    unsigned int vertexBuffer = 0u, textureBuffer = 0u;

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_vertexCoords.size() * sizeof(vec3), &m_vertexCoords.at(0), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(vec3), (void*)(0 * sizeof(float)));

	m_vertexCoords.clear();

	glGenBuffers(1, &textureBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_textureCoords.size() * sizeof(vec2), &m_textureCoords.at(0), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(vec2), (void*)(0 * sizeof(float)));

	m_textureCoords.clear();

	if (!m_VAO) {
		throw runtime_error("Falha ao criar VAO.");
	}
}

Earth::~Earth() {
    m_indiceCoords.clear();

	glDeleteVertexArrays(1, &m_VAO);
}

void Earth::render(const mat4& projectionMatrix, const mat4& viewMatrix) const {
    glCullFace(GL_FRONT);

	glUseProgram(m_shader->use());
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glBindVertexArray(m_VAO);

	mat4 modelMatrix = mat4(1.0f);
	modelMatrix = rotate(modelMatrix, radians(static_cast<float>(45.0f * glfwGetTime())), vec3(0.0f, 1.0f, 0.0f));

	m_shader->setUniformMatrix("model", modelMatrix);
	m_shader->setUniformMatrix("view", viewMatrix);
	m_shader->setUniformMatrix("projection", projectionMatrix);

	glDrawElements(GL_QUADS, m_indiceCoords.size(), GL_UNSIGNED_SHORT, &m_indiceCoords.at(0));
	glBindVertexArray(0);
}

void Earth::mesh(const unsigned int rings, const unsigned int sectors) {
    const float R = 1.0f / (rings - 1.0f), S = 1.0f / (sectors - 1.0f);

	for (int r = 0; r != rings; ++r) {
		for (int s = 0; s != sectors; ++s) {
			const float x = cos(2.0f * M_PI * s * S) * sin(M_PI * r * R);
			const float y = sin(-(M_PI / 2.0f) + M_PI * r * R);
			const float z = sin(2.0f * M_PI * s * S) * sin(M_PI * r * R);

			m_vertexCoords.emplace_back(vec3(x, y, z));
			m_textureCoords.emplace_back(vec2(s * S, r * R));

			m_indiceCoords.emplace_back(r * sectors + s);
			m_indiceCoords.emplace_back(r * sectors + (s + 1u));
			m_indiceCoords.emplace_back((r + 1u) * sectors + (s + 1u));
			m_indiceCoords.emplace_back((r + 1u) * sectors + s);
		}
	}
}
