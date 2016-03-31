#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const Camera& camera)
	: m_direction(0.0f, -1.0f, -1.0f)
	, m_ambientColour(1.0f, 1.0f, 1.0f)
	, m_diffuseColour(1.0f, 1.0f, 1.0f)
	, m_specularColour(1.0f, 1.0f, 1.0f)
	, m_camera(camera)
	, m_shader(Shader("../Source/SUN_VERTEX_SHADER.vs", "../Source/SUN_FRAG_SHADER.frag"))
{
	glUniform1i(glGetUniformLocation(m_shader.programID(), "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(m_shader.programID(), "material.specular"), 1);
}
 

void DirectionalLight::UseShader() const
{
	m_shader.use();

	glUniform3fv(glGetUniformLocation(m_shader.programID(), "viewPos"), 1, glm::value_ptr(m_camera.position()));

	glUniform3fv(glGetUniformLocation(m_shader.programID(), "light.direction"), 1, glm::value_ptr(m_direction));
	glUniform3fv(glGetUniformLocation(m_shader.programID(), "light.ambient"), 1, glm::value_ptr(m_ambientColour));
	glUniform3fv(glGetUniformLocation(m_shader.programID(), "light.diffuse"), 1, glm::value_ptr(m_diffuseColour));
	glUniform3fv(glGetUniformLocation(m_shader.programID(), "light.specular"), 1, glm::value_ptr(m_specularColour));
}


const Shader& DirectionalLight::getShader() const
{
	return m_shader;
}