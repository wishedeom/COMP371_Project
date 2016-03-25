#include "TextureManager.h"
#include <iostream>

TextureManager textureManager;

typedef std::map<std::string, Texture> TexMap;

TextureManager::TextureManager() {}

void TextureManager::load(const std::string& path)
{
	const Texture texture(path);
	m_textures.insert(TexMap::value_type(path, texture));
}


bool TextureManager::isLoaded(const std::string& name) const
{
	return m_textures.find(name) != m_textures.end();
}


const Texture& TextureManager::get(const std::string& name) const
{
	return m_textures.find(name)->second;
}


const Texture& getTexture(const std::string& path)
{
	if (!textureManager.isLoaded(path))
	{
		textureManager.load(path);
	}
	return textureManager.get(path);
}