#pragma once

// Standard
#include <vector>
#include <tuple>

// Third-party
#include "glm.hpp"
#include "glew.h"
#include "SOIL.h"

// Project
#include "utility.h"
#include "Shader.h"
#include "TextureManager.h"


// A Structure represents a single free-standing building with a polygonal base and a certain height.
// Temporary working-place, should be merged with Building
class Structure
{

	static Shader shader;					// All Structures use the same shader
	static GLuint transformationMatrixID;	// The location of the transformation matrix in the shader program

	// Computes vertices and indices to draw a structure with a polygonal base and a constant height.
	// baseVertices: The vertices of the base polygon.
	// height: The height of the structure.
	static std::tuple<std::vector<glm::vec3>, std::vector<GLuint>, std::vector<glm::vec2>> computeStructureData(const std::vector<glm::vec2>& baseVertices, const float height);

	
	std::vector<glm::vec3> m_vertices;		// The structure's vertex coordinates
	std::vector<GLuint> m_indices;			// The indices to draw the structure as triangles
	std::vector<glm::vec3> m_colours;		// The colour of each vertex
	std::vector<glm::vec2> m_textureCoords;	// The texture coordinates of each vertex

	const Texture& texture;					// Holds the Structure's texture

	GLuint m_vaoID;							// Vertex array object
	GLuint m_positionBufferID;				// Vertex position buffer object
	GLuint m_colourBufferID;				// Vertex colour buffer object
	GLuint m_texBufferID;					// Vertex texture buffer object
	GLuint m_eboID;							// Element buffer object

	
	// Generates and initializes the VAO, VBO, and EBO for drawing the structure.
	void generateBuffers();


	// Fills the structure with a constant colour
	void fill(const glm::vec3& colour);


public:

	// Constructs a structure with a polygonal base and a constant height.
	// baseVertices: The vertices of the base polygon.
	// height: The height of the structure.
	Structure(const std::vector<glm::vec2>& baseVertices, const float height, const glm::vec3& centre = glm::vec3(), const glm::vec3& colour = randomColour());


	// Draws the structure.
	void draw(const glm::mat4& transformation) const;
};