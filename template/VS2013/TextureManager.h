#pragma once
#include "glfw3.h"
#include <map>
#include "Texture.h"

// Load textures and controls OpenGL texture IDs
class TextureManager
{

	std::map<std::string, Texture> m_textures;	// Each texture has a name

public:

	// Constructs an empty Texture Manager
	TextureManager();


	// Returns true if and only if a texture with the given name is already loaded
	bool isLoaded(const std::string& name) const;

	// Loads a texture.
	// name: The name of the texture.
	// filePath: The file path of the texture to load.
	void load(const std::string& name, const std::string& filePath);
};

