#include "Block.h"

const float Block::size = 1.0f;
const float Block::height = 0.0125f;
const int Block::maxSides = 10;
const float Block::maxRadius = 0.1f;
const float Block::maxHeight = 1.0f;
const float Block::maxShininess = 10.0f;


Block::Block(const glm::vec3& centre)
	: m_quad(makeBlockBase(centre, size, height).setShininess(1.0f))
{
	const float offset = size / 6;
	m_buildings[0] = makeBuilding().setOrigin(centre + glm::vec3(-offset, -offset, height));
	m_buildings[1] = makeBuilding().setOrigin(centre + glm::vec3(-offset, offset, height));
	m_buildings[2] = makeBuilding().setOrigin(centre + glm::vec3(offset, -offset, height));
	m_buildings[3] = makeBuilding().setOrigin(centre + glm::vec3(offset, offset, height));
}


void Block::draw(const Camera& camera, const DirectionalLight& light)
{
	m_quad.draw(camera, light);
	for (auto building : m_buildings)
	{
		building.draw(camera, light);
	}
}


Drawable Block::makeBuilding()
{
	return makeRandomRegularPolygonalPrism(maxSides, maxRadius, maxHeight)
		.setTexture("../Images/building1.jpg")
		.setAmbientColour(randomColour())
		.setDiffuseColour(randomColour())
		.setSpecularColour(randomColour())
		.setShininess(randomFloat(maxShininess));
}