#pragma once
#include <string>
#include "glfw3.h"

// Represents a single texture.
class Texture
{
	std::string m_name;
	std::string m_filePath;
	GLuint m_id;

public:
	Texture(const std::string& name, const std::string& filePath);

	std::string name() const;
	std::string filePath() const;
	GLuint id() const;

	void setName(const std::string& name);
};

