#pragma once
#include "glew.h"
#include "glfw3.h"
#include <map>
#include <vector>
#include "Texture.h"


const Texture& getTexture(const std::string& path);


// Load textures and controls OpenGL texture IDs
class TextureManager
{

	std::map<std::string, Texture> m_textures;	// Each texture has a file path

public:

	// Constructs an empty Texture Manager
	TextureManager();


	// Returns true if and only if a texture with the given path is already loaded
	bool isLoaded(const std::string& path) const;


	// Loads a texture.
	// name: The name of the texture.
	// filePath: The file path of the texture to load.
	void load(const std::string& filePath);


	// Returns a reference to a texture by name.
	const Texture& get(const std::string& name) const;
};

