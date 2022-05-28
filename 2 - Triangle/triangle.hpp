#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "shader.hpp"

class Triangle {
    unsigned int m_VAO = 0u, m_count = 0u;

    std::unique_ptr<Shader> m_shader;
    std::vector<glm::vec3> m_vertexCoords, m_colorCoords;

    void mesh(), setup();
    
    
public:
    Triangle(const char*, const char*);
    Triangle(const Triangle&) = delete;
    Triangle& operator=(const Triangle&) = delete;

    ~Triangle();

    void draw(glm::mat4&) const;
};

#endif
