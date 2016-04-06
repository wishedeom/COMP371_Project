#include "PlayerController.h"

#include <cmath>
#include <iostream>

#include <math.h>

#include "glew.h"
#include "glfw3.h"
#include "GLM/GTC/matrix_transform.hpp"

#include "Camera.h"
#include "utility.h"


														// - STATIC CONSTANTS - //

const double PlayerController::height = 0.1;
const double PlayerController::maxSpeed = 5.0;
const double PlayerController::acceleration = 15.0;
const double PlayerController::runFactor = 2.0;
const double PlayerController::jumpSpeed = 3.0;
const double PlayerController::gravity = -9.8;


														// - MEMBER FUNCTIONS - //

PlayerController::PlayerController(Camera& camera, World& world)
	: m_camera(camera)
	, m_axial(AxialDirection::Null)
	, m_lateral(LateralDirection::Null)
	, m_lastFrameTime(glfwGetTime())
	, m_isRunning(false)
	, m_world(world)
{
	block_size = Block::size;
	world_size = world.size;
}


void PlayerController::moveForward() { m_axial = AxialDirection::Forward; }


void PlayerController::moveBackward() {	m_axial = AxialDirection::Backward; }


void PlayerController::stopAxial() { m_axial = AxialDirection::Null; }


void PlayerController::moveLeft() { m_lateral = LateralDirection::Left; }


void PlayerController::moveRight() { m_lateral = LateralDirection::Right; }


void PlayerController::stopLateral() { m_lateral = LateralDirection::Null; }


// Runs every frame
void PlayerController::update()
{
	// Time between frames
	const double time = glfwGetTime();
	const double deltaT = time - m_lastFrameTime;

	// Update velocity
	updateVelocity(deltaT);

	// Check for bounding boxes
	glm::vec3 prevPos = m_camera.position();

	/*	if (isOutsideWorld() )
	{
	isInsideCity();
	}*/

	if (isOutsideBoundingBox() && !isOutsideWorld())
	{
		updatePosition(deltaT);
	}
	if (isOutsideWorld() || !isOutsideBoundingBox()){
		//	glm::vec3 camPos = m_camera.position();
		//	glm::vec3 resetPosition = glm::vec3(camPos.x - 0.1f, camPos.y - 0.1f, camPos.z);
		m_camera.setPosition(prevPos);
	}

	// Update time
	m_lastFrameTime = time;
}


