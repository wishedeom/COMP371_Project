#include "PlayerController.h"

#include <cmath>

#include "glew.h"
#include "glfw3.h"
#include "GLM/GTC/matrix_transform.hpp"

#include "Camera.h"
#include "utility.h"


const double PlayerController::maxSpeed = 5.0f;
const double PlayerController::acceleration = 15.0f;
const double PlayerController::runFactor = 2.0f;


PlayerController::PlayerController(Camera& camera)
	: m_camera(camera)
	, m_axial(AxialDirection::Null)
	, m_lateral(LateralDirection::Null)
	, m_lastFrameTime(glfwGetTime())
	, m_isRunning(false)
{}


void PlayerController::moveForward()
{
	m_axial = AxialDirection::Forward;
}


void PlayerController::moveBackward()
{
	m_axial = AxialDirection::Backward;
}


void PlayerController::stopAxial()
{
	m_axial = AxialDirection::Null;
}


void PlayerController::moveLeft()
{
	m_lateral = LateralDirection::Left;
}


void PlayerController::moveRight()
{
	m_lateral = LateralDirection::Right;
}


void PlayerController::stopLateral()
{
	m_lateral = LateralDirection::Null;
}


void PlayerController::update()
{
	const double time = glfwGetTime();
	const double deltaT = time - m_lastFrameTime;
	updateVelocity(deltaT);
	updatePosition(deltaT);
	m_lastFrameTime = time;
}


void PlayerController::updatePosition(const double deltaT)
{
	const float theta = angle(m_camera.forward(), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec3 worldVelocity = glm::vec3(glm::rotate(id4, theta, up) * glm::vec4(m_velocity, 0.0f));
	const glm::vec3 displacement = worldVelocity * static_cast<float>(deltaT) * static_cast<float>(m_isRunning ? runFactor : 1.0f);
	m_camera.translate(displacement);
}


void PlayerController::updateVelocity(const double deltaT)
{
	glm::vec3 deltaV;

	bool axPosDec = false;
	bool axNegDec = false;
	bool latPosDec = false;
	bool latNegDec = false;

	// Forward-backward
	if ((m_axial == AxialDirection::Forward && m_velocity.y < maxSpeed) || (axNegDec = (m_axial == AxialDirection::Null && m_velocity.y < 0.0f)))
	{
		deltaV.y = acceleration * deltaT;
	}
	else if (m_axial == AxialDirection::Backward && m_velocity.y > -maxSpeed || (axPosDec = (m_axial == AxialDirection::Null && m_velocity.y > 0.0f)))
	{
		deltaV.y = -acceleration * deltaT;
	}

	// Left-right translation
	if ((m_lateral == LateralDirection::Right && m_velocity.x < maxSpeed) || (latNegDec = (m_lateral == LateralDirection::Null && m_velocity.x < 0.0f)))
	{
		deltaV.x = acceleration * deltaT;
	}
	else if (m_lateral == LateralDirection::Left && m_velocity.x > -maxSpeed || (latPosDec = (m_lateral == LateralDirection::Null && m_velocity.x > 0.0f)))
	{
		deltaV.x = -acceleration * deltaT;
	}

	// Update velocity
	m_velocity += deltaV;

	// Deceleration to zero
	if ((axNegDec && m_velocity.y > 0.0f) || (axPosDec && m_velocity.y < 0.0f))
	{
		m_velocity.y = 0.0f;
	}
	if ((latNegDec && m_velocity.x > 0.0f) || (latPosDec && m_velocity.x < 0.0f))
	{
		m_velocity.x = 0.0f;
	}
}


Camera& PlayerController::camera()
{
	return m_camera;
}


void PlayerController::setRunning(const bool isRunning)
{
	m_isRunning = isRunning;
}