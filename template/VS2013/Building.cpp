#pragma once

#include "building.h"

vector <glm::vec3> building::buildings;
vector <GLfloat> building::buildings1;
vector <GLuint> building::IndexArray;
Shader* building::buildingShaderptr = NULL;
Camera* building::cameraptr = NULL;
GLuint building::VBO;
GLuint building::VAO;
GLuint building::EBO;

glm::vec3 building::xyz1(0.0f, 0.0f, 0.0f);
glm::vec3 building::xyz2(0.0f, 0.35f, 0.0f);
glm::vec3 building::xyz3(0.35f, 0.35f, 0.0f);
glm::vec3 building::xyz4(0.35f, 0.0f, 0.0f);

glm::vec3 building::txyz1(0.0f, 0.0f, 0.0f);
glm::vec3 building::txyz2(0.05f, 0.10f, 0.0f);
glm::vec3 building::txyz3(0.10f, 0.0f, 0.0f);


GLfloat building::posy1 = 0.0f;
GLfloat building::posx1 = 0.0f;

GLfloat building::posy = 0.0f;
GLfloat building::posx = 0.0f;

GLfloat building::depth = 0.10f;
GLfloat building::width = 0.10f;
GLfloat building::height = 0.10f;

GLfloat building::Buildingdepth = 0.50f;
GLfloat building::Buildingwidth = 0.50f;
GLfloat building::Buildingheight = 0.50f;

GLfloat building::Blockdepth = 1.0f;
GLfloat building::Blockwidth = 1.0f;
GLfloat building::Blockheight = 1.0f;


GLuint building::j;
GLuint building::k;

vector<GLuint> building::indexes;

int building::randomnumber;

Shader building::lightingShader;
GLuint building::loopCounter = 0;

building::building(Camera * cam){

	if (!lightingShader.initialized())
	{
		lightingShader = Shader("../Source/SUN_VERTEX_SHADER.vs", "../Source/SUN_FRAG_SHADER.frag");
		//viewMatrixID = glGetUniformLocation(shader.programID(), "view_matrix");
		//modelMatrixID = glGetUniformLocation(shader.programID(), "model_matrix");
		//projMatrixID = glGetUniformLocation(shader.programID(), "proj_matrix");
	}
	cameraptr = cam;
	
}

void building::buildings4x4C(GLfloat posx, GLfloat posy)
{
	GLfloat Oposx = posx;
	GLfloat Oposy = posy;
	GLfloat Cposx = 0;
	GLfloat Cposy = 0;
	GLuint z = 0;
	GLuint p = 0;
	GLfloat roof1 = xyz1.z;
	GLfloat roof2 = xyz2.z;
	GLfloat roof3 = xyz3.z;
	GLfloat roof4 = xyz4.z;

	for (z = 0; z < 2; z++)
	{
		Cposy = posy + z*0.35f;

		for (p = 0; p < 2; p++)
		{

			Cposx = posx + p*0.35f;

			defaultvec();

			xyz1.x = xyz1.x + Cposx;
			xyz1.y = xyz1.y + Cposy;

			xyz2.x = xyz2.x + Cposx;
			xyz2.y = xyz2.y + Cposy;

			xyz3.x = xyz3.x + Cposx;
			xyz3.y = xyz3.y + Cposy;

			xyz4.x = xyz4.x + Cposx;
			xyz4.y = xyz4.y + Cposy;

			pushinvec3Cubes();

			randomnumber = rand() % 9 + 1;

			//cout << randomnumber << "\n";
			/*
			xyz1.z = xyz1.z + Buildingheight;
			xyz2.z = xyz2.z + Buildingheight;
			xyz3.z = xyz3.z + Buildingheight;
			xyz4.z = xyz4.z + Buildingheight;
			*/



			xyz1.z = xyz1.z + Buildingheight;
			xyz2.z = xyz2.z + Buildingheight;
			xyz3.z = xyz3.z + Buildingheight;
			xyz4.z = xyz4.z + Buildingheight;

			pushinvec3Cubes();


			for (GLuint u = 2; u < randomnumber; u++)
			{

				roof1 = xyz1.z;
				roof2 = xyz2.z;
				roof3 = xyz3.z;
				roof4 = xyz4.z;

				pushinvec3Cubes();


				xyz1.z = u*Buildingheight;
				xyz2.z = u*Buildingheight;
				xyz3.z = u*Buildingheight;
				xyz4.z = u*Buildingheight;

				pushinvec3Cubes();

			}


		}
	}


}

