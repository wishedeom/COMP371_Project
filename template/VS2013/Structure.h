#pragma once
#pragma once
#include <vector>
#include "glm.hpp"

// A Structure represents a single free-standing building with a polygonal base and a certain height.
class Structure
{
	std::vector<glm::vec3> m_vertices;
	std::vector<GLuint> m_indices;
	GLuint vertexArrayObject;
	GLuint vertexBufferObject;
	GLuint elementBufferObject;

	std::pair<std::vector<glm::vec3>, std::vector<GLuint>> computeStructureData(const std::vector<glm::vec2>& baseVertices, const float height);

public:
	Structure(const std::vector<glm::vec2>& baseVertices, const float height);
};