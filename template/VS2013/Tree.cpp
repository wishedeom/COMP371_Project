#include "Tree.h"

//vector<GLfloat> Tree::treeV;
//vector<GLfloat> Tree::ground;
//vector<GLuint> Tree::treeInd;
Shader* Tree::treeShaderptr = NULL;
const char* Tree::filepath = NULL;

Tree::Tree(float w, float h, const char* filepath)
{
	this->w = w;
	this->h = h;
	this->filepath = filepath;
	treeShaderptr = (new Shader("../Source/TREE_VERTEX_SHADER.vs", "../Source/TREE_FRAG_SHADER.frag"));
	shader_program = treeShaderptr->programID();
	texture = 0;
	VAO = 0;
	VBO = 0;
	EBO = 0;
	blockptr = new Block(0, 0);

	//	defineVertices();
	// xy-axis
	/*treeV = {
		// Positions         // Texture Coords (swapped y coordinates because texture is flipped upside down)
		-0.5f, 0.5f, 0.0f,	0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.0f,	1.0f, 0.0f,

		0.5f, 0.5f, 0.0f,	1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.0f,	1.0f, 1.0f
	};
	*/

	// xz-axis
	treeV = {
		// Positions         // Texture Coords (swapped y coordinates because texture is flipped upside down)
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f,0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f
	};
	

	/*ground = {
		// Positions         // Texture Coords (swapped y coordinates because texture is flipped upside down)
		-0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f,

		0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 1.0f
	};
	*/
	// test3
	
/*	treeV = {
		// Positions         // Texture Coords (swapped y coordinates because texture is flipped upside down)
		0.0f, 0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.0f, 0.0f, 1.0f,
		1.0f, -0.5f, 0.0f, 1.0f, 1.0f,

		0.0f, 0.5f, 0.0f, 0.0f, 0.0f,
		1.0f, -0.5f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.5f, 0.0f, 1.0f, 0.0f
	};
*/
	// Test 4

	// Positions					// Texture Coords
	/*treeV = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
	};*/
	treeInd = {
		0,1,2,
		3,4,5
	};

	/*ground = {
		5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
		-5.0f, -0.5f, 5.0f, 0.0f, 0.0f,
		-5.0f, -0.5f, -5.0f, 0.0f, 2.0f,

		5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
		-5.0f, -0.5f, -5.0f, 0.0f, 2.0f,
		5.0f, -0.5f, -5.0f, 2.0f, 2.0f
	};*/

/*	position = {
		-1.0f,
		-0.75f,
		-0.5f,
		-0.25f,
		0.0f,
		0.25f,
		0.5f,
		0.75f,
		1.0f
	};*/
//	createBuffers();
//	loadTexture();

	
};

Tree::~Tree()
{
	treeV.clear();
	treeInd.clear();
	ground.clear();
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO2);
	glDeleteBuffers(1, &VBO2);
	delete treeShaderptr;
	treeShaderptr = nullptr;
	delete filepath;
	filepath = nullptr;
}

/*void Tree::writeColorCoord()
{
	treeV.push_back(0.0f);
	treeV.push_back(1.0f);
	treeV.push_back(0.0f);
}*/

/* Set the size of random trees & find the vertices */
void Tree::defineVertices()
{
	/*treeV.push_back(-(w / 2)); // Top left
	treeV.push_back(h);
	treeV.push_back(0.0f);

	writeColorCoord();	// Color coordinates

	treeV.push_back(0.0f);	// Texture coordinates
	treeV.push_back(1.0f);

	treeV.push_back(-(w / 2)); // Bottom left
	treeV.push_back(0.0f);
	treeV.push_back(0.0f);

	writeColorCoord();	// Color coordinates

	treeV.push_back(0.0f);	// Texture coordinates
	treeV.push_back(0.0f);

	treeV.push_back(w / 2); // Bottom right
	treeV.push_back(0.0f);
	treeV.push_back(0.0f);

	writeColorCoord();	// Color coordinates

	treeV.push_back(0.0f);	// Texture coordinates
	treeV.push_back(1.0f);

	treeV.push_back(w / 2); // Top right
	treeV.push_back(h);
	treeV.push_back(0.0f);	

	writeColorCoord();	// Color coordinates

	treeV.push_back(1.0f);	// Texture coordinates
	treeV.push_back(1.0f);*/

/*	treeV = {
		// Positions         // Texture Coords (swapped y coordinates because texture is flipped upside down)
		-0.5f, 0.5f, 0.0f,	//0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, //0.0f, 0.0f,
		0.5f, 0.5f, 0.0f, //1.0f, 1.0f,

		0.5f, 0.5f, 0.0f, //1.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, //0.0f, 0.0f,
		0.5f, -0.5f, 0.0f//, 1.0f, 0.0f
	};*/


}