void building::buildings4x4T(GLfloat posx, GLfloat posy)
{
	GLfloat Oposx = posx;
	GLfloat Oposy = posy;
	GLfloat Cposx = 0;
	GLfloat Cposy = 0;
	GLuint z = 0;
	GLuint p = 0;
	GLfloat roof1 = txyz1.z;
	GLfloat roof2 = txyz2.z;
	GLfloat roof3 = txyz3.z;


	for (z = 0; z < 2; z++)
	{
		Cposy = posy + z*0.50;

		for (p = 0; p < 2; p++)
		{

			Cposx = posx + p*0.50f;

			defaultvecTriangle();

			txyz1.x = txyz1.x + Cposx;
			txyz1.y = txyz1.y + Cposy;

			txyz2.x = txyz2.x + Cposx;
			txyz2.y = txyz2.y + Cposy;

			txyz3.x = txyz3.x + Cposx;
			txyz3.y = txyz3.y + Cposy;

			pushinvec3Triangles();

			randomnumber = rand() % 9 + 1;

			
			txyz1.z = txyz1.z + Buildingheight;
			txyz2.z = txyz2.z + Buildingheight;
			txyz3.z = txyz3.z + Buildingheight;
			

			pushinvec3Triangles();


			for (GLuint u = 2; u < randomnumber; u++)
			{

				roof1 = txyz1.z;
				roof2 = txyz2.z;
				roof3 = txyz3.z;
				

				pushinvec3Triangles();


				txyz1.z = u*Buildingheight;
				txyz2.z = u*Buildingheight;
				txyz3.z = u*Buildingheight;
				

				pushinvec3Triangles();

			}


		}
}



}

void building::BuildCity()
{
	GLuint i = 0;
	GLuint x = 0;
	

	for (i = 0; i < 4; i++)
	{
		posy = i * Blockwidth - 0.35f;
		for (x = 0; x < 4; x++)
		{
			posx = x * Blockdepth - 0.35f;

		//	randomnumber = rand() % 100;
		//	cout << randomnumber<< "\n";
		//	if (randomnumber> 50)
		//	{
		//		buildings4x4T(posy, posx);
		//		IndexArray.push_back(0);
		//	}
		//	else
		//	{
				buildings4x4C(posy, posx);
		//		IndexArray.push_back(1);
			//}
			
			
		}
	}
	cout << "IM IN BUILD CITY\n";
	indexCube();
}

void building::MakeIndex()
{
	GLuint spot=0;
	


	for (GLuint i = 0; i < IndexArray.size(); i++)
	{
		cout << spot;
		if (IndexArray[i] == 0)
		{
			cout << "the index is 0" << "\n";

			for (int x=0; x < 4; x++)
			{
			
			indexes.push_back(spot);
			indexes.push_back(spot + 1);
			indexes.push_back(spot + 2);

			// top half

			indexes.push_back(spot + 3);
			indexes.push_back(spot + 4);
			indexes.push_back(spot + 5);

			// first wall

			indexes.push_back(spot);
			indexes.push_back(spot + 3);
			indexes.push_back(spot + 4);

			indexes.push_back(spot);
			indexes.push_back(spot);
			indexes.push_back(spot + 4);

			// second wall 

			indexes.push_back(spot + 1);
			indexes.push_back(spot + 4);
			indexes.push_back(spot + 5);

			indexes.push_back(spot + 1);
			indexes.push_back(spot + 2);
			indexes.push_back(spot + 5);


			// third wall

			indexes.push_back(spot + 2);
			indexes.push_back(spot + 5);
			indexes.push_back(spot + 3);

			indexes.push_back(spot + 2);
			indexes.push_back(spot);
			indexes.push_back(spot + 3);
			
			spot += 6;
			}

		}
		else
		{
			cout << "the index is 1" << "\n";

			for (int x=0; x < 4; x++)
			{

				// Bottom half

				indexes.push_back(spot);
				indexes.push_back(spot + 1);
				indexes.push_back(spot + 2);

				indexes.push_back(spot);
				indexes.push_back(spot + 3);
				indexes.push_back(spot + 2);

				// top half

				indexes.push_back(spot + 4);
				indexes.push_back(spot + 5);
				indexes.push_back(spot + 6);

				indexes.push_back(spot + 4);
				indexes.push_back(spot + 7);
				indexes.push_back(spot + 6);

				// wall #1

				indexes.push_back(spot);
				indexes.push_back(spot + 4);
				indexes.push_back(spot + 7);

				indexes.push_back(spot);
				indexes.push_back(spot + 3);
				indexes.push_back(spot + 7);

				//wall #2

				indexes.push_back(spot);
				indexes.push_back(spot + 4);
				indexes.push_back(spot + 5);

				indexes.push_back(spot);
				indexes.push_back(spot + 1);
				indexes.push_back(spot + 5);

				//wall #3


				indexes.push_back(spot + 1);
				indexes.push_back(spot + 5);
				indexes.push_back(spot + 6);

				indexes.push_back(spot + 1);
				indexes.push_back(spot + 2);
				indexes.push_back(spot + 6);

				//wall #4

				indexes.push_back(spot + 3);
				indexes.push_back(spot + 7);
				indexes.push_back(spot + 6);

				indexes.push_back(spot + 3);
				indexes.push_back(spot + 2);
				indexes.push_back(spot + 6);

				spot += 8;
			}
		}

		
		
	}showind();
		loadTextures();
}

