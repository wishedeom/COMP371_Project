#ifndef _building_H
#define _building_H

#include "glew.h"		// include GL Extension Wrangler
#include "../VS2013/Shader.h" 
#include "glfw3.h"  // include GLFW helper library

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "gtc/constants.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <array>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>
#include "../ThirdParty/glm/gtc/matrix_transform.hpp"
#include "Camera.h"
using namespace std;

class building {

	public:

		static	vector <glm::vec3> buildings;
		static  vector <GLfloat> building::buildings1;
		static vector <GLuint> building::IndexArray;

		static	GLuint building::VBO;
		static	GLuint building::VAO;
		static	GLuint building::EBO;
		static	glm::vec3 xyz1;
		static	glm::vec3 xyz2;
		static	glm::vec3 xyz3;
		static	glm::vec3 xyz4;

		static glm::vec3 building::txyz1;
		static glm::vec3 building::txyz2;
		static glm::vec3 building::txyz3;

		static	GLfloat posy1;
		static	GLfloat posx1;

		static	GLfloat posy;
		static	GLfloat posx;

		static	GLfloat depth;
		static	GLfloat width;
		static	GLfloat height;

		static	GLfloat Buildingdepth;
		static	GLfloat Buildingwidth;
		static	GLfloat Buildingheight;

		static	GLfloat Blockdepth;
		static	GLfloat Blockwidth;
		static	GLfloat Blockheight;

	
		static	GLuint j;
		static	GLuint k;
	
		static vector<GLuint>building::indexes;

		static int randomnumber;
	
		void building::buildings4x4C(GLfloat posx, GLfloat posy);

		void building::buildings4x4T(GLfloat posx, GLfloat posy);

		void building::BuildCity();

		void building::defaultvec();

		void building::defaultvecTriangle();

		void building::indexCube();

		void building::indexTriangle();

		void building::MakeIndex();

		void building::pushinvec3Triangles();

		void building::showind();

		void building::pushinvec3Cubes();

		void building::genbuffer();
		vector<glm::vec3> building::getDataBuffer();
		vector<GLuint> building::getIndexBuffer();


		void building::testbuffer();


		static Shader* buildingShaderptr;
		void loadTextures();
		void Draw();
		void setLighting();
		GLuint LightVAO;
		Shader lightingShader;

		static Camera * cameraptr;

		building(Camera *);
};
#endif


