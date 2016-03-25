#include "Block.h"


//const char* Block::filepath = "../ThirdParty/Simple OpenGL Image Library/test_block.png";
const char* Block::filepath1 = "../Images/road.png";
const char* Block::filepath2 = "../Images/sidewalk.png";
std::vector<glm::vec3> Block::blockCoordinates;
std::vector<GLuint> Block::blockIndices;
Shader * Block::blockShaderptr = NULL;
GLuint Block::boardTexture;
GLuint Block::sidewalkGrassTexture;
std::vector<Block> Block::blocks;
//Shader Block::lightingShader("../Source/SUN_VERTEX_SHADER.vs", "../Source/SUN_FRAG_SHADER.frag");


Block::Block(GLuint x, GLuint y){

	/*	NOTE
	*	The grid isn't used and isn't useful right now
	*	It could come in handy when we use those bumpmaps(?)
	*/
	/*
	GLfloat xDistance = 0.05f;
	GLfloat yDistance = 0.05f;
	GLfloat yDistanceCopy = 0.05f;
	GLuint counter = 0;
	glm::vec3 initialVector(-0.15f, -0.05f, 0.0f);
	for (GLuint i = 0; i < BLOCK_HEIGHT; i++){
	for (GLuint j = 0; j < BLOCK_WIDTH; j++){
	blockCoordinates.push_back(glm::vec3(initialVector.x + xDistance, initialVector.y + yDistance, 0));
	yDistance = yDistance + 0.05f;
	blockIndices.push_back(counter);
	counter++;
	}
	yDistance = yDistanceCopy;
	xDistance = xDistance + 0.05f;
	}
	//createVAO could later be repurposed to actually create the VAO
	//createVAO();
	*/

	loadTextures(x, y);
}

Block::~Block(){
	blockCoordinates.clear();
	blockIndices.clear();
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	delete blockShaderptr;
	blockShaderptr = nullptr;
	filepath1 = NULL;
	filepath2 = NULL;
}
std::vector<glm::vec3> Block::getBlockCoordinates(){
	return blockCoordinates;
}

