#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

using glm::vec3;
using glm::mat4;

class Camera {
public:
    Camera(const float, const float, const float, const float);

    void setPosition(const vec3);

	mat4 getProjectionMatrix() const, getViewMatrix() const;

private:
    float m_fov = 60.0f, m_aspect = 1.0f, m_nearPlane = 0.1f, m_farPlane = 10.0f;

    vec3 m_position = vec3(0.0f), m_front = vec3(0.0f, 0.0f, 1.0f), m_up = vec3(0.0f, 1.0f, 0.0f);
};

#endif
