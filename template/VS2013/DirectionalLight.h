#pragma once

#include "../ThirdParty/glm/gtc/matrix_transform.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "gtc/constants.hpp"
#include "glew.h"
#include "glfw3.h"
#include "glm.hpp"

#include "Shader.h"
#include "Camera.h"

// Represents a light source that uniformly illuminates the world from a single direction
class DirectionalLight
{
	glm::vec3 m_direction;		// The direction, in world coordinates, the light is pointing
	glm::vec3 m_ambientColour;	// The light's ambient colour, applies to all objects equally
	glm::vec3 m_diffuseColour;	// The light's diffuse colour
	glm::vec3 m_specularColour;	// The light's specular colour

	Shader m_shader;			// The shader object of the light
	const Camera& m_camera;		// The camera that will view the world

	double m_lastFrameTime;

public:

	// Constructs a directional light given the view camera
	DirectionalLight(const Camera& camera);

	// Uses the light's shader program
	void UseShader() const;

	// Returns the light's shader program
	const Shader& getShader() const;

	void update();
};