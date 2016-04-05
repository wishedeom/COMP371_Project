#include "PlayerController.h"

#include <cmath>
#include <iostream>

#include "glew.h"
#include "glfw3.h"
#include "GLM/GTC/matrix_transform.hpp"

#include "Camera.h"
#include "utility.h"


const double PlayerController::height = 0.1;
const double PlayerController::maxSpeed = 5.0;
const double PlayerController::acceleration = 15.0;
const double PlayerController::runFactor = 2.0;
const double PlayerController::jumpSpeed = 3.0;
const double PlayerController::gravity = -9.8;


PlayerController::PlayerController(Camera& camera, World& world)
	: m_camera(camera)
	, m_axial(AxialDirection::Null)
	, m_lateral(LateralDirection::Null)
	, m_lastFrameTime(glfwGetTime())
	, m_isRunning(false)
	, m_world(world)
	, blocks(m_world.getBlocks())
{}
/*
PlayerController::PlayerController(Camera& camera)
	: m_camera(camera)
	, m_axial(AxialDirection::Null)
	, m_lateral(LateralDirection::Null)
	, m_lastFrameTime(glfwGetTime())
	, m_isRunning(false)
{}
*/
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

	if (isOutsideBoundingBox()){
		updatePosition(deltaT);
	}
	m_lastFrameTime = time;
	
}

void PlayerController::updatePosition(const double deltaT)
{
	const float theta = angle(m_camera.forward(), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec3 worldVelocity = glm::vec3(glm::rotate(id4, theta, up) * glm::vec4(m_velocity, 0.0f));
	const glm::vec3 displacement = worldVelocity * static_cast<float>(deltaT)* static_cast<float>(m_isRunning ? runFactor : 1.0f);
	m_camera.translate(displacement);
	if (m_camera.position().z < height)
	{
		auto newPosition = m_camera.position();
		newPosition.z = height;
		m_camera.setPosition(newPosition);
	}
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

	// Vertical deceleration
	if (!isOnGround())
	{
		m_velocity.z += gravity * deltaT;
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


bool PlayerController::isOnGround() const
{
	return std::abs(m_camera.position().z - height) / height < 0.1;
}


void PlayerController::jump()
{
	if (isOnGround())
	{
		m_velocity.z += jumpSpeed;
	}
}

bool PlayerController::isOutsideBoundingBox(){
	bool isOutsideBox = true;
	for (GLuint i = 0; i<blocks.size(); i++){
		std::vector<glm::vec3> boundingBox = blocks.at(i).getBoundingBoxes();

		//this is work in progress; the idea is to check if cam is outside the 4 bounding points
		//the logic/implementation needs improvement
		//it isnt currently checking all sides of the bounding box
		//what if i subtract cam.position vector by the bounding box vectors?
		glm::vec3 camPos = m_camera.position();
		glm::vec3 side1(camPos - boundingBox.at(0));
		glm::vec3 side2(camPos - boundingBox.at(1));
		glm::vec3 side3(camPos - boundingBox.at(2));
		glm::vec3 side4(camPos - boundingBox.at(3));

		//std::cout << side1.x << std::endl;
		//std::cout << side2.x << std::endl;
		//std::cout << side3.x << std::endl;
		//std::cout << side4.x << std::endl;


		if (side1.x >= 0.f && side1.y >= 0.f){
			isOutsideBox = false; 
			break;
		}

		else if (side2.x >= 0.f && side2.y >= 0.f){
			isOutsideBox = false;
			break;
		}

		else if (side3.x >= 0.f && side3.y >= 0.f){
			isOutsideBox = false;
			break;
		}

		else if (side4.x >= 0.f && side4.y >= 0.f){
			isOutsideBox = false;
			break;
		}

		/*
		if (((m_camera.position().x > boundingBox.at(0).x && m_camera.position().y > boundingBox.at(0).y) &&
			(m_camera.position().x < boundingBox.at(1).x && m_camera.position().y < boundingBox.at(1).y)))
			
			|| //the previous 2 lines check if the cam is touching 1 side; same logic for next 2 lines
			((m_camera.position().x < boundingBox.at(1).x && m_camera.position().y < boundingBox.at(1).y) &&
			(m_camera.position().x > boundingBox.at(2).x && m_camera.position().y > boundingBox.at(2).y)))
			
			{
			isOutsideBox = false;
		}*/
	}

	return isOutsideBox;
}