void Block::draw(){
	glBindTexture(GL_TEXTURE_2D, boardTexture);
	
	//blockShaderptr->Use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, boardTexture);
	glUniform1i(glGetUniformLocation(blockShaderptr->programID(), "ourTexture1"), 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, sidewalkGrassTexture);
	glUniform1i(glGetUniformLocation(blockShaderptr->programID(), "ourTexture2"), 1);

	//sun stuff; WHY ISNT IT WORKIN
	/*
	Shader lightingShader("../Source/SUN_VERTEX_SHADER.vs", "../Source/SUN_FRAG_SHADER.frag");
	lightingShader.Use();
	//GLint lightPosLoc = glGetUniformLocation(lightingShader.Program, "light.position");
	GLint lightDirLoc = glGetUniformLocation(lightingShader.Program, "light.direction");
	GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
	//glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);
	glUniform3f(lightDirLoc, -0.2f, -1.0f, -0.3f);
	glUniform3f(viewPosLoc, 0.f, 0.f, 0.f);
	// Set lights properties
	glUniform3f(glGetUniformLocation(lightingShader.Program, "light.ambient"), 0.2f, 0.2f, 0.2f);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "light.diffuse"), 0.5f, 0.5f, 0.5f);
	glUniform3f(glGetUniformLocation(lightingShader.Program, "light.specular"), 1.0f, 1.0f, 1.0f);
	// Set material properties
	glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);
	// Create camera transformations
	glm::mat4 view;
	//view = camera.GetViewMatrix();
	glm::mat4 projection; // = glm::perspective(camera.Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
	// Get the uniform locations
	GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
	GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
	GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");
	// Pass the matrices to the shader
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	*/

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, numInd, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


void Block::loadTextures(GLuint x, GLuint y){
	blockShaderptr = (new Shader("../Source/BLOCK_VERTEX_SHADER.vs", "../Source/BLOCK_FRAG_SHADER.frag"));

	/*
	//lighting stuff
	Shader lightingShader("../Source/SUN_VERTEX_SHADER.vs", "../Source/SUN_FRAG_SHADER.frag");
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); // Note that we skip over the other data in our buffer object (we don't need the normals/textures, only positions).
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	// Load textures
	GLuint diffuseMap, specularMap, emissionMap;
	glGenTextures(1, &diffuseMap);
	glGenTextures(1, &specularMap);
	glGenTextures(1, &emissionMap);
	int lightwidth, lightheight;
	unsigned char* lightimage;
	// Diffuse map
	lightimage = SOIL_load_image("container2.png", &lightwidth, &lightheight, 0, SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, lightwidth, lightheight, 0, GL_RGB, GL_UNSIGNED_BYTE, lightimage);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(lightimage);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	// Specular map
	lightimage = SOIL_load_image("container2_specular.png", &lightwidth, &lightheight, 0, SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, specularMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, lightwidth, lightheight, 0, GL_RGB, GL_UNSIGNED_BYTE, lightimage);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(lightimage);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);


	// Set texture units
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.specular"), 1);

	//-------- end of lighting stuff ---------------
	*/


	//------------ block stuff ---------------
	GLfloat xoffset = x*1.f;
	GLfloat yoffset = y*1.f;


	GLfloat vertices[] = {
		// Positions									// Colors				// Texture Coords
		-0.5f + xoffset, 0.5f + yoffset,0.0f,			1.0f, 0.0f, 1.0f,		0.0f, 1.0f,		// Road
		-0.5f + xoffset, -0.5f + yoffset,0.0f,			1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
		0.5f + xoffset, 0.5f + yoffset,	0.0f,			0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
		0.5f + xoffset, -0.5f + yoffset,0.0f,			0.0f, 0.0f, 1.0f,		1.0f, 0.0f,


		-0.35f + xoffset, 0.35f + yoffset,0.0f,			1.0f, 1.0f, 0.0f,		0.1375f, 0.8625f,	//Sidewalk profile
		-0.35f + xoffset, -0.35f + yoffset,0.0f,		1.0f, 1.0f, 0.0f,		0.1375f, 0.1375f,
		0.35f + xoffset, 0.35f + yoffset,0.0f,			1.0f, 1.0f, 0.0f,		0.8625f, 0.8625f,
		0.35f + xoffset, -0.35f + yoffset,0.0f,			1.0f, 1.0f, 0.0f,		0.8625f, 0.1375f,

		-0.35f + xoffset, 0.35f + yoffset,0.0125f,		1.0f, 0.0f, 0.0f,		0.15f, 0.85f,	// Upper Square
		-0.35f + xoffset, -0.35f + yoffset,0.0125f,		1.0f, 1.0f, 0.0f,		0.15f, 0.15f,
		0.35f + xoffset, 0.35f + yoffset,0.0125f,		0.0f, 0.0f, 1.0f,		0.85f, 0.85f,
		0.35f + xoffset, -0.35f + yoffset,0.0125f,		1.0f, 1.0f, 0.0f,		0.85f, 0.15f
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 2, // Road
		2, 1, 3,
		8, 4, 9,
		9, 4, 5,
		9, 5, 11,
		11, 5, 7,
		11, 7, 10,
		10, 7, 6,
		10, 6, 8,
		8, 6, 4,
		8, 9, 10,
		10, 9, 11
	};

	numInd = sizeof(indices);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO


	/// Texture 1
	//	GLuint texture;
	glGenTextures(1, &boardTexture);
	glBindTexture(GL_TEXTURE_2D, boardTexture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load image, create texture and generate mipmaps
	int width, height;
	unsigned char* image = SOIL_load_image(filepath1, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == '\0')
	{
		std::cout << "Unable to load image." << std::endl;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	/// Texture 2
	glGenTextures(1, &sidewalkGrassTexture);
	glBindTexture(GL_TEXTURE_2D, sidewalkGrassTexture); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load image, create texture and generate mipmaps
	image = SOIL_load_image(filepath2, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == '\0')
	{
		std::cout << "Unable to load image." << std::endl;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}
