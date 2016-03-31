#include "Block.h"

const float Block::width = 1.0f;
const float Block::length = 1.0f;


Block::Block(const glm::vec3& centre)
	: m_quad(makeQuad(length, width, "../Images/block.png"))
{
	m_quad.setOrigin(centre);
	m_buildings[0] = makeRandomRegularPolygonalPrism(10, 0.5f, 2.0f).setOrigin(centre + glm::vec3(-length / 6, -width / 6, 0.0f));
	m_buildings[1] = makeRandomRegularPolygonalPrism(10, 0.5f, 2.0f).setOrigin(centre + glm::vec3(length / 6, -width / 6, 0.0f));
	m_buildings[2] = makeRandomRegularPolygonalPrism(10, 0.5f, 2.0f).setOrigin(centre + glm::vec3(-length / 6, width / 6, 0.0f));
	m_buildings[3] = makeRandomRegularPolygonalPrism(10, 0.5f, 2.0f).setOrigin(centre + glm::vec3(length / 6, width / 6, 0.0f));
}


void Block::draw(const Camera& camera)
{
	m_quad.draw(camera);
	for (auto building : m_buildings)
	{
		building.draw(camera);
	}
}