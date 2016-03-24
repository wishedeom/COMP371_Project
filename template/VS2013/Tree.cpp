#include "Tree.h"

vector<GLfloat> Tree::treeV;
vector<GLuint> Tree::treeInd;
Shader* Tree::treeShaderptr = NULL;
const char* Tree::filepath = NULL;

Tree::Tree(float w, float h, const char* filepath)
{
	this->w = w;
	this->h = h;
	this->filepath = filepath;
	//treeShaderptr = (new Shader("../Source/TREE_VERTEX_SHADER.vs", "../Source/TREE_FRAG_SHADER.frag"));
	//shader_program = treeShaderptr->Program;
	texture = 0;
	VAO = 0;
	VBO = 0;
	EBO = 0;
	treeShaderptr = (new Shader("../Source/TREE_VERTEX_SHADER.vs", "../Source/TREE_FRAG_SHADER.frag"));
	shader_program = 0;

//	defineVertices();
	// xy-axis
/*	treeV = {
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
		-0.5f, 0.6f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, 0.6f, 0.5f, 1.0f, 0.0f,

		0.5f, 0.6f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f
	};
	treeInd = {
		0,1,2,
		3,4,5
	};

	createBuffers();
	loadTexture();

	
};

Tree::~Tree()
{
	treeV.clear();
	treeInd.clear();
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
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

	treeV = {
		// Positions         // Texture Coords (swapped y coordinates because texture is flipped upside down)
		-0.5f, 0.5f, 0.0f,	//0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, //0.0f, 0.0f,
		0.5f, 0.5f, 0.0f, //1.0f, 1.0f,

		0.5f, 0.5f, 0.0f, //1.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, //0.0f, 0.0f,
		0.5f, -0.5f, 0.0f//, 1.0f, 0.0f
	};
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(treeV[0]) * treeInd.size(), &treeInd[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0); // Position
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); // Texture
	glEnableVertexAttribArray(1);
	
	glBindVertexArray(0);
}

void Tree::draw()
{
	//glDisable(GL_CULL_FACE);
	//cout << "size" << treeInd.size() << endl;
	treeShaderptr->Use();
//	loadTexture();
//	createBuffers();
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(treeShaderptr->Program, "ourTexture"), 0);
	glDrawElements(GL_TRIANGLES, treeInd.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	//glEnable(GL_CULL_FACE);
}

GLuint Tree::getShaderProgram()
{
	return shader_program;
}

void Tree::loadTexture()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

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
		std::cout << "Unable to load image." << std::endl;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	
}