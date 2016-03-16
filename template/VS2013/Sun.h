#pragma once
#include <vector>
#include "glew.h"		// include GL Extension Wrangler
#include "glfw3.h"  // include GLFW helper library
#include "glm.hpp"
#include <iostream>
#include "Shader.h"

class Sun{
	public :
		Sun();
		~Sun();
		void Draw();
	private:
		GLuint LightVAO, VAO, VBO, EBO;
		static Shader *lightingShader;
		static Shader *lampShader;

		static GLint lightDirLoc;
		static GLint viewPosLoc;
};