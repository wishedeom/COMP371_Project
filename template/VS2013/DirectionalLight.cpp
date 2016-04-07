#include "DirectionalLight.h"

#include "GLM/GTC/matrix_transform.hpp"

#include "utility.h"


DirectionalLight::DirectionalLight(const Camera& camera)
	: m_direction(0.0f, -1.0f, -1.0f)
	, m_ambientColour(1.0f, 1.0f, 1.0f)
	, m_diffuseColour(1.0f, 1.0f, 1.0f)
	, m_specularColour(1.0f, 1.0f, 1.0f)
	, m_camera(camera)
	, m_shader(Shader("../Source/SUN_VERTEX_SHADER.vs", "../Source/SUN_FRAG_SHADER.frag"))
	, m_lastFrameTime(glfwGetTime())
{
	glUniform1i(glGetUniformLocation(m_shader.programID(), "texture"), 0);
}
 

void DirectionalLight::UseShader() const
{
	m_shader.use();

	// Send camera info
	glUniform3fv(glGetUniformLocation(m_shader.programID(), "viewPos"), 1, glm::value_ptr(m_camera.position()));

	// Send light info
	glUniform3fv(glGetUniformLocation(m_shader.programID(), "light.direction"), 1, glm::value_ptr(m_direction));
	glUniform3fv(glGetUniformLocation(m_shader.programID(), "light.ambient"), 1, glm::value_ptr(m_ambientColour));
	glUniform3fv(glGetUniformLocation(m_shader.programID(), "light.diffuse"), 1, glm::value_ptr(m_diffuseColour));
	glUniform3fv(glGetUniformLocation(m_shader.programID(), "light.specular"), 1, glm::value_ptr(m_specularColour));
}


const Shader& DirectionalLight::getShader() const {	return m_shader; }


void DirectionalLight::update()
{
	double time = glfwGetTime();
	double deltaT = time - m_lastFrameTime;
	float theta = deltaT / 100;
	m_direction = glm::vec3(glm::rotate(id4, theta, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::vec4(m_direction, 0.0f));
	m_ambientColour = glm::vec3(glm::rotate(id4, theta, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::vec4(m_ambientColour, 0.0f));
	m_diffuseColour = glm::vec3(glm::rotate(id4, theta, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::vec4(m_diffuseColour, 0.0f));
	m_specularColour = glm::vec3(glm::rotate(id4, theta, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::vec4(m_specularColour, 0.0f));
	m_lastFrameTime = time;
	//std::cout << m_direction.y << std::endl;
}