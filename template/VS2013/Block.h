#pragma once

#include <vector>
#include <iostream>

#include "glew.h"
#include "glfw3.h"		
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "gtc/constants.hpp"

#include "Shader.h"
#include "SOIL.h"
#include "Texture.h"
#include "TextureManager.h"
#include "Structure.h"


class Block
{
	static Shader shader;
	static GLuint transformationMatrixID;	// The location of the transformation matrix in the shader program
	
	static const float width;
	static const float length;

	std::vector<glm::vec3> m_vertices;
	std::vector<glm::vec2> m_textureCoords;
	std::vector<GLuint> m_indices;

	GLuint m_vaoID;
	GLuint m_positionBufferID;
	GLuint m_texBufferID;
	GLuint m_eboID;

	std::array<Structure, 4> structures;

	const Texture& roadTexture;
	const Texture& sidewalkGrassTexture;

public:

	Block(const glm::vec3& centre);

	// Generates and initializes the VAO, VBO, and EBO for drawing the structure.
	void generateBuffers();

	void draw(const glm::mat4& transformation);
};