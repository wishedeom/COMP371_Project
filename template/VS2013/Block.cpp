#include "Block.h"

const float Block::size = 10.0f;
const float Block::height = 0.005;
const int Block::minSides = 3;
const int Block::maxSides = 10;
const float Block::minRadius = 0.5f;
const float Block::maxRadius = 1.0f;
const float Block::minHeight = 0.5f;
const float Block::maxHeight = 10.0f;

Block::Block(const glm::vec3& centre)
	: m_quad(makeBlockBase(centre, size, height))
{
	m_quad.material().texture = getTexture("../Images/block_base.png");
	m_quad.material().ambientColour = { 1.0f, 1.0f, 1.0f };
	m_quad.material().diffuseColour = { 0.0f, 0.0f, 0.0f };
	m_quad.material().specularColour = { 0.0f, 0.0f, 1.0f };
	m_quad.material().shininess = 1.0f;
	const float offset = size / 6;
	m_buildings[0] = makeBuilding().setOrigin(centre + glm::vec3(-offset, -offset, height));
	m_buildings[1] = makeBuilding().setOrigin(centre + glm::vec3(-offset, offset, height));
	m_buildings[2] = makeBuilding().setOrigin(centre + glm::vec3(offset, -offset, height));
	m_buildings[3] = makeBuilding().setOrigin(centre + glm::vec3(offset, offset, height));


	const float boundingOffset = size/3;

	//m_boundingBoxes is 4 points, so basically a square in a 2D plane
	//the idea is to use this square as bounding box in PlayerController.isOutsideBoundingBox

	m_boundingBoxes.push_back(centre + glm::vec3(-boundingOffset, -boundingOffset, height));
	m_boundingBoxes.push_back(centre + glm::vec3(-boundingOffset, boundingOffset, height));
	m_boundingBoxes.push_back(centre + glm::vec3(boundingOffset, -boundingOffset, height));
	m_boundingBoxes.push_back(centre + glm::vec3(boundingOffset, boundingOffset, height));
}

std::vector<glm::vec3> Block::getBoundingBoxes(){
	return m_boundingBoxes;
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
<<<<<<< HEAD
	auto building = makeRandomRegularPolygon(minSides, maxSides, minRadius, maxRadius, minHeight, maxHeight);
	building.material().texture = getTexture("../Images/building1.jpg");
=======
	const GLuint numTextures = 3;
	GLuint randomTexture = rand() % numTextures + 1;
	auto building = makeRandomRegularPolygonalPrism(minSides, maxSides, minRadius, maxRadius, minHeight, maxHeight);
	building.material().texture = getTexture("../Images/building" + std::to_string(randomTexture) + ".jpg");
>>>>>>> refs/remotes/origin/master
	building.material().ambientColour = { 1.0f, 1.0f, 1.0f };
	building.material().diffuseColour = { 1.0f, 0.0f, 0.0f };
	building.material().specularColour = { 0.0f, 0.0f, 1.0f };
	building.material().shininess = 1.0f;
	return building;
}

