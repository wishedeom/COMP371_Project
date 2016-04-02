#include "PlayerController.h"

#include <cmath>

#include "glew.h"
#include "glfw3.h"

#include "Camera.h"

const double PlayerController::maxSpeed = 0.1f;
const double PlayerController::acceleration = 0.1f;


PlayerController::PlayerController(Camera& camera)
	: m_camera(camera)
	, m_axial(AxialDirection::Null)
	, m_lateral(LateralDirection::Null)
	, m_lastFrameTime(glfwGetTime())
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
	updatePosition(deltaT);
	updateVelocity(deltaT);
	m_lastFrameTime = time;
}


void PlayerController::updatePosition(const double deltaT)
{
	const glm::vec3 displacement = m_velocity * static_cast<float>(deltaT);
	m_camera.translate(displacement);
}


void PlayerController::updateVelocity(const double deltaT)
{
	glm::vec3 deltaV;
	
	if (m_axial != AxialDirection::Null && std::abs(m_velocity.y) < maxSpeed)
	{
		if (m_axial == AxialDirection::Forward)
		{
			deltaV.y = acceleration * deltaT;
		}
		else if (m_axial == AxialDirection::Backward)
		{
			deltaV.y = -acceleration * deltaT;
		}
	}

	if (m_lateral != LateralDirection::Null && std::abs(m_velocity.x) < maxSpeed)
	{
		if (m_lateral == LateralDirection::Right)
		{
			deltaV.x = acceleration * deltaT;
		}
		else if (m_lateral == LateralDirection::Left)
		{
			deltaV.x = -acceleration * deltaT;
		}
	}

	m_velocity += deltaV;
}