#include "Block.h"

								// - STATIC CONSTANTS - //

const float Block::size = 10.0f;
const float Block::height = 0.005;
const int Block::minSides = 3;
const int Block::maxSides = 10;
const float Block::minRadius = 0.5f;
const float Block::maxRadius = 1.0f;
const float Block::minHeight = 0.5f;
const float Block::maxHeight = 10.0f;


								// - MEMBER FUNCTIONS - //

// Constructor
Block::Block(const glm::vec3& centre)
	: m_quad(makeBlockBase(centre, size, height))
{
	// Set material properties
	m_quad.material().texture = getTexture("../Images/block_base.png");
	m_quad.material().ambientColour = { 1.0f, 1.0f, 1.0f };
	m_quad.material().diffuseColour = { 0.0f, 0.0f, 0.0f };
	m_quad.material().specularColour = { 0.0f, 0.0f, 1.0f };
	m_quad.material().shininess = 1.0f;

	// Construct buildings
	const float offset = size / 6;
	m_buildings[0] = makeBuilding().setOrigin(centre + glm::vec3(-offset, -offset, height));
	m_buildings[1] = makeBuilding().setOrigin(centre + glm::vec3(-offset, offset, height));
	m_buildings[2] = makeBuilding().setOrigin(centre + glm::vec3(offset, -offset, height));
	m_buildings[3] = makeBuilding().setOrigin(centre + glm::vec3(offset, offset, height));

	// Construct a rectangular axis-aligned bounding box
	const float boundingOffset = size / 3;
	m_boundingBoxes.push_back(centre + glm::vec3(-boundingOffset, -boundingOffset, height));
	m_boundingBoxes.push_back(centre + glm::vec3(-boundingOffset, boundingOffset, height));
	m_boundingBoxes.push_back(centre + glm::vec3(boundingOffset, -boundingOffset, height));
	m_boundingBoxes.push_back(centre + glm::vec3(boundingOffset, boundingOffset, height));
}


std::vector<glm::vec3>& Block::getBoundingBoxes() { return m_boundingBoxes; }


void Block::draw(const Camera& camera, const DirectionalLight& light)
{
	// Draw the block base
	m_quad.draw(camera, light);

	// Draw the buildings
	for (auto building : m_buildings)
	{
		building.draw(camera, light);
	}
}


Drawable Block::makeBuilding()
{
	const GLuint numTextures = 3;
	GLuint randomTexture = rand() % numTextures + 1;
	auto building = makeRandomRegularPolygonalPrism(minSides, maxSides, minRadius, maxRadius, minHeight, maxHeight);
	building.material().texture = getTexture("../Images/building" + std::to_string(randomTexture) + ".jpg");
	building.material().ambientColour = { 1.0f, 1.0f, 1.0f };
	building.material().diffuseColour = { 1.0f, 0.0f, 0.0f };
	building.material().specularColour = { 0.0f, 0.0f, 1.0f };
	building.material().shininess = 1.0f;
	return building;
}

