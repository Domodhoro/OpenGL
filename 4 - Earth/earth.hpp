#ifndef EARTH_HPP
#define EARTH_HPP

#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;

#include <glm/glm.hpp>

using glm::mat4;
using glm::vec2;
using glm::vec3;

#include "shader.hpp"

class Earth {
public:
    Earth(const unsigned int&);
    ~Earth();

    void render(const mat4&, const mat4&) const;

private:
    unsigned int m_texture = 0u, m_VAO = 0u;

    vector<vec3> m_vertexCoords;
    vector<vec2> m_textureCoords;
    vector<unsigned short> m_indiceCoords;

    unique_ptr<Shader> m_shader;

    void mesh(const unsigned int, const unsigned int);
};

#endif
