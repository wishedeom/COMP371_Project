#include "Sun.h"

GLint Sun::lightDirLoc;
GLint Sun::viewPosLoc;

//from http://learnopengl.com/code_viewer.php?code=lighting/light_casters_directional
Sun::Sun(){
	/*
	Shader lightingShader("../Source/SUN_VERTEX_SHADER.vs", "../Source/SUN_FRAG_SHADER.frag");
	//Shader lampShader("path/to/shaders/lamp.vs", "path/to/shaders/lamp.frag");

	// Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); // Note that we skip over the other data in our buffer object (we don't need the normals/textures, only positions).
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	GLuint diffuseMap, specularMap, emissionMap;
	glGenTextures(1, &diffuseMap);
	glGenTextures(1, &specularMap);
	glGenTextures(1, &emissionMap);

	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "material.specular"), 1);
	*/
}

void Sun::Draw(){
	Shader lightingShader("../Source/SUN_VERTEX_SHADER.vs", "../Source/SUN_FRAG_SHADER.frag");
	//Shader lampShader("path/to/shaders/lamp.vs", "path/to/shaders/lamp.frag");

	// Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Set the vertex attributes (only position data for the lamp))
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); // Note that we skip over the other data in our buffer object (we don't need the normals/textures, only positions).
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	GLuint diffuseMap, specularMap, emissionMap;
	glGenTextures(1, &diffuseMap);
	glGenTextures(1, &specularMap);
	glGenTextures(1, &emissionMap);

	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.programID(), "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.programID(), "material.specular"), 1);

	lightDirLoc = glGetUniformLocation(lightingShader.programID(), "light.direction");
	viewPosLoc = glGetUniformLocation(lightingShader.programID(), "viewPos");
	glUniform3f(lightDirLoc, -0.2f, -1.0f, -0.3f);

	// glUniform3f(viewPosLoc,  camera.Position.x, camera.Position.y, camera.Position.z);
	glUniform3f(viewPosLoc, 0.f, 0.0f, 0.f);
	// Set lights properties
	glUniform3f(glGetUniformLocation(lightingShader.programID(), "light.ambient"), 0.2f, 0.2f, 0.2f);
	glUniform3f(glGetUniformLocation(lightingShader.programID(), "light.diffuse"), 0.5f, 0.5f, 0.5f);
	glUniform3f(glGetUniformLocation(lightingShader.programID(), "light.specular"), 1.0f, 1.0f, 1.0f);

	// Set material properties
	glUniform1f(glGetUniformLocation(lightingShader.programID(), "material.shininess"), 32.0f);

	// Get the uniform locations
	GLint modelLoc = glGetUniformLocation(lightingShader.programID(), "model");
	GLint viewLoc = glGetUniformLocation(lightingShader.programID(), "view");
	GLint projLoc = glGetUniformLocation(lightingShader.programID(), "projection");
	// Pass the matrices to the shader
	//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// Bind diffuse map
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);
	// Bind specular map
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, specularMap);
}