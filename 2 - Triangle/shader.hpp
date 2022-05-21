#ifndef SHADER_HPP
#define SHADER_HPP

#include <glm/glm.hpp>

class Shader
{
public:
    Shader(const char*, const char*);

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    ~Shader();

    unsigned int& use();

    void setUniformMatrix(const char*, const glm::mat4&) const;

private:
    unsigned int m_shader = 0u, m_vertex = 0u, m_fragment = 0u;

    unsigned int compileVertex(const char*);
    unsigned int compileFragment(const char*);
};

#endif
