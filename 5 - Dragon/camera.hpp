#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

class Camera
{
public:
    Camera(const float, const float, const float, const float);

    void setPosition(const glm::vec3);

	glm::mat4 getProjectionMatrix() const;
	glm::mat4 getViewMatrix() const;

private:
    float m_fov = 60.0f, m_aspect = 1.0f, m_nearPlane = 0.1f, m_farPlane = 10.0f;

    glm::vec3 m_position, m_front, m_up;
};

#endif
