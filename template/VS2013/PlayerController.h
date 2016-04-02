#pragma once

#include <memory>

#include "glew.h"
#include "glm.hpp"

#include "Camera.h"

// Controls the player's movement.
class PlayerController
{
	enum class AxialDirection
	{
		Forward,
		Backward,
		Null
	};

	enum class LateralDirection
	{
		Left,
		Right,
		Null
	};

	Camera& m_camera;

	AxialDirection m_axial;
	LateralDirection m_lateral;

	glm::vec3 m_velocity;	// Player velocity in egocentric coordinates
	bool m_isRunning;

	double m_lastFrameTime;

	void updatePosition(const double deltaT);
	void updateVelocity(const double deltaT);

public:

	static const double maxSpeed;
	static const double acceleration;
	static const double runFactor;

	PlayerController(Camera& camera);

	void moveForward();
	void moveBackward();
	void stopAxial();
	void moveLeft();
	void moveRight();
	void stopLateral();

	void setRunning(const bool isRunning);

	Camera& camera();

	void update();
};