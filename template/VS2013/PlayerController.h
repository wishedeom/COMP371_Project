#pragma once

#include <memory>

#include "glew.h"
#include "glm.hpp"

#include "World.h"
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
	World& m_world;
	std::vector<Block> blocks;

	AxialDirection m_axial;
	LateralDirection m_lateral;

	glm::vec3 m_velocity;	// Player velocity in egocentric coordinates
	bool m_isRunning;

	double m_lastFrameTime;

	void updatePosition(const double deltaT);
	void updateVelocity(const double deltaT);

	bool isOnGround() const;
	bool isOutsideBoundingBox();
	bool isInsideWorld();

	glm::vec3 previousPos;
public:

	static const double height;
	static const double maxSpeed;
	static const double acceleration;
	static const double runFactor;
	static const double jumpSpeed;
	static const double gravity;

	PlayerController(Camera& camera);
	PlayerController(Camera& camera, World& world);

	void moveForward();
	void moveBackward();
	void stopAxial();
	void moveLeft();
	void moveRight();
	void stopLateral();

	void setRunning(const bool isRunning);
	void jump();

	Camera& camera();

	void update();
};