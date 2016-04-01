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

	std::vector<glm::vec3> m_vertices;		// The structure's vertex coordinates in model space
	std::vector<glm::vec3> m_normals;		// The normal of each vertex
	std::vector<glm::vec2> m_textureCoords;	// The texture coordinates of each vertex
	std::vector<GLuint> m_indices;			// The indices to draw the structure as triangles

	GLuint m_vaoID;			// Vertex array object
	GLuint m_posBuffID;		// Vertex position buffer object
	GLuint m_colBuffID;		// Vertex colour buffer object
	GLuint m_texBuffID;		// Vertex texture buffer object
	GLuint m_eboID;			// Element buffer object, for vertex draw indices

	bool m_upToDate;		// True if and only if all buffers are up-to-date

	Texture m_texture;		// Texture
	glm::vec3 m_ambientColour;	// Ambient colour
	glm::vec3 m_diffuseColour;	// Diffuse colour
	glm::vec3 m_specularColour;	// Specular colour
	float m_shininess;

	glm::mat4 m_modelMatrix;

	glm::vec3 m_origin;		// Origin of model coordinate system in world coordinates
	

	// Generates and initializes the VAO, VBO, and EBO for drawing the structure.
	void generateBuffers();

	// Fills buffers
	void fillBuffers();

	// Fills the structure with a constant colour
	//void fill(const glm::vec3& colour);


public:

	// Constructs a drawable.
	Drawable
		(
		const std::vector<glm::vec3>& vertices = std::vector<glm::vec3>(),
		const std::vector<GLuint>& indices = std::vector<GLuint>(),
		const std::vector<glm::vec3>& normals = std::vector<glm::vec3>(),
		const std::vector<glm::vec2>& textureCoords = std::vector<glm::vec2>(),
		const glm::vec3& origin = glm::vec3(),
		const std::string& diffuseTexturePath = "",
		const float shininess = 0.0f
	);

	Drawable& setVertices(const std::vector<glm::vec3> vertices);
	Drawable& setNormals(const std::vector<glm::vec3> normals);
	Drawable& setTextureCoords(const std::vector<glm::vec2> texCoords);
	Drawable& setIndices(const std::vector<GLuint> indices);
	Drawable& setShininess(const float shininess);

	Drawable& setAmbientColour(const glm::vec3& ambientColour);
	Drawable& setDiffuseColour(const glm::vec3& diffuseColour);
	Drawable& setSpecularColour(const glm::vec3& specularColour);

	// Sets the texture
	Drawable& setTexture(const std::string& path);
	Drawable& setTexture(const Texture& texture);

	// Translates the drawable to a new origin.
	Drawable& setOrigin(const glm::vec3& origin);

	// Returns the model matrix
	glm::mat4 modelMatrix() const;

	// Returns the origin of the coordinate system
	glm::vec3 origin() const;

	// Draws the drawable, as seen by a given camera.
	virtual void draw(const Camera& camera, const DirectionalLight& light);
};