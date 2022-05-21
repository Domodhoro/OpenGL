#ifndef EARTH_HPP
#define EARTH_HPP

#include <vector>

#include <glm/glm.hpp>

#include "shader.hpp"

class Earth
{
public:
    Earth(const unsigned int&);

    Earth(const Earth&) = delete;
    Earth& operator=(const Earth&) = delete;

    ~Earth();

    void draw(const glm::mat4&, const glm::mat4&) const;

private:
    unsigned int m_texture = 0u, m_VAO = 0u, m_count = 0u;

    std::vector<glm::vec3> m_vertexCoords;
	std::vector<glm::vec2> m_textureCoords;
	std::vector<unsigned short> m_indiceCoords;

	std::unique_ptr<Shader> m_shader;

    void mesh(const unsigned int, const unsigned int);
};

#endif
