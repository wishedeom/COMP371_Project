#pragma once
#include <vector>
#include "glew.h"		// include GL Extension Wrangler
#include "glfw3.h"  // include GLFW helper library
#include "glm.hpp"
#include <iostream>
#include "Shader.h"
#include "../ThirdParty/glm/gtc/type_ptr.hpp"
#include "../ThirdParty/glm/gtc/matrix_transform.hpp"
#include "Camera.h"

class Sun{
	public :
		Sun(Camera*);
		~Sun();
		void Draw();
	private:
		GLuint VAO, VBO, EBO;
		void generateBuffers();
		static Shader *lightingShader;
		static Shader *lampShader;
		static Camera* cameraptr;
		static GLint lightDirLoc;
		static GLint viewPosLoc;
};