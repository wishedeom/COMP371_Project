#pragma once

#include <vector>
#include <iostream>
#include <array>

<<<<<<< HEAD
#include "../ThirdParty/glew/glew.h"
#include "../ThirdParty/glfw/glfw3.h"		
#include "../ThirdParty/glm/glm.hpp"
#include "../ThirdParty/gtc/matrix_transform.hpp"
#include "../ThirdParty/gtc/type_ptr.hpp"
#include "../ThirdParty/gtc/constants.hpp"
=======
#include "glew.h"
#include "glfw3.h"		
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "gtc/constants.hpp"
>>>>>>> refs/remotes/origin/master

#include "Shader.h"
#include "SOIL.h"
#include "Texture.h"
#include "TextureManager.h"
#include "Drawable.h"


class Block
{
	Drawable m_quad;
	std::array<Drawable, 4> m_buildings;

public:

	static const float width;
	static const float length;

	Block(const glm::vec3& centre);

	void draw(const Camera& camera);
};