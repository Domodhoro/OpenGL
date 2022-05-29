#ifndef DRAGON_HPP
#define DRAGON_HPP

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "mesh.hpp"
#include "shader.hpp"

class Dragon {
    unsigned int m_VAO = 0u;
    const float m_rotationSpeed = 30.0f;

    std::unique_ptr<Shader> m_shader;
    std::unique_ptr<Mesh> m_mesh;

public:
    Dragon();
    Dragon(const Dragon&) = delete;
    Dragon& operator=(const Dragon&) = delete;

    ~Dragon();

    void render(const glm::mat4&, const glm::mat4&, const glm::vec3&) const;
};

#endif
