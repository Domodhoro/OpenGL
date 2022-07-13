#ifndef DRAGON_HPP
#define DRAGON_HPP

#include <memory>
#include <vector>

using std::unique_ptr;

#include <glm/glm.hpp>

using glm::mat4;
using glm::vec3;

#include "mesh.hpp"
#include "shader.hpp"

class Dragon {
public:
    Dragon();
    ~Dragon();

    void render(const mat4&, const mat4&, const vec3&) const;

private:
    unsigned int m_VAO = 0u;
    const float m_rotationSpeed = 30.0f;

    unique_ptr<Shader> m_shader;
    unique_ptr<Mesh> m_mesh;
};

#endif
