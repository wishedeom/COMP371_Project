#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const Camera& camera)
	: m_camera(camera)
	, m_shader(Shader("../Source/SUN_VERTEX_SHADER.vs", "../Source/SUN_FRAG_SHADER.frag")) {}
 

void DirectionalLight::UseShader() const
{
	m_shader.use();
	GLint lightDirLoc = glGetUniformLocation(m_shader.programID(), "light.direction");
	GLint viewPosLoc = glGetUniformLocation(m_shader.programID(), "viewPos");

	glUniform3f(lightDirLoc, 0.f, -10.0f, -100.f);
	glUniform3f(viewPosLoc, m_camera.position().x, m_camera.position().y, m_camera.position().z);

	glUniform3f(glGetUniformLocation(m_shader.programID(), "light.ambient"), 0.4f, 0.4f, 0.4f);
	glUniform3f(glGetUniformLocation(m_shader.programID(), "light.diffuse"), 0.7f, 0.7f, 0.7f);
	glUniform3f(glGetUniformLocation(m_shader.programID(), "light.specular"), 1.0f, 1.0f, 1.0f);
}


const Shader& DirectionalLight::getShader() const
{
	return m_shader;
}