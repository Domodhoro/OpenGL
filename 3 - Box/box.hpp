#ifndef BOX_HPP
#define BOX_HPP

#include <memory>
#include <vector>

using std::vector;
using std::unique_ptr;
using std::make_unique;

#include <glm/glm.hpp>

using glm::mat4;
using glm::vec3;
using glm::vec2;

#include "shader.hpp"

class Box {
public:
    Box(const unsigned int&);
    ~Box();

    void render(mat4&, mat4&) const;

private:
    unsigned int m_texture = 0u, m_VAO = 0u;

    struct Mesh {
        unsigned int m_count = 0u;

        vector<vec3> m_vertexCoords;
        vector<vec2> m_textureCoords;

        void setup();
    }
    mesh;

    unique_ptr<Shader> m_shader;
};

#endif
