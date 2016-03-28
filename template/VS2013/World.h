#pragma once

#include <vector>

#include "Block.h"
#include "Sun.h"

class World
{
	std::vector<Block> m_blocks;

public:
	World(const int length, const int width);
	void draw(const Camera& camera);
};