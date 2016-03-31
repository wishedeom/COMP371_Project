#pragma once
#include <string>
#include "glfw3.h"

// Represents a single texture.
class Texture
{
	GLuint m_id;			// OpenGL id for the texture; 0 if not loaded

public:

	// Constructs a texture whose image is read from the given file path
	// filePath: Location of the texture image
	Texture(const std::string& filePath);

	
	// Constructs an empty texture object
	Texture();

	
	// Returns the OpenGL id for the texture; 0 if not loaded
	GLuint id() const;


	// Binds the texture for drawing
	void bind() const;

	// Unbinds to allow next texture to be bound.
	void unbind() const;
};

