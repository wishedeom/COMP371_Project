#include "Texture.h"
#include <stdexcept>
#include "SOIL.h"
#include <iostream>

Texture::Texture(const std::string& name, const std::string& filePath)
{
	setName(name);
	const GLuint id = SOIL_load_OGL_texture(filePath.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	if (id == 0)
	{
		std::cout << "Error loading texture: " << filePath << std::endl;
	}
	else
	{
		m_filePath = filePath;
		m_id = id;
	}
}

Texture::Texture() { m_id = 0; }

std::string Texture::name() const { return m_name; }
std::string Texture::filePath() const { return m_filePath; }
GLuint Texture::id() const { return m_id; }

void Texture::setName(const std::string& name)
{
	if (name == "")
	{
		throw std::logic_error("Texture name cannot be empty.");
	}
	m_name = name;
}