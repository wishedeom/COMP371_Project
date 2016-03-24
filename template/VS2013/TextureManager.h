#pragma once
#include "glfw3.h"
#include <map>
#include "Texture.h"

// Load textures and controls OpenGL texture IDs
class TextureManager
{

	std::map<std::string, Texture> m_textures;	// Each texture has a name

public:

	TextureManager();
};

