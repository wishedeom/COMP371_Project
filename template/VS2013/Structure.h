#pragma once
#pragma once
#include <vector>
#include "glm.hpp"
#include "glew.h"

// A Structure represents a single free-standing building with a polygonal base and a certain height.
class Structure
{
	// Computes vertices and indices to draw a structure with a polygonal base and a constant height.
	// baseVertices: The vertices of the base polygon.
	// height: The height of the structure.
	static std::pair<std::vector<glm::vec3>, std::vector<GLuint>> computeStructureData(const std::vector<glm::vec2>& baseVertices, const float height);

	
	std::vector<glm::vec3> m_vertices;	// The structure's vertex coordinates
	std::vector<GLuint> m_indices;		// The indices to draw the structure as triangles
	GLuint m_VAO;						// Vertex array object
	GLuint m_VBO;						// Vertex buffer object
	GLuint m_EBO;						// Element buffer object

	
	// Generates and initializes the VAO, VBO, and EBO for drawing the structure.
	void generateBuffers();


public:

	// Constructs a structure with a polygonal base and a constant height.
	// baseVertices: The vertices of the base polygon.
	// height: The height of the structure.
	Structure(const std::vector<glm::vec2>& baseVertices, const float height);


	// Draws the structure.
	void draw() const;
};