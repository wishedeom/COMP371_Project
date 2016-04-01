#include "World.h"

World::World(const int length, const int width)
{
	for (int x = 1; x <= length; x++)
	{
		for (int y = 1; y <= width; y++)
		{
			m_blocks.push_back(Block(glm::vec3(Block::size * (x - length / 2), Block::size * (y - width / 2), 0.0f)));
		}
	}
}

void World::draw(const Camera& camera, const DirectionalLight& light)
{
	for (auto block : m_blocks)
	{
		block.draw(camera, light);
	}
}