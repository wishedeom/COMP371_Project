#include "Block.h"

const float Block::size = 1.0f;
const float Block::height = 0.0125f;


Block::Block(const glm::vec3& centre)
	: m_quad(makeBlockBase(centre, size, height, "../Images/block_base.png"))
{
	const float offset = size / 6;
	const int maxSides = 10;
	const float maxRadius = 0.1f;
	const float maxHeight = 1.0f;
	m_buildings[0] = makeRandomRegularPolygonalPrism(maxSides, maxRadius, maxHeight).setOrigin(centre + glm::vec3(-offset, -offset, height));
	m_buildings[1] = makeRandomRegularPolygonalPrism(maxSides, maxRadius, maxHeight).setOrigin(centre + glm::vec3(-offset, offset, height));
	m_buildings[2] = makeRandomRegularPolygonalPrism(maxSides, maxRadius, maxHeight).setOrigin(centre + glm::vec3(offset, -offset, height));
	m_buildings[3] = makeRandomRegularPolygonalPrism(maxSides, maxRadius, maxHeight).setOrigin(centre + glm::vec3(offset, offset, height));
}


void Block::draw(const Camera& camera, const DirectionalLight& light)
{
	m_quad.draw(camera, light);
	for (auto building : m_buildings)
	{
		building.draw(camera, light);
	}
}