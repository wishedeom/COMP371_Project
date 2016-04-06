#include "World.h"

World::World(const int aSize)
	: size(aSize)
{
	for (float x = 1.0f; x <= size; x++)
	{
		for (float y = 1.0f; y <= size; y++)
		{
			m_blocks.push_back(Block(glm::vec3(Block::size * (x - size / 2), Block::size * (y - size / 2), 0.0f)));
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

