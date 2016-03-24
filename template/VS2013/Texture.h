#pragma once
#include <string>
#include "glfw3.h"

// Represents a single texture.
class Texture
{
	std::string m_filePath;
	GLuint m_id;

public:
	Texture( const std::string& filePath);

	Texture();

	std::string filePath() const;
	GLuint id() const;
};

