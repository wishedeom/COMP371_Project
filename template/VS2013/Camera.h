#pragma once
#include "glm.hpp"
#include "glfw3.h"

// The Camera class represents the user's point of view in the scene. The camera has a position and orientation in three-dimensional space, and the
// view volume of the camera itself is determined by it's field-of-view (FOV) angle, and the aspect ratio between the width and height of the screen.
class Camera
{
	static const glm::vec3 up;				// The camera's relative up position in the world.
	static const float mouseSensitivity;	// Sensitivity of the camera's orientation to mouse movement.

	glm::vec3 m_position;		// The camera's position
	glm::vec3 m_orientation;	// The direction the camera is pointing.
	float m_fov;				// The angle of the camera's field-of-view, in degrees. Must be between 0 and 180, exclusive.
	float m_aspectRatio;		// The ratio between the width and height of the viewport. Must be greater than 0.
	float m_nearPlane;			// The distance between the camera and the near image plane
	float m_farPlane;			// The distance between the camera and the far image plane
	double m_xCursorPos;		// The mouse cursor's previous x-position.
	double m_yCursorPos;		// The mouse cursor's previous y-position.

public:

	static const float movementSpeed;		// Speed of planar movement.

	// Constructs a camera with a given initial position, orientation, FOV, aspect ratio, near plane, and far plane, displaying to a given window.
	// position: The camera's initial position.
	// orientation: The camera's new orientation. Cannot be the zero vector.
	// fov: The camera's initial field of view angle, in degrees. Must be between 0 and 180, exclusive.
	// aspectRatio: The camera's initial aspect ratio. Must be greater than 0.
	// nearPlane: The distance between the camera and the near image plane.
	// farPlane: The distance between the camera and the far image plane.
	// window: The window the camera will be displaying to.
	Camera(const glm::vec3& position, const glm::vec3& orientation, float fov, const float nearPlane, const float farPlane, GLFWwindow& window);

	// Constructs a camera with default parameters displaying to a given window.
	// window: The window the camera will be displaying to.
	Camera(GLFWwindow& window);


	// Returns the camera's position.
	glm::vec3 position() const;


	// Returns the camera's orientation.
	glm::vec3 orientation() const;


	// Returns the camera's forward direction, in the plane of the world.
	glm::vec3 forward() const;


	// Returns the camera's left direction, in the plane of the world.
	glm::vec3 right() const;


	// Returns the camera's field-of-view (FOV) angle.
	float fov() const;


	// Returns the camera's aspect ratio.
	float aspectRatio() const;


	// Returns the camera's near plane distance.
	float nearPlane() const;


	// Returns the camera's far plane distance.
	float farPlane() const;


	// Returns the camera's projection matrix.
	glm::mat4 projection() const;


	// Returns the camera's view matrix.
	glm::mat4 view() const;


	// Moves the camera to a new position.
	// position: The camera's new position.
	void setPosition(const glm::vec3& position);


	// Sets the camera to a new orientation.
	// orientation: The camera's new orientation. Cannot be the zero vector.
	void setOrientation(const glm::vec3& orientation);


	// Sets the camera's field of view angle.
	// fov: The camera's new field-of-view angle, in degrees. Must be between 0 and 180, exclusive.
	void setFOV(const float fov);


	// Sets the camera's aspect ratio.
	// fov: The camera's new aspect ratio. Must be positive.
	void setAspectRatio(const float aspectRatio);


	// Sets the camera's near plane distance.
	// nearPlane: The camera's new near plane distance. Must be positive and less than the far plane distance.
	void setNearPlane(const float nearPlane);


	// Sets the camera's far plane distance.
	// farPlane: The camera's new far plane distance. Must be positive and greater than the near plane distance.
	void setFarPlane(const float farPlane);


	// Translates the camera by the given vector.
	void translate(const glm::vec3& direction);


	// Orients the camera based on new mouse cursor position, relative to the old cursor position.
	// x: The mouse cursor's x-position.
	// y: The mouse cursor's y-position.
	void orientToCursor(const double x, const double y);
};