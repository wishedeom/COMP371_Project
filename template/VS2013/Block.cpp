#include "Block.h"

const float Block::size = 10.0f;
const float Block::height = 0.00125f;
const int Block::minSides = 3;
const int Block::maxSides = 10;
const float Block::minRadius = 0.5f;
const float Block::maxRadius = 1.0f;
const float Block::minHeight = 0.5f;
const float Block::maxHeight = 1.0f;


Block::Block(const glm::vec3& centre)
	: m_quad(makeBlockBase(centre, size, height))
{
	m_quad.material().texture = getTexture("../Images/block_base.png");
	m_quad.material().shininess = 1.0f;
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
	auto building = makeRandomRegularPolygonalPrism(minSides, maxSides, minRadius, maxRadius, minHeight, maxHeight);
	building.material().texture = getTexture("../Images/building1.jpg");
	building.material().ambientColour = randomColour();
	building.material().diffuseColour = randomColour();
	building.material().specularColour = randomColour();
	building.material().shininess = 1.0f;
	return building;
}