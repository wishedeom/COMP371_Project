#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 tex;

uniform mat4 view_matrix, model_matrix, proj_matrix;
in  vec3 in_Position;		//vertex position

out vec2 TexCoord;

void main()
{
	//gl_Position = vec4(position, 1.0f);
	mat4 CTM = proj_matrix * view_matrix * model_matrix;
	gl_Position = CTM * vec4 (in_Position, 1.0);
	//TexCoord = vec2(tex.x, 1.0 - tex.y);
	TexCoord = tex;
}