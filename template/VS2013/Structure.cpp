#include "Structure.h"
#include "glm.hpp"
#include "glew.h"
#include <vector>
#include "Sweep.h"
#include <tuple>

Structure::Structure(const std::vector<glm::vec2>& baseVertices, const float height)
{
	std::tie(m_vertices, m_indices) = computeStructureData(baseVertices, height);
}


std::pair<std::vector<glm::vec3>, std::vector<GLuint>> Structure::computeStructureData(const std::vector<glm::vec2>& baseVertices, const float height)
{
	const auto embeddedBaseVertices = embed(baseVertices); // Base polygon, embedded in 3-space

	std::vector<glm::vec3> verticalTrajectory;
	verticalTrajectory.push_back(glm::vec3());
	verticalTrajectory.push_back(glm::vec3(0.0f, 0.0f, height));

	auto vertices = computeTranslationalSweep(embeddedBaseVertices, verticalTrajectory);
	auto indices = computeSweepIndices(embeddedBaseVertices.size(), verticalTrajectory.size());

	return make_pair(vertices, indices);
}


void Structure::generateBuffers()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);
}