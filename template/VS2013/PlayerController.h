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

	AxialDirection m_axial;		// The player's current axial motion
	LateralDirection m_lateral;	// The player's current lateral motion

	glm::vec3 m_velocity;		// Player velocity in egocentric coordinates
	bool m_isRunning;			// True if and only if the player is currently running

	double m_lastFrameTime;		// The clock time at the end of the last frame

	// Runs each frame to update the player's position based on its current velocity.
	// deltaT: The time difference between the previous and current frames.
	void updatePosition(const double deltaT);

	// Runs each fram to update the player's velocity based on its current acceleration, based on key input.
	// deltaT: The time difference between the previous and current frames.
	void updateVelocity(const double deltaT);

	// Returns true if and only if the player is (approximately) on the ground.
	bool isOnGround() const;

	// Returns true if and only if the player is outside a bounding box.

	bool isOutsideBoundingBox();
	bool isOutsideWorld();

	glm::vec3 previousPos;

	int block_size;
	int world_size;

public:

	static const double height;			// The player's height
	static const double maxSpeed;		// The maximum translational speed of the player
	static const double acceleration;	// How quickly the player speeds up or slows down
	static const double runFactor;		// How many times faster the player moves while running
	static const double jumpSpeed;		// The vertical speed the player gets when jumping
	static const double gravity;		// Downward gravitational acceleration

	// Constructs a PlayerController looking out of a given Camera in a given World.
	PlayerController(Camera& camera, World& world, int block_size, int world_size);

	// These functions begin and end the player's motion
	void moveForward();
	void moveBackward();
	void stopAxial();
	void moveLeft();
	void moveRight();
	void stopLateral();

	// Set's the player's running state.
	// isRunning: True if and only if the player will be running.
	void setRunning(const bool isRunning);

	// Causes the player to jump upwards.
	void jump();

	// Returns a reference to the player's camera.
	Camera& camera() const;

	// Called every frame to update's the player's position and velocity.
	void update();

	void isInsideCity();
};