#include "World.h"

World::World(const int length, const int width)
{
	for (int x = 1; x <= length; x++)
	{
		for (int y = 1; y <= width; y++)
		{
			m_blocks.push_back(Block(glm::vec3(Block::length * x, Block::width * y, 0.0f)));
		}
	}
}

void World::draw(const Camera& camera)
{
	for (auto block : m_blocks)
	{
		block.draw(camera);
	}
}