void Tree::createBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);


	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(treeV[0]) * treeV.size(), &treeV[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(treeInd[0]) * treeInd.size(), &treeInd[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0); // Position
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); // Texture
	glEnableVertexAttribArray(1);
	
	glBindVertexArray(0);

/*	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);

	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ground[0]) * ground.size(), &ground[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(treeInd[0]) * treeInd.size(), &treeInd[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0); // Position
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); // Texture
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);*/
}


void Tree::billboarding(Camera* cameraptr, glm::vec3 pos)
{
	///Transformations
	glm::mat4 proj_matrix;
	glm::mat4 view_matrix;
	glm::mat4 model_matrix;

	view_matrix_id = glGetUniformLocation(shader_program, "view_matrix");
	model_matrix_id = glGetUniformLocation(shader_program, "model_matrix");
	proj_matrix_id = glGetUniformLocation(shader_program, "proj_matrix");

	view_matrix = cameraptr->view();
	glm::vec3 camRight = glm::normalize(glm::vec3(view_matrix[0], view_matrix[1], view_matrix[2]));
	glm::vec3 camUp = glm::normalize(glm::vec3(view_matrix[3], view_matrix[4], 1.0));
	glm::vec3 camPos = cameraptr->position();

	glm::vec3 billFront = glm::vec3(camPos.x * -1, camPos.y * -1, camPos.z) - pos;
//	glm::vec3 billFront = camPos - pos;
//	billFront = glm::vec3(billFront.x * -1, billFront.y * -1, billFront.z);
	glm::vec3 billFrontNorm = glm::normalize(billFront);
	glm::vec3 billRight = glm::normalize(glm::cross(camUp, billFrontNorm));
	glm::vec3 billUp = glm::normalize(glm::cross(billFrontNorm, billRight));

	// Place the tree in the world
	model_matrix = glm::translate(model_matrix, pos);

	// Temporarily move the tree to the camera
	model_matrix = glm::translate(model_matrix, billFront);

	// Find the rotation angle
	GLfloat dot = glm::dot(camRight, billRight);
	GLfloat camRightMag = glm::length(camRight);
	GLfloat billRightMag = glm::length(billRight);
	GLfloat angle = glm::acos(dot / (camRightMag * billRightMag));

	// Perform the rotation
	//glm::vec3 rotAxis = glm::normalize(glm::vec3(camUp.x, camUp.y, 1.0));
	model_matrix = glm::rotate(model_matrix, angle, camUp);

	// Move the tree back
	model_matrix = glm::translate(model_matrix, glm::vec3(billFront.x * -1, billFront.y * -1, billFront.z * -1));

	proj_matrix = cameraptr->projection();

	glUniformMatrix4fv(proj_matrix_id, 1, GL_FALSE, glm::value_ptr(proj_matrix));
	glUniformMatrix4fv(view_matrix_id, 1, GL_FALSE, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, glm::value_ptr(model_matrix));
}

void Tree::draw()
{
	/* BLOCK */

	//blockptr->loadTextures(0,0);
	blockptr->draw();

	/* TREE */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	treeShaderptr->use();
	createBuffers();
	loadTexture();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(treeShaderptr->programID(), "ourTexture1"), 0);
	glBindVertexArray(VAO);
//	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDrawElements(GL_TRIANGLES, treeInd.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glDisable(GL_BLEND);
}

GLuint Tree::getShaderProgram()
{
	return shader_program;
}

void Tree::loadTexture()
{
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load image, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image(filepath, &width, &height, 0, SOIL_LOAD_RGBA);
	if (image == '\0')
	{
		cout << "Unable to load image." << endl;
	}
	cout << "LOADED TREE IMAGE" << endl;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	
}

// Copy of buildCity
// Define the boundary of potential park = inner section of a block
void Tree::buildPark()
{
	GLuint i = 0;
	GLuint x = 0;
	GLfloat posx = 0;
	GLfloat posy = 0;
	GLfloat blockwidth = 1.0f;
	GLfloat blockdepth = 1.0f;

	for (i = 0; i < 4; i++)
	{
		posy = i * blockwidth - 0.35f;
		for (x = 0; x < 4; x++)
		{
			posx = x * blockdepth - 0.35f;

		//	buildings4x4C(posy, posx);

		}
	}
	cout << "IM IN BUILD CITY\n";
	//indexCube();
}