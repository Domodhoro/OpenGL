#include <glm/gtc/matrix_transform.hpp>

#include "camera.hpp"

Camera::Camera(const float fov, const float aspect, const float nearPlane, const float farPlane) : m_fov(fov), m_aspect(aspect), m_nearPlane(nearPlane), m_farPlane(farPlane) {}

void Camera::setPosition(const glm::vec3 position) {
    m_position = position;
}

glm::mat4 Camera::getProjectionMatrix() const {
	return glm::perspective(glm::radians(m_fov), m_aspect, m_nearPlane, m_farPlane);
}

glm::mat4 Camera::getViewMatrix() const {
	return glm::lookAt(m_position, m_position + m_front, m_up);
}
