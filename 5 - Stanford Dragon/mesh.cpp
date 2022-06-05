#include <stdexcept>

#include "mesh.hpp"

Mesh::Mesh(const char* meshPath) : file(fopen(meshPath, "r")) {
    if (file == nullptr) {
        throw std::runtime_error("Falha ao abrir arquivo modelo.");
    }

    while (true) {
        char line[128];

        if (fscanf(file, "%s", line) == EOF) {
            break;
        }

        if (strcmp(line, "v") == 0) {
            glm::vec3 vertex = glm::vec3(0.0);

            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);

            m_tempVertex.emplace_back(vertex);
        } else if (strcmp(line, "vn") == 0) {
            glm::vec3 normal = glm::vec3(0.0);

            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);

            m_tempNormal.emplace_back(normal);
        } else if (strcmp(line, "f") == 0) {
            unsigned int vertexIndex[3] = {0, 0, 0};
            unsigned int normalIndex[3] = {0, 0, 0};

            fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);

            m_vertexIndices.emplace_back(vertexIndex[2]);
            m_vertexIndices.emplace_back(vertexIndex[1]);
            m_vertexIndices.emplace_back(vertexIndex[0]);

            m_normalIndices.emplace_back(normalIndex[2]);
            m_normalIndices.emplace_back(normalIndex[1]);
            m_normalIndices.emplace_back(normalIndex[0]);
        }
    }

    fclose(file);

    build();

    m_tempVertex.clear();
    m_tempNormal.clear();
    m_vertexIndices.clear();
    m_normalIndices.clear();
}

std::vector<glm::vec3>& Mesh::getVertexCoords() {
    return m_vertexCoords;
}

std::vector<glm::vec3>& Mesh::getNormalCoords() {
    return m_normalCoords;
}

unsigned int& Mesh::getCount() {
    return m_count;
}

void Mesh::build() {
    for( int i = 0; i != static_cast<int>(m_vertexIndices.size()); ++i) {
        glm::vec3 vertex = m_tempVertex.at(m_vertexIndices.at(i) - 1);
        glm::vec3 normal = m_tempNormal.at(m_normalIndices.at(i) - 1);

        m_vertexCoords.emplace_back(vertex);
        m_normalCoords.emplace_back(normal);

        ++m_count;
    }
}
