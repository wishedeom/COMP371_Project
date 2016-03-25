#pragma once
#include <string>
#include "glfw3.h"

// Represents a single texture.
class Texture
{
	std::string m_filePath;	// Where the texture image is stored
	GLuint m_id;			// OpenGL id for the texture; 0 if not loaded

public:

	// Constructs a texture whose image is read from the given file path
	// filePath: Location of the texture image
	Texture(const std::string& filePath);

	
	// Constructs an empty texture object
	Texture();

	
	// Returns the file path of the texture
	std::string filePath() const;

	
	// Returns the OpenGL id for the texture; 0 if not loaded
	GLuint id() const;


	// Binds the texture for drawing
	void bind() const;
};

