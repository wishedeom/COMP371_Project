#version 330 core

struct Material
{
	vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	float shininess;
};  

struct Light
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;
in vec3 skyboxTex;

out vec4 color;
  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

uniform samplerCube skybox;
uniform sampler2D texture1;

in vec4 viewSpace;

//values for fog
//FOG COLOR SHOULD MATCH BACKGROUND COLOR TO GIVE FADE-IN EFFECT
vec3 fogColor = vec3(0.4,0.4,0.4);
//vec3 fogColor = texture(skybox, skyboxTex).rgb;
//length is multipled to limit how far you can see, multiply by bigger number to see closer
float distance = length(viewSpace)*3;

float fogFactor = 0;

void main()
{
    // Ambient
    vec3 ambient = light.ambient * material.ambient;
  	
    // Diffuse
    vec3 lightDir = normalize(-light.direction);  
    float diff = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * material.diffuse;
    
    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, Normal);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * material.specular;
            
	fogFactor = (80-distance)/(80-20);
	fogFactor = clamp (fogFactor, 0,1);

	vec3 textureVec =  texture(texture1, TexCoords).rgb;
	
	vec3 ads = vec3(textureVec+diffuse);
	color = vec4(mix(fogColor,ads,fogFactor),fogFactor);
} 