void building::defaultvecTriangle()

{
	txyz1.x = 0.0f;
	txyz1.y = 0.0f;
	txyz1.z = 0.0f;

	txyz2.x = 0.1f;
	txyz2.y = 0.0f;
	txyz2.z = 0.0f;

	txyz3.x = 0.05f;
	txyz3.y = 0.1f;
	txyz3.z = 0.0f;
}

void building::defaultvec()
{
	xyz1.x = 0.0f;
	xyz1.y = 0.0f;
	xyz1.z = 0.0f;

	xyz2.x = 0.0f;
	xyz2.y = 0.35f;
	xyz2.z = 0.0f;

	xyz3.x = 0.35f;
	xyz3.y = 0.35f;
	xyz3.z = 0.0f;

	xyz4.x = 0.35f;
	xyz4.y = 0.0f;
	xyz4.z = 0.0f;
}

void building::indexCube()
{
	cout << buildings.size() << "\n";

	for (GLuint i = 0; i <= buildings.size() - 1; i += 8)
	{
		// Bottom half

		indexes.push_back(i);
		indexes.push_back(i + 1);
		indexes.push_back(i + 2);

		indexes.push_back(i);
		indexes.push_back(i + 3);
		indexes.push_back(i + 2);

		// top half

		indexes.push_back(i + 4);
		indexes.push_back(i + 5);
		indexes.push_back(i + 6);

		indexes.push_back(i + 4);
		indexes.push_back(i + 7);
		indexes.push_back(i + 6);

		// wall #1

		indexes.push_back(i);
		indexes.push_back(i + 4);
		indexes.push_back(i + 7);

		indexes.push_back(i);
		indexes.push_back(i + 3);
		indexes.push_back(i + 7);

		//wall #2

		indexes.push_back(i);
		indexes.push_back(i + 4);
		indexes.push_back(i + 5);

		indexes.push_back(i);
		indexes.push_back(i + 1);
		indexes.push_back(i + 5);

		//wall #3


		indexes.push_back(i + 1);
		indexes.push_back(i + 5);
		indexes.push_back(i + 6);

		indexes.push_back(i + 1);
		indexes.push_back(i + 2);
		indexes.push_back(i + 6);

		//wall #4

		indexes.push_back(i + 3);
		indexes.push_back(i + 7);
		indexes.push_back(i + 6);

		indexes.push_back(i + 3);
		indexes.push_back(i + 2);
		indexes.push_back(i + 6);
	}

	//	showind();
	loadTextures();
}

void building::indexTriangle()
{

	for (GLuint i = 0; i <= buildings.size() - 1; i += 6)
	{
		// Bottom half

		indexes.push_back(i);
		indexes.push_back(i + 1);
		indexes.push_back(i + 2);

		// top half

		indexes.push_back(i + 3);
		indexes.push_back(i + 4);
		indexes.push_back(i + 5);
		
		// first wall

		indexes.push_back(i);
		indexes.push_back(i + 3);
		indexes.push_back(i + 4);

		indexes.push_back(i);
		indexes.push_back(i);
		indexes.push_back(i + 4);

		// second wall 

		indexes.push_back(i+1);
		indexes.push_back(i + 4);
		indexes.push_back(i + 5);

		indexes.push_back(i+1);
		indexes.push_back(i+2);
		indexes.push_back(i + 5);


		// third wall
		
		indexes.push_back(i + 2);
		indexes.push_back(i + 5);
		indexes.push_back(i + 3);

		indexes.push_back(i + 2);
		indexes.push_back(i);
		indexes.push_back(i + 3);
		

	}

	loadTextures();

}

void building::showind()
{
	GLuint x = 0;

	for (GLuint i = 0; i <= indexes.size() - 1; i++)
	{
		cout << indexes[i] << "  ,  ";
		x++;
		
		if (x == 3)
		{
			cout << "\n";
			x = 0;
		}
	}
}

