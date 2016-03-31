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


class DirectionalLight
{
	glm::vec3 m_direction;
	glm::vec3 m_ambientColour;
	glm::vec3 m_diffuseColour;
	glm::vec3 m_specularColour;

	Shader m_shader;
	const Camera& m_camera;

public:
	DirectionalLight(const Camera& camera);
	void UseShader() const;
	const Shader& getShader() const;
};