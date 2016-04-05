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
	static Drawable makeBuilding();
	Drawable m_quad;
	std::array<Drawable, 4> m_buildings;
	std::vector<glm::vec3> m_boundingBoxes;
	
	
public:
	std::vector<glm::vec3> getBoundingBoxes();
	static const float size;
	static const float height;
	static const int minSides;
	static const int maxSides;
	static const float minRadius;
	static const float maxRadius;
	static const float minHeight;
	static const float maxHeight;

	Block(const glm::vec3& centre = glm::vec3());

	void draw(const Camera& camera, const DirectionalLight& light);
};