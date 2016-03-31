#pragma once

#include <vector>

#include "Block.h"
#include "Sun.h"

class World
{
	std::vector<Block> m_blocks;

public:
	World(const int length = 2, const int width = 2);
	void draw(const Camera& camera, const DirectionalLight& light);
};