#ifndef BOX_HPP
#define BOX_HPP

#include <memory>
#include <vector>

#include <glm/glm.hpp>

#include "shader.hpp"

class Box {
    unsigned int m_texture = 0u, m_VAO = 0u, m_count = 0u;

    std::vector<glm::vec3> m_vertexCoords;
    std::vector<glm::vec2> m_textureCoords;

    std::unique_ptr<Shader> m_shader;
    
    void mesh();
    
public:
    Box(const unsigned int&);
    Box(const Box&) = delete;
    Box& operator=(const Box&) = delete;

    ~Box();

    void draw(glm::mat4&, glm::mat4&) const;
};

#endif
