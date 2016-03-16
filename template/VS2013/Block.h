#pragma once
#include <vector>
#include "glew.h"		// include GL Extension Wrangler
#include "glfw3.h"  // include GLFW helper library
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "gtc/constants.hpp"
#include <iostream>
#include "Shader.h"
#include "SOIL.h"

using namespace std;
#define BLOCK_WIDTH 20
#define BLOCK_HEIGHT 20


class Block{
	public:
		Block();
		Block(GLuint,GLuint);
		~Block();

		static Block* getBlocks();
		vector<glm::vec3> getBlockCoordinates();
		void draw();
		void loadTextures(GLuint,GLuint);

	private:
		static const char* filepath1;
		static const char* filepath2;
		//static const char* filepath;
		static GLuint boardTexture;
		static GLuint sidewalkGrassTexture;

		static Shader *blockShaderptr;
		static vector<glm::vec3> blockCoordinates;
		static vector<GLuint> blockIndices;
		static vector<Block> blocks;
		static Shader lightingShader;

		GLuint VAO, VBO, EBO;
		void createVAO();
		GLuint numInd;
		GLuint shader_program;
};
