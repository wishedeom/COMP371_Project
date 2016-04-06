#include "World.h"

World::World(const int length, const int width)
{
	for (float x = 1.0f; x <= length; x++)
	{
		for (float y = 1.0f; y <= width; y++)
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

std::vector<glm::vec3> World::getBoundingBoxVector(){
	return boundingBoxVector;
}

std::vector<Block>& World::getBlocks() { return m_blocks; }

