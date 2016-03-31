#include "DirectionalLight.h"


Shader DirectionalLight::shader;


DirectionalLight::DirectionalLight(Camera cam)
	: camera(cam)
{
	if (!shader.isInitialized()){
		Shader shader("../Source/SUN_VERTEX_SHADER.vs", "../Source/SUN_FRAG_SHADER.frag");
	}
}
 

void DirectionalLight::UseShader(){
	shader.use();
	GLint lightDirLoc = glGetUniformLocation(shader.programID(), "light.direction");
	GLint viewPosLoc = glGetUniformLocation(shader.programID(), "viewPos");

	//glUniform3f(lightDirLoc, -0.2f, -1.0f, -0.3f);
	glUniform3f(lightDirLoc, 0.f, -10.0f, -100.f);
	glUniform3f(viewPosLoc, camera.position().x, camera.position().y, camera.position().z);

	glUniform3f(glGetUniformLocation(shader.programID(), "light.ambient"), 0.4f, 0.4f, 0.4f);
	glUniform3f(glGetUniformLocation(shader.programID(), "light.diffuse"), 0.7f, 0.7f, 0.7f);
	glUniform3f(glGetUniformLocation(shader.programID(), "light.specular"), 1.0f, 1.0f, 1.0f);
	glm::mat4 model;


	glm::mat4 view;
	view = camera.view();
	glm::mat4 projection = glm::perspective(camera.fov(), (GLfloat)800 / (GLfloat)800, 0.1f, 100.0f);

	GLint modelLoc = glGetUniformLocation(shader.programID(), "model");
	GLint viewLoc = glGetUniformLocation(shader.programID(), "view");
	GLint projLoc = glGetUniformLocation(shader.programID(), "projection");

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}