void PlayerController::updatePosition(const double deltaT)
{
	// Transform player velocity in egocentric coordinates to world coordinates
	const float theta = angle(m_camera.forward(), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::vec3 worldVelocity = glm::vec3(glm::rotate(id4, theta, up) * glm::vec4(m_velocity, 0.0f));
	
	// Displacement
	glm::vec3 displacement = worldVelocity * static_cast<float>(deltaT)* static_cast<float>(m_isRunning ? runFactor : 1.0f);
	
	// Translate the camera
	m_camera.translate(displacement);

	// Correct height after jumping
	if (m_camera.position().z < height)
	{
		auto newPosition = m_camera.position();
		newPosition.z = height;
		m_camera.setPosition(newPosition);
	}
	

}


void PlayerController::updateVelocity(const double deltaT)
{
	// Change in velocity from previous frame
	glm::vec3 deltaV;

	// True if and onyl if the player is decelerating while moving in the given direction
	bool axPosDec = false;		// Positive axial (forward-backward)
	bool axNegDec = false;		// Negative axial
	bool latPosDec = false;		// Positive lateral (right in egocentric coordinates)
	bool latNegDec = false;		// Negative lateral (left)

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

	// Deceleration to zero if a direction key is released
	if ((axNegDec && m_velocity.y > 0.0f) || (axPosDec && m_velocity.y < 0.0f))
	{
		m_velocity.y = 0.0f;
	}
	if ((latNegDec && m_velocity.x > 0.0f) || (latPosDec && m_velocity.x < 0.0f))
	{
		m_velocity.x = 0.0f;
	}

	// Vertical deceleration, after a jump
	if (!isOnGround())
	{
		m_velocity.z += gravity * deltaT;
	}
}


Camera& PlayerController::camera() const { return m_camera; }


void PlayerController::setRunning(const bool isRunning) { m_isRunning = isRunning; }


// Within 0.1 player heights of the ground, to account for floating-point comparisons
bool PlayerController::isOnGround() const {	return std::abs(m_camera.position().z - height) / height < 0.1; }


void PlayerController::jump()
{
	if (isOnGround())
	{
		m_velocity.z += jumpSpeed;
	}
}


bool PlayerController::isOutsideBoundingBox()
{
	bool isOutsideBox = true;
	auto& blocks = m_world.getBlocks();
	for (GLuint i = 0; i < blocks.size(); i++)
	{
		std::vector<glm::vec3> boundingBox = blocks.at(i).getBoundingBoxes();
	
		//the 4 sides of the "square"
		if (((m_camera.position().x < boundingBox.at(0).x && m_camera.position().x > boundingBox.at(1).x) &&
			(m_camera.position().y < boundingBox.at(0).y && m_camera.position().y > boundingBox.at(1).y)))
		{
			isOutsideBox = false;
			break;
		}

		if (((m_camera.position().x < boundingBox.at(1).x && m_camera.position().x > boundingBox.at(2).x) &&
			(m_camera.position().y < boundingBox.at(1).y && m_camera.position().y > boundingBox.at(2).y)))
		{
			isOutsideBox = false;
			break;
		}

		if (((m_camera.position().x < boundingBox.at(2).x && m_camera.position().x > boundingBox.at(3).x) &&
			(m_camera.position().y < boundingBox.at(2).y && m_camera.position().y > boundingBox.at(3).y)))
		{
			isOutsideBox = false;
			break;
		}

		if (((m_camera.position().x < boundingBox.at(3).x && m_camera.position().x > boundingBox.at(0).x) &&
			(m_camera.position().y < boundingBox.at(3).y && m_camera.position().y > boundingBox.at(0).y)))
		{
			isOutsideBox = false;
			break;
		}
	}

	return isOutsideBox;
}


void PlayerController::isInsideCity()
{
	glm::vec3 centerMin = glm::vec3(block_size * (1 - world_size / 2), block_size * (1 - world_size / 2), 0.0f);
	glm::vec3 centerMax = glm::vec3(block_size * (world_size - world_size / 2), block_size * (world_size - world_size / 2), 0.0f);

	glm::vec3 camPos = m_camera.position();

	float pos_x = centerMax.x + (block_size / 2);
	float neg_x = centerMin.x - (block_size / 2);
	float pos_y = centerMax.y + (block_size / 2);
	float neg_y = centerMin.y - (block_size / 2);

	float cam_x = camPos.x;
	float cam_y = camPos.y;

	GLfloat reset_x;
	GLfloat reset_y;

	glm::vec3 resetPosition = camPos;

	if (cam_x >= pos_x)
	{
		resetPosition.x = pos_x - block_size / 2;
	}

	if (cam_x <= neg_x)
	{
		resetPosition.x = pos_x + block_size / 2;
	}

	if (cam_y >= pos_y)
	{
		resetPosition.y = pos_y - block_size / 2;
	}

	if (cam_y <= neg_y)
	{
		resetPosition.y = pos_y + block_size / 2;
	}

	resetPosition = glm::vec3(resetPosition.x, resetPosition.y, resetPosition.z);

	m_camera.setPosition(resetPosition);
}

bool PlayerController::isOutsideWorld()
{
	glm::vec3 centerMin = glm::vec3(block_size * (1 - world_size / 2), block_size * (1 - world_size / 2), 0.0f);
	glm::vec3 centerMax = glm::vec3(block_size * (world_size - world_size / 2), block_size * (world_size - world_size / 2), 0.0f);

	glm::vec3 camPos = m_camera.position();

	float pos_x = centerMax.x + (block_size / 2);
	float neg_x = centerMin.x - (block_size / 2);
	float pos_y = centerMax.y + (block_size / 2);
	float neg_y = centerMin.y - (block_size / 2);

	float cam_x = camPos.x;
	float cam_y = camPos.y;

	GLfloat reset_x;
	GLfloat reset_y;

	if (cam_x >= pos_x || cam_x <= neg_x || cam_y >= pos_y || cam_y <= neg_y)
	{
		glm::vec3 resetPosition = m_camera.position();

		if (cam_x >= pos_x)
		{
			resetPosition.x = pos_x - 0.1;
		}

		if (cam_x <= neg_x)
		{
			resetPosition.x = pos_x + 0.1;
		}

		if (cam_y >= pos_y)
		{
			resetPosition.y = pos_y - 0.1;
		}

		if (cam_y <= neg_y)
		{
			resetPosition.y = pos_y + 0.1;
		}

		resetPosition = glm::vec3(resetPosition.x, resetPosition.y, resetPosition.z);

		m_camera.setPosition(resetPosition);

		return true;
	}
	else
	{
		return false;
	}
}