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


std::vector<glm::vec2> randomRegularPolygon(const int maxSides, const float minRadius, const float maxRadius)
{
	//const int sides = randomInt(3, maxSides);
	int randSides = randomInt(3, maxSides/2);
	int evenSides = randSides * 2;
	const float radius = randomFloat(minRadius, maxRadius);
	return makeRegularPolygon(randSides, radius);
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

int randomInt(const int min, const int max)
{
	return std::rand() % (max - min + 1) + min;
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


Drawable makePolygonalPrismFlatRooftop(const std::vector<glm::vec2>& baseVertices, const float height)
{
	auto embeddedBaseVertices = embed(baseVertices);			// Base polygon, embedded in 3-space
	embeddedBaseVertices.push_back(embeddedBaseVertices[0]);	// Connect the polygon

	std::vector<glm::vec3> verticalTrajectory;					// Represents height of the building
	verticalTrajectory.push_back(glm::vec3());
	verticalTrajectory.push_back(glm::vec3(0.0f, 0.0f, height));

	auto positions = computeTranslationalSweep(embeddedBaseVertices, verticalTrajectory);
	auto indices = computeSweepIndices(embeddedBaseVertices.size(), verticalTrajectory.size());

	// Normals
	std::vector<glm::vec3> normals;
	for (const auto vertex : positions)
	{
		normals.push_back(glm::vec3(vertex.x, vertex.y, 0.0f));
	}

	const float length = glm::distance(baseVertices[0], baseVertices[1]);

	// Wrap texture around, one width for each side
	std::vector<glm::vec2> textureCoords(positions.size());
	for (int i = 0; i < positions.size() / 2; i++)
	{
		textureCoords[i] = glm::vec2(i * length, 0.0f);
		textureCoords[i + positions.size() / 2] = glm::vec2(i * length, height);
	}

	std::vector<Vertex> vertices;
	for (int i = 0; i < positions.size(); i++)
	{
		vertices.push_back({ positions[i], normals[i], textureCoords[i] });
	}

	return Drawable().setVertices(vertices).setIndices(indices);
}


Drawable makePolygonalPrismTriangularRooftop(const std::vector<glm::vec2>& baseVertices, const float height, const float minHeight, const float maxHeight)
{
	auto embeddedBaseVertices = embed(baseVertices);			// Base polygon, embedded in 3-space
	embeddedBaseVertices.push_back(embeddedBaseVertices[0]);	// Connect the polygon

	// Divides the height in two parts: 1- Main body 2- Rooftop
	GLfloat mh, rh;
	GLfloat percent = randomFloat(20.f, 80.f);

	if (percent > 100.f)
		percent = percent - 100.f;
	percent = percent / 100.f;

	if (percent > 0.8f)
		percent = 0.8f;
	else if (percent < 0.2f)
		percent = 0.2f;

	mh = height * percent;
	rh = height - mh;

	/*****************************/
	/** Building main body data **/
	/*****************************/
	std::vector<glm::vec3> verticalTrajectory;					// Represents height of the building main body
	verticalTrajectory.push_back(glm::vec3());
	verticalTrajectory.push_back(glm::vec3(0.0f, 0.0f, mh));

	std::vector<glm::vec3> positions = computeTranslationalSweep(embeddedBaseVertices, verticalTrajectory);
	auto indices = computeSweepIndices(embeddedBaseVertices.size(), verticalTrajectory.size());

	// Normals
	std::vector<glm::vec3> normals;
	for (const auto vertex : positions)
	{
		normals.push_back(glm::vec3(vertex.x, vertex.y, 0.0f));
	}

	const GLfloat length = glm::distance(baseVertices[0], baseVertices[1]);

	// Wrap texture around, one width for each side
	std::vector<glm::vec2> textureCoords(positions.size());
	for (GLuint i = 0; i < positions.size() / 2; i++)
	{
		textureCoords[i] = glm::vec2(i * length, 0.0f);
		textureCoords[i + positions.size() / 2] = glm::vec2(i * length, mh);
	}

	std::vector<Vertex> vertices;
	for (GLuint i = 0; i < positions.size(); i++)
	{
		vertices.push_back({ positions[i], normals[i], textureCoords[i] });
	}


	/************************************/
	/* Building additional rooftop data */
	/************************************/
	// Positions
	for (GLuint i = 0; i < embeddedBaseVertices.size(); i++)
	{
		positions.push_back(glm::vec3(embeddedBaseVertices[i].x, embeddedBaseVertices[i].y, mh)); // Represents the base of the rooftop

		if (i < embeddedBaseVertices.size() - 1)
		{
			positions.push_back(glm::vec3(0.0f, 0.0f, height));	// Represents the highest point of the rooftop
		}
	}

	// Indices
	for (GLuint i = (embeddedBaseVertices.size() * 2); i < positions.size(); i += 2)
	{
		const GLuint lowerLeft = i;
		const GLuint upper = i + 1;
		const GLuint lowerRight = i + 2;

		indices.push_back(lowerLeft);
		indices.push_back(lowerRight);
		indices.push_back(upper);
		
	}

	// Normals
	for (GLuint i = (embeddedBaseVertices.size() * 2); i < positions.size(); i++)
	{
		if (i % 2 == 0)
			normals.push_back(glm::vec3(positions[i].x, positions[i].y, 0.0f));
		else
			normals.push_back(glm::vec3(positions[i - 1].x, positions[i - 1].y, 0.0f));
	}

	// Wrap texture around, one width for each side
	GLuint temp = 0;
	for (GLuint i = (embeddedBaseVertices.size() * 2); i < positions.size(); i += 2)
	{
		// Base
		textureCoords.push_back(glm::vec2(temp * length, 0.0f));

		// Top
		if (i < positions.size() - 1)
		{
			textureCoords.push_back(glm::vec2((temp + 0.5) * length, rh));
		}

		temp++;
	}

	// Sends to the collections of vertices to be drawn
	for (GLuint i = (embeddedBaseVertices.size() * 2); i < positions.size(); i++)
	{
		vertices.push_back({ positions[i], normals[i], textureCoords[i] });
	}

	return Drawable().setVertices(vertices).setIndices(indices);
}


Drawable makeRegularPolygonalPrism(const int sides, const float radius, const float height)
{
	return makePolygonalPrismFlatRooftop(makeRegularPolygon(sides, radius), height);
}


Drawable makeRandomRegularPolygon(const int minSides, const int maxSides, const float minRadius, const float maxRadius, const float minHeight, const float maxHeight)
{
	const float height = randomFloat(minHeight, maxHeight);

	// Random pick a type of polygon
	int rooftopType = (std::rand() % 99 + 1) % 2;

	// 0: Flat rooftop
	if (rooftopType == 0)
		return makePolygonalPrismFlatRooftop(randomRegularPolygon(maxSides, minRadius, maxRadius), height);

	// 1: Triangular rooftop
	else
		return makePolygonalPrismTriangularRooftop(randomRegularPolygon(maxSides, minRadius, maxRadius), height, minHeight, maxHeight);
}


Drawable makeBlockBase(const glm::vec3& centre, const float size, const float height)
{
	const float edge = 0.5f;
	const float sidewalk = 0.4f;

	std::vector<glm::vec3> positions;
	
	for (int i = -1; i <= 1; i += 2)
	{
		for (int j = 1; j >= -1; j -= 2)
		{
			positions.push_back(centre + size * glm::vec3(i * edge, j * edge, 0.0f));
		}
	}

	for (int i = -1; i <= 1; i += 2)
	{
		for (int j = 1; j >= -1; j -= 2)
		{
			positions.push_back(centre + size * glm::vec3(i * sidewalk, j * sidewalk, 0.0f));
		}
	}

	for (int i = -1; i <= 1; i += 2)
	{
		for (int j = 1; j >= -1; j -= 2)
		{
			positions.push_back(centre + size * glm::vec3(i * sidewalk, j * sidewalk, height));
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

	std::vector<Vertex> vertices;
	for (int i = 0; i < positions.size(); i++)
	{
		vertices.push_back({ positions[i], normals[i], textures[i] });
	}

	return Drawable().setVertices(vertices).setIndices(indices);
}


float angle(const glm::vec3& u, const glm::vec3& v)
{
	const glm::vec3 nu = glm::normalize(u);
	const glm::vec3 nv = glm::normalize(v);
	const GLfloat dotProduct = glm::dot(nu, nv);
	const glm::vec3 crossProduct = glm::cross(nu, nv);
	return -acos(dotProduct) * signum(crossProduct.z);
}


float signum(const float x)
{
	float sign;
	if (x > 0.0f)
	{
		sign = +1.0f;
	}
	else if (x == 0.0f)
	{
		sign = 0.0f;
	}
	else
	{
		sign = -1.0f;
	}
	return sign;
}