#pragma once

#include <vector>
#include "glew.h"
#include "glm.hpp"
#include "glfw3.h"

#include "Block.h"

class World
{
	std::vector<Block> m_blocks;
	std::vector<glm::vec3> boundingBoxVector;
public:
	World(const int aSize);
	void draw(const Camera& camera, const DirectionalLight& light);
	std::vector<glm::vec3> getBoundingBoxVector();
	std::vector<Block>& getBlocks();
	const int size;
};