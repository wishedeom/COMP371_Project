#include "Drawable.h"

// Standard
#include <vector>
#include <tuple>

// Third-party
#include "glew.h"
#include "glm.hpp"
#include "gtc/type_ptr.hpp"
#include "gtc/matrix_transform.hpp"
#include "SOIL.h"

// Project
#include "utility.h"
#include "Shader.h"
#include "TextureManager.h"


Drawable::Drawable(const std::vector<glm::vec3>& vertices, const std::vector<GLuint>& indices, const std::vector<glm::vec3>& normals, const std::vector<glm::vec2>& textureCoords,
	const glm::vec3& origin, const std::string& diffuseTexturePath,	const float shininess)
	: m_vertices(vertices)
	, m_indices(indices)
	, m_textureCoords(textureCoords)
	, m_normals(normals)
	, m_texture(getTexture(diffuseTexturePath))
	, m_ambientColour(1.0f)
	, m_diffuseColour(1.0f)
	, m_specularColour(1.0f)
	, m_shininess(shininess)
	, m_upToDate(false)
{
	setOrigin(origin);
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
	glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);	// Invalidate old data
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices[0]) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(m_vertices[0]), (GLvoid*)0);

	// Put vertex normal data into VAO attribute 1
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_colBuffID);
	glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW); // Invalidate old data
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_normals[0]) * m_normals.size(), m_normals.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(m_normals[0]), (GLvoid*)0);

	// Put vertex texture coordinate data into VAO attribute 2
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, m_texBuffID);
	glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW); // Invalidate old data
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_textureCoords[0]) * m_textureCoords.size(), m_textureCoords.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(m_textureCoords[0]), (GLvoid*)0);

	// Send index data to EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW); // Invalidate old data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices[0]) * m_indices.size(), m_indices.data(), GL_STATIC_DRAW);

	// Unbind VAO
	glBindVertexArray(0);

	m_upToDate = true;
}


//void Drawable::fill(const glm::vec3& colour)
//{
//	m_upToDate = false;
//	for (int i = 0; i < m_vertices.size(); i++)
//	{
//		m_colours.push_back(colour);
//	}
//}


Drawable& Drawable::setOrigin(const glm::vec3& origin)
{
	m_origin = origin;
	m_modelMatrix = glm::translate(id4, origin);
	return *this;
}


glm::vec3 Drawable::origin() const { return m_origin; }


glm::mat4 Drawable::modelMatrix() const { return m_modelMatrix; }


Drawable& Drawable::setVertices(const std::vector<glm::vec3> vertices)
{
	m_upToDate = false;
	m_vertices = vertices;
	return *this;
}


Drawable& Drawable::setNormals(const std::vector<glm::vec3> normals)
{
	m_upToDate = false;
	m_normals = normals;
	return *this;
}


Drawable& Drawable::setTextureCoords(const std::vector<glm::vec2> textureCoords)
{
	m_upToDate = false;
	m_textureCoords = textureCoords;
	return *this;
}


Drawable& Drawable::setIndices(const std::vector<GLuint> indices)
{
	m_upToDate = false;
	m_indices = indices;
	return *this;
}


Drawable& Drawable::setAmbientColour(const glm::vec3& ambientColour)
{
	m_ambientColour = ambientColour;
	return *this;
}


Drawable& Drawable::setDiffuseColour(const glm::vec3& diffuseColour)
{
	m_diffuseColour = diffuseColour;
	return *this;
}


Drawable& Drawable::setSpecularColour(const glm::vec3& specularColour)
{
	m_specularColour = specularColour;
	return *this;
}


Drawable& Drawable::setShininess(const float shininess)
{
	m_shininess = shininess;
	return *this;
}


Drawable& Drawable::setTexture(const std::string& path)
{
	return setTexture(getTexture(path));
}

Drawable& Drawable::setTexture(const Texture& texture)
{
	m_texture = texture;
	return *this;
}


void Drawable::draw(const Camera& camera, const DirectionalLight& light)
{
	// If buffers are not up to date, fill with position, normal, texture, and index data
	if (!m_upToDate)
	{
		fillBuffers();
	}
	
	// Use the directional light shader
	light.UseShader();

	// Bind the object's texture to the "texture" uniform in the shader
	m_texture.bind();

	// Send the material properties of the object to the shader
	glUniform3fv(glGetUniformLocation(light.getShader().programID(), "material.ambient"), 1, glm::value_ptr(m_ambientColour));
	glUniform3fv(glGetUniformLocation(light.getShader().programID(), "material.diffuse"), 1, glm::value_ptr(m_diffuseColour));
	glUniform3fv(glGetUniformLocation(light.getShader().programID(), "material.specular"), 1, glm::value_ptr(m_specularColour));
	glUniform1f(glGetUniformLocation(light.getShader().programID(), "material.shininess"), m_shininess);

	// Send the transformation matrices to the shader
	glUniformMatrix4fv(light.getShader().projMatrixID(), 1, GL_FALSE, glm::value_ptr(camera.projection()));
	glUniformMatrix4fv(light.getShader().viewMatrixID(), 1, GL_FALSE, glm::value_ptr(camera.view()));
	glUniformMatrix4fv(light.getShader().modelMatrixID(), 1, GL_FALSE, glm::value_ptr(m_modelMatrix));

	// Bind the VAO, and draw the mesh
	glBindVertexArray(m_vaoID);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, (GLvoid*)0);
	glBindVertexArray(0);

	m_texture.unbind();
}