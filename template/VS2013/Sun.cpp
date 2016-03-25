#include "Sun.h"

GLint Sun::lightDirLoc;
GLint Sun::viewPosLoc;
Shader * Sun::lightingShader = NULL;
Camera* Sun::cameraptr = NULL;


//from http://learnopengl.com/code_viewer.php?code=lighting/light_casters_directional
Sun::Sun(Camera* camera){
	cameraptr = camera;
	lightingShader = new Shader("../Source/SUN_VERTEX_SHADER.vs", "../Source/SUN_FRAG_SHADER.frag");

	generateBuffers();
}

void Sun::Draw(){

	lightingShader->use();
	GLint lightDirLoc = glGetUniformLocation(lightingShader->programID(), "light.direction");
	GLint viewPosLoc = glGetUniformLocation(lightingShader->programID(), "viewPos");

	glUniform3f(lightDirLoc, -0.2f, -1.0f, -0.3f);
	glUniform3f(viewPosLoc, cameraptr->position().x, cameraptr->position().y, cameraptr->position().z);

	glUniform3f(glGetUniformLocation(lightingShader->programID(), "light.ambient"), 0.2f, 0.2f, 0.2f);
	glUniform3f(glGetUniformLocation(lightingShader->programID(), "light.diffuse"), 0.5f, 0.5f, 0.5f);
	glUniform3f(glGetUniformLocation(lightingShader->programID(), "light.specular"), 1.0f, 1.0f, 1.0f);

	glm::mat4 view;
	view = cameraptr->view();
	glm::mat4 projection = glm::perspective(cameraptr->fov(), (GLfloat)800 / (GLfloat)800, 0.1f, 100.0f);

	GLint modelLoc = glGetUniformLocation(lightingShader->programID(), "model");
	GLint viewLoc = glGetUniformLocation(lightingShader->programID(), "view");
	GLint projLoc = glGetUniformLocation(lightingShader->programID(), "projection");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

Sun::~Sun(){
	delete lightingShader;
	lightingShader = nullptr;
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Sun::generateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); 
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	GLuint diffuseMap, specularMap, emissionMap;
	glGenTextures(1, &diffuseMap);
	glGenTextures(1, &specularMap);
	glGenTextures(1, &emissionMap);
}