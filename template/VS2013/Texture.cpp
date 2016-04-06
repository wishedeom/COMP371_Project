#include "Texture.h"

#include <iostream>
#include <stdexcept>

#include "glew.h"
#include "SOIL.h"


Texture::Texture(const std::string& filePath)
{
	// Load the texture from memory using SOIL
	const GLuint id = SOIL_load_OGL_texture
	(
		filePath.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_POWER_OF_TWO | SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS
	);

	if (id == 0)
	{
		std::cout << "Error loading texture: " << filePath << std::endl;
	}

	m_id = id;
}


Texture::Texture() { m_id = 0; }


GLuint Texture::id() const { return m_id; }


void Texture::bind() const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_id);
}


void Texture::unbind() { glBindTexture(GL_TEXTURE_2D, 0); }