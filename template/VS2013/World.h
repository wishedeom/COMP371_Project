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
	World(const int length = 2, const int width = 2);
	void draw(const Camera& camera, const DirectionalLight& light);
	std::vector<glm::vec3> getBoundingBoxVector();
	std::vector<Block> getBlocks();
};