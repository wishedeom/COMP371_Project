#pragma once

#include <vector>

#include "Block.h"
#include "Sun.h"
#include "Building.h"

class World
{
	vector<Block> m_blocks;

public:
	World(const int length, const int width);
	void draw(const Camera& camera);
};