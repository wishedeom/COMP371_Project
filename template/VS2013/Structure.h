#pragma once
#pragma once
#include <vector>
#include "glm.hpp"

// A Structure represents a single free-standing building with a polygonal base and a certain height.
class Structure
{
	std::vector<glm::vec2> m_baseVertices;
	double m_height;

public:
	Structure(const std::vector<glm::vec2>& baseVertices, const double height);
};