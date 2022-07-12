#include <glm/gtc/matrix_transform.hpp>

using glm::perspective;
using glm::radians;
using glm::lookAt;

#include "camera.hpp"

Camera::Camera(const float fov, const float aspect, const float nearPlane, const float farPlane) : m_fov(fov), m_aspect(aspect), m_nearPlane(nearPlane), m_farPlane(farPlane) {}

void Camera::setPosition(const vec3 position) {
    m_position = position;
}

mat4 Camera::getProjectionMatrix() const {
	return perspective(radians(m_fov), m_aspect, m_nearPlane, m_farPlane);
}

mat4 Camera::getViewMatrix() const {
	return lookAt(m_position, m_position + m_front, m_up);
}
