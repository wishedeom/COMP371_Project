#include "Structure.h"
#include "utility.h"

#include "glm.hpp"
#include "glew.h"
#include "SOIL.h"

#include <vector>
#include <tuple>


const GLuint Structure::textureID = SOIL_load_OGL_texture("building.jpg", 0, 0, 0);


Structure::Structure(const std::vector<glm::vec2>& baseVertices, const float height, const glm::vec3& colour)
{
	std::tie(m_vertices, m_indices) = computeStructureData(baseVertices, height); // Compute vertices and indices of building
	textureFill();		// Fill with texture coordinates
	fill(colour);		// Fill with given colour
	generateBuffers();	// Put position, colour, and texture data into buffers
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
	// Generate vertex array object, vertex position and colour and element buffer objects
	glGenVertexArrays(1, &m_vaoID);
	glGenBuffers(1, &m_positionBufferID);
	glGenBuffers(1, &m_colourBufferID);
	glGenBuffers(1, &m_texBufferID);
	glGenBuffers(1, &m_eboID);

	// Bind VAO
	glBindVertexArray(m_vaoID);

	// Put vertex position data into VAO attribute 0
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_positionBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices[0]) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(m_vertices[0]), (GLvoid*)0);

	// Put vertex position data into VAO attribute 1
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_colourBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_colours[0]) * m_colours.size(), m_colours.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(m_colours[0]), (GLvoid*)0);

	// Put vertex texture coordinate data into VAO attribute 2
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, m_texBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_textures[0]) * m_textures.size(), m_textures.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(m_colours[0]), (GLvoid*)0);

	// Send index data to EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices[0]) * m_indices.size(), m_indices.data(), GL_STATIC_DRAW);

	// Unbind VAO
	glBindVertexArray(0);
}


void Structure::textureFill()
{
	for (const auto vertex : m_vertices)
	{
		m_textures.push_back(glm::vec2(vertex.x, vertex.z));
	}
}


void Structure::fill(const glm::vec3& colour)
{
	for (int i = 0; i < m_vertices.size(); i++)
	{
		m_colours.push_back(colour);
	}
}


void Structure::draw() const
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBindVertexArray(m_vaoID);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, (GLvoid*)0);
	glBindVertexArray(0);
}