#ifndef TREE_H_
#define TREE_H_

#include <vector>
#include "../ThirdParty/glew/glew.h"		// include GL Extension Wrangler
#include "../ThirdParty/glfw/glfw3.h"  // include GLFW helper library
#include "../ThirdParty/glm/glm.hpp"
#include <iostream>
#include "../VS2013/Shader.h"
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
	void buildPark();
private:
	vector<GLfloat> treeV;
	vector<GLfloat> ground;
	vector<GLuint> treeInd;
	//vector<GLfloat> position;
	static const char* filepath;
	GLuint texture;
	GLuint VAO, VBO, EBO, VAO2, VBO2, EBO2;
	static Shader *treeShaderptr;
	GLuint shader_program;
	GLfloat w, h; // To set the size of random trees & find the vertices
	GLuint view_matrix_id = 0;
	GLuint model_matrix_id = 0;
	GLuint proj_matrix_id = 0;

	//void writeColorCoord();
};

#endif /* TREE_H_ */