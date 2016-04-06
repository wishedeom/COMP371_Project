#pragma once

#include <vector>
#include "glew.h"
#include "glm.hpp"
#include "glfw3.h"

#include "Block.h"

// Represents the entire city.
class World
{

	std::vector<Block> m_blocks;				// Holds all of the city's blocks
	std::vector<glm::vec3> boundingBoxVector;	// Holds the extreme coordinates of the city's bounding box

public:

	const int size;	// The size of the city

	// Constructs a city with a given side length, in blocks
	World(const int aSize);

	// Draws the city.
	// camera: The camera that is seeing the city.
	// light: The light that is illuminating the city.
	void draw(const Camera& camera, const DirectionalLight& light);

	// Returns the bounding box coordinates.
	std::vector<glm::vec3> getBoundingBoxVector();

	// Returns the blocks of the city.
	std::vector<Block>& getBlocks();
};