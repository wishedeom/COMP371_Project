#include "utility.h"
#include "GLM/GTC/matrix_transform.hpp"


// The translational sweep is made from a profile polyline with p vertices and a trajectory polyline with t vertices, for a total of p * t vertices. The sweep itself
// consists of (p - 1) * (t - 1) recangles, paramaterized from 0 to p - 2 along the profile curve and from 0 to t - 2 along the trajectory curve. Since the
// vertices are numbered starting from 0 and increasing along the profile curve, then the trajectory curve, the vertex indices for the four vertices of rectange (i, j) are
// as follows.
//
//		 upper left (UL)		  upper right (UR)
//		(i + (j + 1) * p)		(i + (j + 1) * p + 1)
//				*----------<------------*
//				|                   /	|
//				|                /		|
//				|             /			|
//				|          ^			|
//				|        /			    ^
//				|     /					|
//				|  /					|
//				*----------->-----------*
//			(i + j * p)			(i + p * j + 1)
//		  lower left (LL)		lower right (LR)
//
// The vertices for the triangles to draw are
//
//		LL -> LR -> UR
//			then
//		LL -> UR -> UL
//
// This is done for each rectangle of the translational sweep mesh.
std::vector<GLuint> computeSweepIndices(const int p, const int t)
{
	static std::vector<GLuint> indices;
	for (int i = 0; i < p - 1; i++)
	{
		for (int j = 0; j < t - 1; j++)
		{
			// Vertices of rectangle (i, j)
			const GLuint lowerLeft = i + j	* p;
			const GLuint lowerRight = i + j	* p + 1;
			const GLuint upperLeft = i + (j + 1) * p;
			const GLuint upperRight = i + (j + 1) * p + 1;

			// Lower triangle
			indices.push_back(lowerLeft);
			indices.push_back(lowerRight);
			indices.push_back(upperRight);

			// Upper triangle
			indices.push_back(lowerLeft);
			indices.push_back(upperRight);
			indices.push_back(upperLeft);
		}
	}
	return indices;
}


std::vector<glm::vec3> computeDisplacements(const std::vector<glm::vec3>& polyline)
{

	std::vector<glm::vec3> displacements;	// To hold displacement vectors
	const auto firstVertex = polyline[0];	// First vertex in polyline
	for (auto vertex : polyline)
	{
		displacements.push_back(vertex - firstVertex);	// Compute the displacement from the first vertex to each vertex of the polyline,
														//and push that onto the vector of displacements.
	}
	return displacements;
}


std::vector<glm::vec3> computeTranslationalSweep(const std::vector<glm::vec3>& profilePolyline, const std::vector<glm::vec3>& trajectoryPolyline)
{
	const auto trajectoryCurveDisplacements = computeDisplacements(trajectoryPolyline);	// Compute trajectory curve displacements.
	std::vector<glm::vec3> translationalSweep;	// To hold translational sweep vertices.
	for (auto displacement : trajectoryCurveDisplacements)
	{
		for (auto profileVertex : profilePolyline)
		{
			// Iterate through the trajectory curve displacement vectors and translate each profile polyline vertex.
			translationalSweep.push_back(profileVertex + displacement);
		}
	}
	return translationalSweep;
}


std::vector<glm::vec3> rotatePolyline(const std::vector<glm::vec3>& polyline, const GLfloat angle)
{
	const auto rotationMatrix = glm::rotate(glm::mat4(1.0), angle, up);
	std::vector<glm::vec3> rotatedPolyline;
	for (auto vertex : polyline)
	{
		rotatedPolyline.push_back(glm::vec3(rotationMatrix * glm::vec4(vertex, 0.0)));
	}
	return rotatedPolyline;
}


std::vector<glm::vec3> computeRotationalSweep(const std::vector<glm::vec3>& profilePolyline, const int numSpans)
{
	const GLfloat angle = 2 * pi / numSpans;
	std::vector<glm::vec3> rotationalSweep;
	for (int i = 0; i <= numSpans + 1; i++)
	{
		auto rotatedPolyline = rotatePolyline(profilePolyline, angle * i);
		for (auto vertex : rotatedPolyline)
		{
			rotationalSweep.push_back(vertex);
		}
	}
	return rotationalSweep;
}


std::vector<glm::vec3> embed(const std::vector<glm::vec2>& vertices)
{
	std::vector<glm::vec3> embeddedVertices;
	for (const auto vertex : vertices)
	{
		embeddedVertices.push_back(glm::vec3(vertex, 0.0f));
	}
	return embeddedVertices;
}


std::vector<glm::vec2> regularPolygon(const int sides, const float apothem)
{
	// Triangle is the polygon with least number of sides
	if (sides < 3)
	{
		throw std::logic_error("A polygon must have at least 3 sides.");
	}
	const float angle = 2 * pi / sides;		// Central angle between successive pairs of vertices
	auto rotMatrix = glm::rotate(id4, angle, up);
}