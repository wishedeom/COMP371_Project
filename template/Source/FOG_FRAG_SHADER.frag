#version 330 core

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;
in vec4 viewSpace;  

  
//values for fog
vec3 fogColor = vec3(0.5,0.5,0.5);
vec3 lightColor = vec3(0.7,0.7,0.7);
float distance = length(viewSpace);
float fogFactor = 0;
  
  
out vec4 color;
  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{

	fogFactor = (80-distance)/(80-20);
	fogFactor = clamp (fogFactor, 0,1);
			
			
	vec3 finalColor = mix(fogColor, lightCOlor, fogFactor);
	color = vec4(finalColor, 1);
} 

