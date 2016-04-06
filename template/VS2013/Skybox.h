#pragma once

#ifndef SKYBOX_H_
#define SKYBOX_H_

#include <vector>
#include "glew.h"		// include GL Extension Wrangler
#include "glfw3.h"  // include GLFW helper library
#include "glm.hpp"
#include <iostream>
#include "Shader.h"
#include "Camera.h"
#include "SOIL.h"

using namespace std;
class Skybox
{
	public:
		Skybox();
		
		void loadTexture();
		GLuint createTexture();
		void createBuffers();
		void draw(const Camera& camera);
		GLuint getShaderProgram();
	private:
		static vector<glm::vec3> cubeV;
		static GLfloat skyboxVertices[];
		static vector<GLuint> cubeInd;
		vector<const char*> faces;
		GLuint cubemapTexture;
		GLuint ProgramID;
		//GLuint faceTex;
		GLuint skyboxVAO, skyboxVBO;
		static Shader *skyShaderptr;
		GLuint shader_program;
		GLuint loadCubemap(vector<const GLchar*> faces);
		void loadIndices();
		GLuint size;
};

#endif /* SKYBOX_H_ */