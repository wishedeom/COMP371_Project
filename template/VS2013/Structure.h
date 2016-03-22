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

	std::vector<glm::vec3> m_vertices;
	std::vector<GLuint> m_indices;
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_EBO;

	// Initializes the VAO, VBO, and EBO for drawing the structure.
	void generateBuffers();

public:

	// Constructs a structure with a polygonal base and a constant height.
	// baseVertices: The vertices of the base polygon.
	// height: The height of the structure.
	Structure(const std::vector<glm::vec2>& baseVertices, const float height);
};