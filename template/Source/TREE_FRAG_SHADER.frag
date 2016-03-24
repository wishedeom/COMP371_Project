#version 330 core
in vec2 TexCoord;

out vec4 color;

// Texture samplers
uniform sampler2D ourTexture;

void main()
{
//	vec4 texColor = vec4(vec3(texture(ourTexture, TexCoord)), 1.0);
//	if (texColor.a < 0.8)
//		discard;
//	color = texColor;
	color = texture(ourTexture, TexCoord);
}

