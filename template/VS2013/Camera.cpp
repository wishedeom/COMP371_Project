#include "camera.h"
#include <stdexcept>
#include "GLM/GTC/matrix_transform.hpp"


const glm::vec3 Camera::up(0.0f, 0.0f, 1.0f);


Camera::Camera(const glm::vec3& position, const glm::vec3& orientation, float fov, const float aspectRatio, const float nearPlane, const float farPlane)
	: m_position(position)
{
	setOrientation(orientation);
	setFOV(fov);
	setAspectRatio(aspectRatio);
	setFarPlane(farPlane);
	setNearPlane(nearPlane);
}


Camera::Camera() : Camera(glm::vec3(), glm::vec3(0.0f, 0.0f, -1.0f), 90.0, 1.0f, 1.0f, 2.0f) {}


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
	const auto m = glm::lookAt(glm::vec3(), m_orientation, up);
	return glm::translate(m, m_position);
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
	m_nearPlane = nearPlane;
}


void Camera::setFarPlane(const float farPlane)
{
	if (!(0.f < farPlane))
	{
		throw std::logic_error("Far plane distance must be strictly positive.");
	}
	m_farPlane = farPlane;
}


void Camera::translate(const glm::vec3& direction)
{
	m_position += direction;
}