#version 330 core
out vec4 FragColor;
in vec4 color;
in vec2 texCoord;
in vec3 normal;
in vec3 pos;
uniform sampler2D tex0;
uniform vec3 lightPos;
uniform vec3 camPos;
uniform vec4 lightColor;
uniform float ambientIntensity;
void main()
{
   vec3 lightDir = normalize(lightPos - pos);

   float diffuse = max(dot(normal, lightDir) , 0.0f);

   float specLight = 0.5f;
   vec3 viewDir = normalize(camPos - pos);
   vec3 reflectionDir = reflect(-lightDir, normal);

   float specular = pow(max(dot(viewDir, reflectionDir), 0), 8) * specLight;
   FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambientIntensity + specular);
}