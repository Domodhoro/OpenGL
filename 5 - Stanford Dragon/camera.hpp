#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

class Camera {
    float m_fov = 60.0f, m_aspect = 1.0f, m_nearPlane = 0.1f, m_farPlane = 10.0f;

    glm::vec3 m_position = glm::vec3(0.0f), m_front = glm::vec3(0.0f, 0.0f, 1.0f), m_up = glm::vec3(0.0f, 1.0f, 0.0f);

public:
    Camera(const float, const float, const float, const float);

    void setPosition(const glm::vec3);

	glm::mat4 getProjectionMatrix() const, getViewMatrix() const;
};

#endif
