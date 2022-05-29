#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

#include <glm/glm.hpp>

class Shader {
    unsigned int m_shader = 0u, m_vertex = 0u, m_fragment = 0u, compileVertex(const char*), compileFragment(const char*);

    std::string read(const char*) const;
    
public:
    Shader(const char*, const char*);
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    ~Shader();

    unsigned int& use();

    void setUniformMatrix(const char*, const glm::mat4&) const;
};

#endif
