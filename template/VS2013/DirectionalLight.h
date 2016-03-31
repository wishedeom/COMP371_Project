#pragma once
#include "Shader.h"
#include "Camera.h"
#include "../ThirdParty/glm/gtc/matrix_transform.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "gtc/constants.hpp"
#include "glew.h"		// include GL Extension Wrangler
#include "glfw3.h"  // include GLFW helper library
#include "glm.hpp"


class DirectionalLight
{
public:
	DirectionalLight(const Camera& camera);
	void UseShader() const;
	const Shader& getShader() const;

private:
	Shader m_shader;
	const Camera& m_camera;

};