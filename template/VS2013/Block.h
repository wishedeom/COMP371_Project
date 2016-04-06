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

// Represents a single city block. Contains a base and four buildings.
class Block
{
	// Creates a single random building from the Block's parameters.
	static Drawable makeBuilding();

	Drawable m_quad;						// Block base
	std::array<Drawable, 4> m_buildings;	// Holds the four buildings

public:

	static const float size;		// Side length of the block
	static const float height;		// Height of the block base
	static const int minSides;		// Minimum number of sides for each building
	static const int maxSides;		// Maximum number of sides for each building
	static const float minRadius;	// Minumum radius of each building
	static const float maxRadius;	// Maximum radius of each building
	static const float minHeight;	// Minimum height of each building
	static const float maxHeight;	// Maximum height of each building

	// Constructs a city block centred at the given point.
	// centre: The centre of the block.
	Block(const glm::vec3& centre = glm::vec3());

	// Draws the block's base and four buildings.
	// camera: From which point of view the block will be drawn.
	// light: The light which will illuminate the block.
	void draw(const Camera& camera, const DirectionalLight& light);
};