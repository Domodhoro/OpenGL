#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

using std::string;

#include <glm/glm.hpp>

using glm::mat4;
using glm::vec3;

class Shader {
public:
    Shader(const char*, const char*);
    ~Shader();

    unsigned int& use();

    void setUniformMatrix(const char*, const mat4&) const, setUniformVec3f(const char*, const vec3&) const, setUniformFloat(const char*, const float&) const;

private:
    unsigned int m_shader = 0u, m_vertex = 0u, m_fragment = 0u, compileVertex(const char*), compileFragment(const char*);

    string read(const char*) const;
};

#endif
