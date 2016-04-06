#pragma once

#include <memory>

#include "glew.h"
#include "glm.hpp"

#include "World.h"
#include "Camera.h"

// Controls the player's movement.
class PlayerController
{
	// Describes motion along the forward-backward axis
	enum class AxialDirection
	{
		Forward,
		Backward,
		Null
	};

	// Describes motion along the left-right axis
	enum class LateralDirection
	{
		Left,
		Right,
		Null
	};

	Camera& m_camera;			// The player's camera
	World& m_world;				// The world the player lives in
	//std::vector<Block> blocks;

	AxialDirection m_axial;		// The player's current axial motion
	LateralDirection m_lateral;	// The player's current lateral motion

	glm::vec3 m_velocity;	// Player velocity in egocentric coordinates
	bool m_isRunning;		// True if and only if the player is currently running

	double m_lastFrameTime;	// The clock time at the end of the last frame

	void updatePosition(const double deltaT);
	void updateVelocity(const double deltaT);

	bool isOnGround() const;
	bool isOutsideBoundingBox();
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