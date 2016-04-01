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
#include "Camera.h"
#include "DirectionalLight.h"


// A Drawable represents a single mesh.
class Drawable
{	

protected:

	std::vector<Vertex> m_vertices;		// Vertex data - positions, normals, texture coordinates
	std::vector<GLuint> m_indices;		// The indices to draw the structure as triangles

	GLuint m_vaoID;			// Vertex array object
	GLuint m_vboID;			// Vertex buffer object
	GLuint m_eboID;			// Element buffer object, for vertex draw indices

	bool m_upToDate;		// True if and only if all buffers are up-to-date

	Material m_material;	// Material properties

	glm::mat4 m_modelMatrix;

	glm::vec3 m_origin;		// Origin of model coordinate system in world coordinates
	

	// Generates and initializes the VAO, VBO, and EBO for drawing the structure.
	void generateBuffers();

	// Fills buffers
	void fillBuffers();


public:

	// Constructs a drawable.
	Drawable();

	// Sets the drawable's vertex data
	Drawable& setVertices(const std::vector<Vertex>& vertices);

	// Sets the drawable's index data, for drawing triangle vertices
	Drawable& setIndices(const std::vector<GLuint> indices);

	// Translates the drawable to a new origin.
	Drawable& setOrigin(const glm::vec3& origin);

	// Returns the model matrix
	glm::mat4 modelMatrix() const;

	// Returns the origin of the coordinate system
	glm::vec3 origin() const;

	// Draws the drawable, as seen by a given camera.
	virtual void draw(const Camera& camera, const DirectionalLight& light);
};


// Represents the data of a single vertex, in model coordinates
struct Vertex
{
	glm::vec3 position;		// Position
	glm::vec3 normal;		// Normal vector at position
	glm::vec2 texCoords;	// Texture coordinate at position
};


// Represents a drawable's material properties
struct Material
{
	Texture texture;			// Texture
	glm::vec3 ambientColour;	// Ambient colour
	glm::vec3 diffuseColour;	// Diffuse colour
	glm::vec3 specularColour;	// Specular colour
	float shininess;
};