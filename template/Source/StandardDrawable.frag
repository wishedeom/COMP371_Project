#version 330 core
in vec3 fragColor;
in vec2 fragTexCoord;

out vec4 color;

// Texture samplers
uniform sampler2D texture;

void main()
{
	color = texture(texture, fragTexCoord) * fragColor;
}