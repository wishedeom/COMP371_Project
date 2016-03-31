#include "utility.h"

#include <vector>

#include "glfw3.h"
#include "glm.hpp"
#include "GLM/GTC/matrix_transform.hpp"

#include "TextureManager.h"
#include "Drawable.h"


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


std::vector<glm::vec2> makeRegularPolygon(const int sides, const float radius)
{
	// Triangle is the polygon with least number of sides
	if (sides < 3)
	{
		throw std::logic_error("A polygon must have at least 3 sides.");
	}
	const float angle = 2 * pi / sides;						// Central angle between successive pairs of vertices
	const auto rotMatrix = glm::rotate(id4, angle, up);		// To rotate our first vertex through each vertex of the polygon
	std::vector<glm::vec2> vertices;						// To hold the vertices
	glm::vec2 vertex(radius, 0.0f);						// First vertex
	
	// Construct the polygon
	for (int i = 1; i <= sides; i++)
	{
		vertices.push_back(vertex);
		// Must embed vec2 in 3D projective space, mutliply to rotate, then project to 2-space.
		vertex = glm::vec2(rotMatrix * glm::vec4(vertex, 0.0f, 1.0f));
	}
	
	return vertices;
}


std::vector<glm::vec2> randomRegularPolygon(const int maxSides, const float maxRadius)
{
	const int sides = std::rand() % (maxSides - 2) + 3;
	const float radius = maxRadius * std::rand() / RAND_MAX;
	return makeRegularPolygon(sides, radius);
}


std::vector<glm::vec2> transformPolygon(const std::vector<glm::vec2>& polygon, const glm::mat4& matrix)
{
	std::vector<glm::vec2> transformedPolygon;
	for (const auto vertex : polygon)
	{
		transformedPolygon.push_back(glm::vec2(matrix * glm::vec4(vertex, 0.0f, 1.0f)));
	}
	return transformedPolygon;
}


float randomFloat(const float min, const float max)
{
	return (max - min) * std::rand() / RAND_MAX + max;
}


float randomFloat(const float max)
{
	return randomFloat(0.0f, max);
}


glm::vec3 randomColour()
{
	return glm::vec3(randomFloat(), randomFloat(), randomFloat());
}


const Texture& randomBuildingTexture()
{
	return getTexture("../Images/building" + std::to_string(std::rand() % 3 + 1) + ".jpg");
}


std::vector<glm::vec3> translate(const std::vector<glm::vec3>& vertices, const glm::vec3& translation)
{
	std::vector<glm::vec3> newVertices;
	for (const auto vertex : vertices)
	{
		newVertices.push_back(vertex + translation);
	}
	return newVertices;
}


Drawable makePolygonalPrism(const std::vector<glm::vec2>& baseVertices, const float height, const std::string& texturePath)
{
	auto embeddedBaseVertices = embed(baseVertices);			// Base polygon, embedded in 3-space
	embeddedBaseVertices.push_back(embeddedBaseVertices[0]);	// Connect the polygon

	std::vector<glm::vec3> verticalTrajectory;					// Represents height of the building
	verticalTrajectory.push_back(glm::vec3());
	verticalTrajectory.push_back(glm::vec3(0.0f, 0.0f, height));

	auto vertices = computeTranslationalSweep(embeddedBaseVertices, verticalTrajectory);
	auto indices = computeSweepIndices(embeddedBaseVertices.size(), verticalTrajectory.size());

	// Normals
	std::vector<glm::vec3> normals;
	for (const auto vertex : vertices)
	{
		normals.push_back(glm::vec3(vertex.x, vertex.y, 0.0f));
	}

	const float length = glm::distance(baseVertices[0], baseVertices[1]);

	// Wrap texture around, one width for each side
	std::vector<glm::vec2> textureCoords(vertices.size());
	for (int i = 0; i < vertices.size() / 2; i++)
	{
		textureCoords[i] = glm::vec2(i * length, 0.0f);
		textureCoords[i + vertices.size() / 2] = glm::vec2(i * length, height);
	}
	
	glm::vec3 colour(1.0f);		// White, all texture

	Drawable prism(vertices, indices, normals, textureCoords);
	
	if (texturePath != "")
	{
		prism.setTexture(texturePath);
	}
	else
	{
		prism.setTexture(randomBuildingTexture());
	}

	return prism;
}


Drawable makeRegularPolygonalPrism(const int sides, const float radius, const float height, const std::string& texturePath)
{
	return makePolygonalPrism(makeRegularPolygon(sides, radius), height, texturePath);
}


Drawable makeRandomRegularPolygonalPrism(const int maxSides, const float maxRadius, const float minHeight, const float maxHeight, const std::string& texturePath)
{
	const float height = maxHeight * std::rand() / RAND_MAX;
	return makePolygonalPrism(randomRegularPolygon(maxSides, maxRadius), height, texturePath);
}


Drawable makeBlockBase(const glm::vec3& centre, const float size, const float height, const std::string& texturePath)
{
	const float edge = 0.5f;
	const float sidewalk = 0.4f;

	std::vector<glm::vec3> vertices;
	
	for (int i = -1; i <= 1; i += 2)
	{
		for (int j = 1; j >= -1; j -= 2)
		{
			vertices.push_back(centre + size * glm::vec3(i * edge, j * edge, 0.0f));
		}
	}

	for (int i = -1; i <= 1; i += 2)
	{
		for (int j = 1; j >= -1; j -= 2)
		{
			vertices.push_back(centre + size * glm::vec3(i * sidewalk, j * sidewalk, 0.0f));
		}
	}

	for (int i = -1; i <= 1; i += 2)
	{
		for (int j = 1; j >= -1; j -= 2)
		{
			vertices.push_back(centre + size * glm::vec3(i * sidewalk, j * sidewalk, height));
		}
	}

	std::vector<glm::vec3> normals;

	normals.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));

	normals.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
	normals.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
	normals.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
	normals.push_back(glm::vec3(1.0f, 1.0f, 0.0f));

	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(glm::vec3(1.0f, 1.0f, 0.0f));

	std::vector<glm::vec2> textures;

	textures.push_back(glm::vec2(0.0f, 1.0f));
	textures.push_back(glm::vec2(0.0f, 0.0f));
	textures.push_back(glm::vec2(1.0f, 1.0f));
	textures.push_back(glm::vec2(1.0f, 0.0f));

	textures.push_back(glm::vec2(0.15f, 0.85f));
	textures.push_back(glm::vec2(0.15f, 0.15f));
	textures.push_back(glm::vec2(0.85f, 0.85f));
	textures.push_back(glm::vec2(0.85f, 0.15f));

	textures.push_back(glm::vec2(0.15f, 0.85f));
	textures.push_back(glm::vec2(0.15f, 0.15f));
	textures.push_back(glm::vec2(0.85f, 0.85f));
	textures.push_back(glm::vec2(0.85f, 0.15f));

	std::vector<GLuint> indices =
	{
		0, 1, 2,
		2, 1, 3,
		8, 4, 9,
		9, 4, 5,
		9, 5, 11,
		11, 5, 7,
		11, 7, 10,
		10, 7, 6,
		10, 6, 8,
		8, 6, 4,
		8, 9, 10,
		10, 9, 11
	};

	return Drawable(vertices, indices, normals, textures, centre, texturePath);
}