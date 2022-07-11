#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <vector>
#include <memory>

using std::unique_ptr;
using std::make_unique;
using std::vector;
using std::runtime_error;

#include <glm/glm.hpp>

using glm::vec3;
using glm::mat4;

#include "shader.hpp"

class Triangle {
public:
    Triangle(const char*, const char*);
    ~Triangle();

    void render(mat4&) const;

private:
    unsigned int m_VAO = 0u, m_count = 0u;

    unique_ptr<Shader> m_shader;
    vector<vec3> m_vertexCoords, m_colorCoords;

    void setup();
};

#endif
