#include "Structure.h"
#include "Sweep.h"

#include "glm.hpp"
#include "glew.h"

#include <vector>
#include <tuple>


Structure::Structure(const std::vector<glm::vec2>& baseVertices, const float height)
{
	std::tie(m_vertices, m_indices) = computeStructureData(baseVertices, height);	// Compute vertices and indices of building
	generateBuffers();	// Put into buffers
}


std::pair<std::vector<glm::vec3>, std::vector<GLuint>> Structure::computeStructureData(const std::vector<glm::vec2>& baseVertices, const float height)
{
	auto embeddedBaseVertices = embed(baseVertices);			// Base polygon, embedded in 3-space
	embeddedBaseVertices.push_back(embeddedBaseVertices[0]);	// Connect the polygon

	std::vector<glm::vec3> verticalTrajectory;					// Represents height of the building
	verticalTrajectory.push_back(glm::vec3());
	verticalTrajectory.push_back(glm::vec3(0.0f, 0.0f, height));

	auto vertices = computeTranslationalSweep(embeddedBaseVertices, verticalTrajectory);
	auto indices = computeSweepIndices(embeddedBaseVertices.size(), verticalTrajectory.size());

	return make_pair(vertices, indices);
}


void Structure::generateBuffers()
{
	// Generate vertex array object and vertex and element buffer objects
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	// Bind VAO
	glBindVertexArray(m_VAO);

	// Send vertex data to VAO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices[0]) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);

	// Send index data to VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices[0]) * m_indices.size(), m_indices.data(), GL_STATIC_DRAW);

	// Initialize vertex attribute pointer and enable VAO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Unbind VAO
	glBindVertexArray(0);
}


void Structure::draw() const
{
	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, (GLvoid*)0);
	glBindVertexArray(0);
}