#ifndef MESH_HPP
#define MESH_HPP

#include <cstring>
#include <vector>
#include <stdexcept>

#include <glm/glm.hpp>

class Mesh {
    FILE* file = nullptr;

    std::vector<glm::vec3> m_vertexCoords, m_normalCoords, m_tempVertex, m_tempNormal;
    std::vector<unsigned int> m_vertexIndices, m_normalIndices;

    unsigned int m_count = 0u;

    void build();

public:
    Mesh(const char*);

    std::vector<glm::vec3>& getVertexCoords(), & getNormalCoords();

    unsigned int& getCount();
};

#endif
