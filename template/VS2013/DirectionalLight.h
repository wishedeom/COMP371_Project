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
	DirectionalLight(Camera);
	void UseShader();

private:
	static Shader shader;
	Camera& camera;

};