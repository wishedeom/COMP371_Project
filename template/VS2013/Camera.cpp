#include "camera.h"
#include <stdexcept>
#include "GLM/GTC/matrix_transform.hpp"


const glm::vec3 Camera::up(0.0f, 0.0f, 1.0f);

const float Camera::mouseSensitivity = 0.001f;

const float Camera::movementSpeed = 0.1f;


Camera::Camera(const glm::vec3& position, const glm::vec3& orientation, float fov, const float nearPlane, const float farPlane, GLFWwindow& window)
	: m_position(position)
{
	setOrientation(orientation);
	setFOV(fov);
	setFarPlane(farPlane);
	setNearPlane(nearPlane);

	// Set aspect ratio
	int width, height;
	glfwGetWindowSize(&window, &width, &height);
	m_aspectRatio = width / height;

	// Set initial cursor positions
	double x, y;
	glfwGetCursorPos(&window, &x, &y);
	m_xCursorPos = x;
	m_yCursorPos = y;
}


Camera::Camera(GLFWwindow& window)
	: Camera(glm::vec3(0.0f, 0.0f, 0.2f), glm::vec3(1.0f, 0.0f, 0.0f), 1.0f, 0.2f, 100.0f, window) {}


glm::vec3 Camera::position() const { return m_position; }


glm::vec3 Camera::orientation() const { return m_orientation; }


glm::vec3 Camera::forward() const
{
	return glm::vec3(m_orientation.x, m_orientation.y, 0.0f);	// If Camera::up changes, so must this.
}


glm::vec3 Camera::right() const
{
	return glm::cross(forward(), up);
}


float Camera::fov() const { return m_fov; }


float Camera::aspectRatio() const { return m_aspectRatio; }


float Camera::nearPlane() const { return m_nearPlane; }


float Camera::farPlane() const { return m_farPlane; }


glm::mat4 Camera::projection() const
{
	return glm::perspective(m_fov, m_aspectRatio, m_nearPlane, m_farPlane);
}


glm::mat4 Camera::view() const
{
	return glm::lookAt(m_position, m_position + m_orientation, up);
}


void Camera::setPosition(const glm::vec3& position) { m_position = position; }


void Camera::setOrientation(const glm::vec3& orientation)
{
	if (orientation == glm::vec3())
	{
		throw std::logic_error("Orientation cannot be the zero vector.");
	}
	m_orientation = glm::normalize(orientation);
}


void Camera::setFOV(const float fov)
{
	if (!(0.f < fov && fov < 180.f))
	{
		throw std::logic_error("Field-of-view angle must be between 0 and 180 degrees, exclusive.");
	}
	m_fov = fov;
}


void Camera::setAspectRatio(const float aspectRatio)
{
	if (!(0.f < aspectRatio))
	{
		throw std::logic_error("Aspect ratio must be strictly positive.");
	}
	m_aspectRatio = aspectRatio;
}


void Camera::setNearPlane(const float nearPlane)
{
	if (!(0.f < nearPlane))
	{
		throw std::logic_error("Near plane distance must be strictly positive.");
	}
	if (!(nearPlane < m_farPlane))
	{
		throw std::logic_error("Near plane must be nearer than the far plane.");
	}
	m_nearPlane = nearPlane;
}


void Camera::setFarPlane(const float farPlane)
{
	if (!(0.f < farPlane))
	{
		throw std::logic_error("Far plane distance must be strictly positive.");
	}
	if (!(m_nearPlane < farPlane))
	{
		throw std::logic_error("Far plane must be farther then the near plane.");
	}
	m_farPlane = farPlane;
}


void Camera::translate(const glm::vec3& direction)
{
	m_position += direction;
}


void Camera::orientToCursor(const double x, const double y)
{
	const float horizontalAngle = (m_xCursorPos - x) * mouseSensitivity;
	const float verticalAngle = (m_yCursorPos - y) * mouseSensitivity;
	m_orientation = glm::vec3(glm::rotate(glm::rotate(glm::mat4(1.0f), horizontalAngle, up), verticalAngle, right())  * glm::vec4(m_orientation, 0.0f));
	m_xCursorPos = x;
	m_yCursorPos = y;
}