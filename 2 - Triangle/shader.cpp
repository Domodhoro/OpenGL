#include <stdexcept>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"

Shader::Shader(const char* vertexSource, const char* fragmentSource) : m_vertex(compileVertex(vertexSource)), m_fragment(compileFragment(fragmentSource)) {
    m_shader = glCreateProgram();

    glAttachShader(m_shader, m_vertex);
    glAttachShader(m_shader, m_fragment);
    glLinkProgram(m_shader);

    int success = 0;
    glGetProgramiv(m_shader, GL_LINK_STATUS, &success);
    
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(m_shader, 512, nullptr, infoLog);

        throw std::runtime_error("Falha ao compilar shader: " + std::string(infoLog));
    }

    glDeleteShader(m_vertex);
    glDeleteShader(m_fragment);
}

Shader::~Shader() {
    glDeleteProgram(m_shader);
}

unsigned int& Shader::use() {
    return m_shader;
}

unsigned int Shader::compileVertex(const char* vertexPath) {
    unsigned int m_vertex = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(m_vertex, 1, &vertexPath, 0);
    glCompileShader(m_vertex);

    int success = 0;
    glGetShaderiv(m_vertex, GL_COMPILE_STATUS, &success);
    
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(m_vertex, 512, nullptr, infoLog);

        throw std::runtime_error("Falha ao compilar vertex: " + std::string(infoLog));
    }

    return m_vertex;
}

unsigned int Shader::compileFragment(const char* fragmentPath) {
    unsigned int m_fragment = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(m_fragment, 1, &fragmentPath, 0);
    glCompileShader(m_fragment);

    int success = 0;
    glGetShaderiv(m_fragment, GL_COMPILE_STATUS, &success);
    
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(m_fragment, 512, nullptr, infoLog);

        throw std::runtime_error("Falha ao compilar fragment: " + std::string(infoLog));
    }

    return m_fragment;
}

void Shader::setUniformMatrix(const char* ID, const glm::mat4& matrix) const {
    glUniformMatrix4fv(glGetUniformLocation(m_shader, ID), 1, GL_FALSE, value_ptr(matrix));
}