void building::pushinvec3Cubes()
{
	buildings.push_back(xyz1);
	//cout << xyz1.x << "  ,  " << xyz1.y << "  ,  " << xyz1.z << "\n";
	buildings.push_back(xyz2);
	//cout << xyz2.x << "  ,  " << xyz2.y << "  ,  " << xyz2.z << "\n";
	buildings.push_back(xyz3);
	//cout << xyz3.x << "  ,  " << xyz3.y << "  ,  " << xyz3.z << "\n";
	buildings.push_back(xyz4);
	//cout << xyz4.x << "  ,  " << xyz4.y << "  ,  " << xyz4.z << "\n";
}

void building::pushinvec3Triangles()
{
	buildings.push_back(txyz1);
	//cout << txyz1.x << "  ,  " << txyz1.y << "  ,  " << txyz1.z << "\n";
	buildings.push_back(txyz2);
	//cout << txyz2.x << "  ,  " << txyz2.y << "  ,  " << txyz2.z << "\n";
	buildings.push_back(txyz3);
	//cout << txyz3.x << "  ,  " << txyz3.y << "  ,  " << txyz3.z << "\n";

}


void building::testbuffer()
{

	buildings1 = {
		0.0f, 0.0f, 0.0f,
		0.05f, 0.10f, 0.0f,
		0.10f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.1f,-
		0.05f, 0.10f, 0.1f,
		0.10f, 0.0f, 0.1f
		
	};

	indexes = {
		0, 1, 2,
		3, 4, 5,

		0, 3, 4,
		0, 1, 4,
		1, 4, 5,
		1, 2, 5,
		2, 5, 3,
		2, 0, 3,
		


	};

	loadTextures();

}

vector<glm::vec3> building::getDataBuffer()
{
	
	return buildings;

}

vector<GLuint> building::getIndexBuffer()
{

	return indexes;

}

void building::genbuffer()
{
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Give our vertices to OpenGL.

	glBufferData(GL_ARRAY_BUFFER, buildings1.size()*sizeof(glm::vec3), &buildings1.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// Give our vertices to OpenGL.
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size()*sizeof(GLuint), &indexes.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		3 * sizeof(GLfloat),                  // stride
		(GLvoid*)0            // array buffer offset
		);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO

}

void building::loadTextures(){
	//buildingShaderptr = (new Shader("../Source/COMP371_hw1.vs", "../Source/COMP371_hw1.fss"));

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(buildings2.at(i))*buildings2.size(), buildings2.data(), GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, buildings.size()*sizeof(glm::vec3), &buildings.front(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size()*sizeof(GLuint), &indexes.front(), GL_STATIC_DRAW);

	cout << "SIZE OF BULDINGS  IS " << buildings.size() << endl;
	cout << "SIZE OF indexes IS " << indexes.size() << endl;
	// Position attribute

	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		3 * sizeof(GLfloat),  // stride
		(GLvoid*)0            // array buffer offset
		);
	glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	/*
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	*/
	glBindVertexArray(0); // Unbind VAO

	setLighting();

}

void building::Draw(){
	lightingShader.use();
	GLint lightDirLoc = glGetUniformLocation(lightingShader.programID(), "light.direction");
	GLint viewPosLoc = glGetUniformLocation(lightingShader.programID(), "viewPos");

	//glUniform3f(lightDirLoc, -0.2f, -1.0f, -0.3f);
	glUniform3f(lightDirLoc, 0.f, -10.0f, -100.f);
	glUniform3f(viewPosLoc, cameraptr->position().x, cameraptr->position().y, cameraptr->position().z);

	glUniform3f(glGetUniformLocation(lightingShader.programID(), "light.ambient"), 0.4f, 0.4f, 0.4f);
	glUniform3f(glGetUniformLocation(lightingShader.programID(), "light.diffuse"), 0.7f, 0.7f, 0.7f);
	glUniform3f(glGetUniformLocation(lightingShader.programID(), "light.specular"), 1.0f, 1.0f, 1.0f);
	glm::mat4 model;


	glm::mat4 view;
	view = cameraptr->view();
	glm::mat4 projection = glm::perspective(cameraptr->fov(), (GLfloat)800 / (GLfloat)800, 0.1f, 100.0f);

	GLint modelLoc = glGetUniformLocation(lightingShader.programID(), "model");
	GLint viewLoc = glGetUniformLocation(lightingShader.programID(), "view");
	GLint projLoc = glGetUniformLocation(lightingShader.programID(), "projection");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES,indexes.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}

void building::setLighting(){
	//Shader * lightingShader = new Shader("../Source/SUN_VERTEX_SHADER.vs", "../Source/SUN_FRAG_SHADER.frag");

	glGenVertexArrays(1, &LightVAO);
	glBindVertexArray(LightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	GLuint diffuseMap, specularMap, emissionMap;
	glGenTextures(1, &diffuseMap);
	glGenTextures(1, &specularMap);
	glGenTextures(1, &emissionMap);

}