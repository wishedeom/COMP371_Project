#include "Texture.h"
#include <stdexcept>
#include "SOIL.h"
#include <iostream>


Texture::Texture(const std::string& filePath)
{
	const GLuint id = SOIL_load_OGL_texture(filePath.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y);
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


std::string Texture::filePath() const { return m_filePath; }


GLuint Texture::id() const { return m_id; }


void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_id);
}