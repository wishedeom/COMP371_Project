#include "Structure.h"

// Standard
#include <vector>
#include <tuple>

// Third-party
#include "glew.h"
#include "glm.hpp"
#include "gtc/type_ptr.hpp"
#include "SOIL.h"

// Project
#include "utility.h"
#include "Shader.h"
#include "TextureManager.h"


Shader Structure::shader;	// All Structures use the same shader

GLuint Structure::transformationMatrixID;

Structure::Structure(const std::vector<glm::vec2>& baseVertices, const float height, const glm::vec3& centre, const glm::vec3& colour)
	: texture(randomBuildingTexture())
{
	// Shader is static variable, yet cannot be initialized before GLFW!
	// This ensures the shader is constructed after initialization of GLFW.
	if (!shader.isInitialized())
	{
		shader = Shader("Structure.vs", "Structure.frag");
		transformationMatrixID = shader.transformationMatrixID();
	}

	// Compute vertices and indices of building
	std::tie(m_vertices, m_indices, m_textureCoords) = computeStructureData(baseVertices, height);
	if (centre != glm::vec3())
	{
		m_vertices = translate(m_vertices, centre);
	}
	fill(colour);			// Fill with given colour
	generateBuffers();		// Put position, colour, and texture data into buffers
}


std::tuple<std::vector<glm::vec3>, std::vector<GLuint>, std::vector<glm::vec2>> Structure::computeStructureData(const std::vector<glm::vec2>& baseVertices, const float height)
{
	auto embeddedBaseVertices = embed(baseVertices);			// Base polygon, embedded in 3-space
	embeddedBaseVertices.push_back(embeddedBaseVertices[0]);	// Connect the polygon

	std::vector<glm::vec3> verticalTrajectory;					// Represents height of the building
	verticalTrajectory.push_back(glm::vec3());
	verticalTrajectory.push_back(glm::vec3(0.0f, 0.0f, height));

	const auto vertices = computeTranslationalSweep(embeddedBaseVertices, verticalTrajectory);
	const auto indices = computeSweepIndices(embeddedBaseVertices.size(), verticalTrajectory.size());

	// Wrap texture around...
	std::vector<glm::vec2> textureCoords(vertices.size());
	for (int i = 0; i < vertices.size() / 2; i++)
	{
		textureCoords[i] = glm::vec2(i, 0.0f);
		textureCoords[i + vertices.size() / 2] = glm::vec2(i, height);
	}
	return make_tuple(vertices, indices, textureCoords);
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_textureCoords[0]) * m_textureCoords.size(), m_textureCoords.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(m_textureCoords[0]), (GLvoid*)0);

	// Send index data to EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices[0]) * m_indices.size(), m_indices.data(), GL_STATIC_DRAW);

	// Unbind VAO
	glBindVertexArray(0);
}


void Structure::fill(const glm::vec3& colour)
{
	for (int i = 0; i < m_vertices.size(); i++)
	{
		m_colours.push_back(colour);
	}
}


void Structure::draw(const glm::mat4& transformation) const
{
	texture.bind();
	shader.use();
	glUniformMatrix4fv(transformationMatrixID, 1, GL_FALSE, glm::value_ptr(transformation));
	glBindVertexArray(m_vaoID);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, (GLvoid*)0);
	glBindVertexArray(0);
}