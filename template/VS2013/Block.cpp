#include "Block.h"

Shader Block::shader;
GLuint Block::transformationMatrixID;

const float Block::width = 20.0f;
const float Block::length = 20.0f;


Block::Block(const glm::vec3& centre)
	: roadTexture(getTexture("../Images/road.png"))
	, sidewalkGrassTexture(getTexture("../Images/sidewalk.png"))
{
	if (!shader.isInitialized())
	{
		shader = Shader("../Source/Block.vs", "../Source/Block.frag");
		transformationMatrixID = shader.transformationMatrixID();
	}
	m_vertices.push_back(centre + glm::vec3(-length / 2, -width / 2, 0.0f));
	m_vertices.push_back(centre + glm::vec3(-length / 2, width / 2, 0.0f));
	m_vertices.push_back(centre + glm::vec3(length / 2, width / 2, 0.0f));
	m_vertices.push_back(centre + glm::vec3(length / 2, -width / 2, 0.0f));
	
	m_indices.push_back(0);
	m_indices.push_back(1);
	m_indices.push_back(2);
	m_indices.push_back(0);
	m_indices.push_back(2);
	m_indices.push_back(3);

	m_textureCoords.push_back(glm::vec2(0.0f, 0.0f));
	m_textureCoords.push_back(glm::vec2(1.0f, 0.0f));
	m_textureCoords.push_back(glm::vec2(1.0f, 1.0f));
	m_textureCoords.push_back(glm::vec2(0.0f, 1.0f));

	generateBuffers();
}


void Block::generateBuffers()
{
	// Generate vertex array object, vertex position and colour and element buffer objects
	glGenVertexArrays(1, &m_vaoID);
	glGenBuffers(1, &m_positionBufferID);
	glGenBuffers(1, &m_texBufferID);
	glGenBuffers(1, &m_eboID);

	// Bind VAO
	glBindVertexArray(m_vaoID);

	// Put vertex position data into VAO attribute 0
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_positionBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices[0]) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(m_vertices[0]), (GLvoid*)0);

	// Put vertex texture coordinate data into VAO attribute 1
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_texBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_textureCoords[0]) * m_textureCoords.size(), m_textureCoords.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(m_textureCoords[0]), (GLvoid*)0);

	// Send index data to EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices[0]) * m_indices.size(), m_indices.data(), GL_STATIC_DRAW);

	// Unbind VAO
	glBindVertexArray(0);
}


void Block::draw(const glm::mat4& transformation)
{
	sidewalkGrassTexture.bind();
	shader.use();
	glUniformMatrix4fv(transformationMatrixID, 1, GL_FALSE, glm::value_ptr(transformation));
	glBindVertexArray(m_vaoID);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}