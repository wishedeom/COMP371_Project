#include "Drawable.h"

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


Drawable::Drawable(const std::vector<glm::vec3>& vertices, const std::vector<GLuint>& indices, const glm::vec3& colour, const std::vector<glm::vec2>& textureCoords,
	const Shader& shader, const Texture& texture)
	: m_vertices(vertices)
	, m_indices(indices)
	, m_textureCoords(textureCoords)
	, m_shader(shader)
	, m_texture(texture)
	, m_upToDate(false)
{
	fill(colour);
	generateBuffers();
}


void Drawable::generateBuffers()
{
	// Generate vertex array object, vertex position and colour and element buffer objects
	glGenVertexArrays(1, &m_vaoID);
	glGenBuffers(1, &m_posBuffID);
	glGenBuffers(1, &m_colBuffID);
	glGenBuffers(1, &m_texBuffID);
	glGenBuffers(1, &m_eboID);
}


void Drawable::fillBuffers()
{
	// Bind VAO
	glBindVertexArray(m_vaoID);

	// Put vertex position data into VAO attribute 0
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_posBuffID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices[0]) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(m_vertices[0]), (GLvoid*)0);

	// Put vertex position data into VAO attribute 1
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_colBuffID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_colours[0]) * m_colours.size(), m_colours.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(m_colours[0]), (GLvoid*)0);

	// Put vertex texture coordinate data into VAO attribute 2
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, m_texBuffID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_textureCoords[0]) * m_textureCoords.size(), m_textureCoords.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(m_textureCoords[0]), (GLvoid*)0);

	// Send index data to EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices[0]) * m_indices.size(), m_indices.data(), GL_STATIC_DRAW);

	// Unbind VAO
	glBindVertexArray(0);

	m_upToDate = true;
}


void Drawable::fill(const glm::vec3& colour)
{
	m_upToDate = false;
	for (int i = 0; i < m_vertices.size(); i++)
	{
		m_colours.push_back(colour);
	}
}


void Drawable::draw(const glm::mat4& transformation)
{
	if (!m_upToDate)
	{
		fillBuffers();		// Put position, colour, and texture data into buffers
	}
	m_texture.bind();
	m_shader.use();
	glUniformMatrix4fv(m_shader.transformationMatrixID(), 1, GL_FALSE, glm::value_ptr(transformation));
	glBindVertexArray(m_vaoID);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, (GLvoid*)0);
	glBindVertexArray(0);
}