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


Drawable::Drawable()
	: m_upToDate(false)
	, m_everFilled(false)
{
	generateBuffers();
}


void Drawable::generateBuffers()
{
	// Generate vertex array object, vertex position and colour and element buffer objects
	glGenVertexArrays(1, &m_vaoID);
	glGenBuffers(1, &m_vboID);
	glGenBuffers(1, &m_eboID);
}

// Only called by draw()
void Drawable::fillBuffers()
{
	// VAO is already bound in draw()

	// Bind vertex data to VBO
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
	if (m_everFilled)
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices[0]) * m_vertices.size(), nullptr, GL_STATIC_DRAW);	// Invalidate old data, if there is old data to invalidate
	}
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices[0]) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);

	// Bind index data to EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboID);
	if (m_everFilled)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices[0]) * m_indices.size(), nullptr, GL_STATIC_DRAW); // Invalidate old data, if there is old data to invalidate
	}
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_indices[0]) * m_indices.size(), m_indices.data(), GL_STATIC_DRAW);

	// Point VAO attribute 0 to vertex position data
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(m_vertices[0]), (GLvoid*)0);

	// Point VAO attribute 1 to vertex normal data
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(m_vertices[0]), (GLvoid*)offsetof(Vertex, normal));

	// Point VAO attribute 2 to vertex texture coordinate data
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(m_vertices[0]), (GLvoid*)offsetof(Vertex, texCoords));


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Proceed to draw()

	m_upToDate = true;
	if (!m_everFilled)
	{
		m_everFilled = true;
	}
}


Drawable& Drawable::setOrigin(const glm::vec3& origin)
{
	m_origin = origin;
	m_modelMatrix = glm::translate(id4, origin);
	return *this;
}


glm::vec3 Drawable::origin() const { return m_origin; }


glm::mat4 Drawable::modelMatrix() const { return m_modelMatrix; }


Drawable& Drawable::setVertices(const std::vector<Vertex>& vertices)
{
	m_upToDate = false;
	m_vertices = vertices;
	return *this;
}


Drawable& Drawable::setIndices(const std::vector<GLuint> indices)
{
	m_upToDate = false;
	m_indices = indices;
	return *this;
}


Material& Drawable::material() { return m_material; }


void Drawable::draw(const Camera& camera, const DirectionalLight& light)
{
	glBindVertexArray(m_vaoID);

	// If buffers are not up to date, fill with position, normal, texture, and index data
	if (!m_upToDate)
	{
		fillBuffers();
	}
	
	// Use the directional light shader
	light.UseShader();

	// Bind the object's texture to the "texture" uniform in the shader
	m_material.texture.bind();

	// Send the material properties of the object to the shader
	glUniform3fv(glGetUniformLocation(light.getShader().programID(), "material.ambient"), 1, glm::value_ptr(m_material.ambientColour));
	glUniform3fv(glGetUniformLocation(light.getShader().programID(), "material.diffuse"), 1, glm::value_ptr(m_material.diffuseColour));
	glUniform3fv(glGetUniformLocation(light.getShader().programID(), "material.specular"), 1, glm::value_ptr(m_material.specularColour));
	glUniform1f(glGetUniformLocation(light.getShader().programID(), "material.shininess"), m_material.shininess);

	// Send the transformation matrices to the shader
	glUniformMatrix4fv(light.getShader().projMatrixID(), 1, GL_FALSE, glm::value_ptr(camera.projection()));
	glUniformMatrix4fv(light.getShader().viewMatrixID(), 1, GL_FALSE, glm::value_ptr(camera.view()));
	glUniformMatrix4fv(light.getShader().modelMatrixID(), 1, GL_FALSE, glm::value_ptr(m_modelMatrix));

	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Bind the VAO, and draw the mesh
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, (GLvoid*)0);
	Texture::unbind();
	glBindVertexArray(0);
}