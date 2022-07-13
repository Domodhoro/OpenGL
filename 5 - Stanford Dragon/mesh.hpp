#ifndef MESH_HPP
#define MESH_HPP

#include <cstring>
#include <vector>
#include <stdexcept>

using std::vector;

#include <glm/glm.hpp>

using glm::vec3;

class Mesh {
public:
    Mesh(const char*);

    vector<vec3>& getVertexCoords(), & getNormalCoords();

    unsigned int& getCount();

private:
    FILE* file = nullptr;

    vector<glm::vec3> m_vertexCoords, m_normalCoords, m_tempVertex, m_tempNormal;
    vector<unsigned int> m_vertexIndices, m_normalIndices;

    unsigned int m_count = 0u;

    void setup();
};

#endif
