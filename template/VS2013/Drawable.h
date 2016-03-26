#pragma once

// Standard
#include <vector>
#include <tuple>

// Third-party
#include "glew.h"
#include "glm.hpp"
#include "SOIL.h"

// Project
#include "utility.h"
#include "Shader.h"
#include "TextureManager.h"


// A Drawable represents a single free-standing building with a polygonal base and a certain height.
class Drawable
{	
	std::vector<glm::vec3> m_vertices;		// The structure's vertex coordinates
	std::vector<glm::vec3> m_colours;		// The colour of each vertex
	std::vector<glm::vec2> m_textureCoords;	// The texture coordinates of each vertex
	std::vector<GLuint> m_indices;			// The indices to draw the structure as triangles

	Texture m_texture;
	Shader m_shader;

	GLuint m_vaoID;			// Vertex array object
	GLuint m_posBuffID;		// Vertex position buffer object
	GLuint m_colBuffID;		// Vertex colour buffer object
	GLuint m_texBuffID;		// Vertex texture buffer object
	GLuint m_eboID;			// Element buffer object, for vertex draw indices

	bool m_upToDate; // True if and only if all buffers are up-to-date

	
	// Generates and initializes the VAO, VBO, and EBO for drawing the structure.
	void generateBuffers();


	// Fills buffers
	void fillBuffers();


	// Fills the structure with a constant colour
	void fill(const glm::vec3& colour);


public:

	// Constructs a structure with a polygonal base and a constant height.
	// baseVertices: The vertices of the base polygon.
	// height: The height of the structure.
	Drawable(const std::vector<glm::vec3>& vertices = std::vector<glm::vec3>(), const std::vector<GLuint>& indices = std::vector<GLuint>(),
		const glm::vec3& colour = glm::vec3(), const std::vector<glm::vec2>& textureCoords = std::vector<glm::vec2>(),
		const Shader& shader = Shader(), const Texture& texture = Texture());


	// Draws the structure.
	virtual void draw(const glm::mat4& transformation);
};