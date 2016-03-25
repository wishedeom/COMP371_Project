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

	Texture texture;
	static Shader shader;

public:

	static GLuint viewMatrixID;		// HIDE LATER
	static GLuint modelMatrixID;
	static GLuint projMatrixID;

private:

	// Computes vertices and indices to draw a structure with a polygonal base and a constant height.
	// baseVertices: The vertices of the base polygon.
	// height: The height of the structure.
	static std::tuple<std::vector<glm::vec3>, std::vector<GLuint>, std::vector<glm::vec2>> computeStructureData(const std::vector<glm::vec2>& baseVertices, const float height);

	
	std::vector<glm::vec3> m_vertices;		// The structure's vertex coordinates
	std::vector<GLuint> m_indices;			// The indices to draw the structure as triangles
	std::vector<glm::vec3> m_colours;		// The colour of each vertex
	std::vector<glm::vec2> m_textureCoords;	// The texture coordinates of each vertex

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

	// Constructs a random structure.
	// maxSides: The maximum number of sides the structure can have. Must be at least 3.
	// maxApothem: The maximum size of the apothem the structure can have. Must be positive.
	// maxHeight: The maximum height of the structure. Must be positive.
	static Structure randomStructure(const int maxSides, const float maxApothem, const float maxHeight, const glm::vec3& centre = glm::vec3());


	// Constructs a structure with a polygonal base and a constant height.
	// baseVertices: The vertices of the base polygon.
	// height: The height of the structure.
	Structure(const std::vector<glm::vec2>& baseVertices, const float height, const glm::vec3& centre = glm::vec3(), const glm::vec3& colour = randomColour());


	// Draws the structure.
	void draw() const;
};