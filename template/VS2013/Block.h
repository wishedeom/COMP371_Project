#pragma once

#include <vector>
#include <iostream>
#include <array>

#include "glew.h"
#include "glfw3.h"		
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "gtc/constants.hpp"

#include "Shader.h"
#include "SOIL.h"
#include "Texture.h"
#include "TextureManager.h"
#include "Drawable.h"


class Block
{
	Drawable m_quad;
	std::array<Drawable, 4> m_buildings;

public:

	static const float size;
	static const float height;

	Block(const glm::vec3& centre = glm::vec3());

	void draw(const Camera& camera, const DirectionalLight& light);
};