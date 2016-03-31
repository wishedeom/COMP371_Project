#include "Fog.h"

Shader Fog::shader;

Fog::Fog(Camera* cam){
	if (!shader.initialized()){
		Shader shader("../Source/SUN_VERTEX_SHADER.vs", "../Source/SUN_FRAG_SHADER.frag");
	}
	camera = cam;

	glUniform4f(glGetUniformLocation(shader.programID(), "fogParams.fogColor"), 0.6f, 0.6f, 0.6f,1.0f);
	glUniform1f(glGetUniformLocation(shader.programID(), "fogParams.fogStart"), 1.f);
	glUniform1f(glGetUniformLocation(shader.programID(), "fogParams.fogEnd"), 5.0f);
}
