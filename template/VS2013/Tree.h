#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include "glew.h"		// include GL Extension Wrangler
#include "glfw3.h"  // include GLFW helper library
#include "glm.hpp"
#include <iostream>
#include "Shader.h"
#include "SOIL.h"

using namespace std;

class Tree
{
public:
	Tree(GLfloat w, GLfloat h, const char* filepath);
	~Tree();
	void defineVertices();
	void loadTexture();
	void createBuffers();
	void draw();
	GLuint getShaderProgram();

private:
	static vector<GLfloat> treeV;
	static vector<GLuint> treeInd;
	static const char* filepath;
	GLuint texture;
	GLuint VAO, VBO, EBO;
	static Shader *treeShaderptr;
	GLuint shader_program;
	GLfloat w, h;

	void writeColorCoord();
};

#endif /* TREE_H_ */