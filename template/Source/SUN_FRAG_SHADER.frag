#version 330 core



struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float     shininess;
};  

struct Light {
    //vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;
in vec4 viewSpace;  

  
//values for fog
//vec3 fogColor = vec3(0.5,0.5,0.5);
//float distance = length(viewSpace);
//float fogFactor = 0;
  
  
out vec4 color;
  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    // Ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
  	
    // Diffuse 
    vec3 norm = normalize(Normal);
    // vec3 lightDir = normalize(light.position - FragPos);
    vec3 lightDir = normalize(-light.direction);  
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));  
    
    // Specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
            
	//fogFactor = (80-distance)/(80-20);
	//fogFactor = clamp (fogFactor, 0,1);
			
			
	//vec3 finalColor = mix(fogColor, ambient, diffuse, specular);
	//color = vec4(finalColor, 1);
    color = vec4(ambient + diffuse + specular, 1);  

} 

