#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 tex;

uniform mat4 view_matrix, model_matrix, proj_matrix, model_view_matrix;
in vec3 in_Position;
out vec2 TexCoord;

void main()
{
	//mat4 CTM = model_view_matrix * in_Position;
	mat4 CTM = proj_matrix * view_matrix * model_matrix;
	gl_Position = CTM * vec4 (in_Position, 1.0);
	//gl_Position = proj_matrix * CTM;
	TexCoord = tex;
}