#version 330 core
out vec4 FragColor;
in vec4 color;
in vec2 texCoord;
in vec3 normal;
in vec3 pos;
uniform sampler2D tex0;
uniform sampler2D tex1;
uniform vec3 lightPos;
uniform vec3 camPos;
uniform vec4 lightColor;
uniform float ambientIntensity;


vec4 direcLight()
{

	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - pos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(tex0, texCoord) * (diffuse + ambientIntensity) + texture(tex1, texCoord).r * specular) * lightColor;
}


vec4 pointLight(){



	float distanceToLight = length(lightPos - pos);
	float quadCoef = 0.5;
	float linearCoef = 0.1;
	float lightDistanceMultiplier = 1.0f / (quadCoef * distanceToLight * distanceToLight + linearCoef * distanceToLight + 1.0f);
	vec3 lightDir = normalize(lightPos - pos);

   float diffuse = max(dot(normal, lightDir) , 0.0f);

   float specLight = 0.5f;
   vec3 viewDir = normalize(camPos - pos);
   vec3 reflectionDir = reflect(-lightDir, normal);	

   float specular = pow(max(dot(viewDir, reflectionDir), 0.0f), 16) * specLight;

   return texture(tex0, texCoord) * lightColor * (diffuse * lightDistanceMultiplier + ambientIntensity) + texture(tex1, texCoord).r * specular * lightDistanceMultiplier;

}


vec4 spotLight(){
	
	float innerCone = 0.95f;
	float outerCone = 0.8f;


	vec3 lightDir = normalize(lightPos - pos);

   float diffuse = max(dot(normal, lightDir) , 0.0f);

   float specLight = 0.5f;
   vec3 viewDir = normalize(camPos - pos);
   vec3 reflectionDir = reflect(-lightDir, normal);	

   float specular = pow(max(dot(viewDir, reflectionDir), 0.0f), 16) * specLight;


   float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDir);
   float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return (texture(tex0, texCoord) * (diffuse * inten + ambientIntensity) + texture(tex1, texCoord).r * specular * inten) * lightColor;

}
void main()
{
	FragColor = spotLight();
  
}