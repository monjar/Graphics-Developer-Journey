#version 330 core
out vec4 FragColor;
in vec4 color;
in vec2 texCoord;
in vec3 normal;
in vec3 pos;
uniform sampler2D tex0;
uniform vec3 lightPos;
uniform vec4 lightColor;
uniform float ambientIntensity;
void main()
{
   vec3 lightDir = normalize(lightPos - pos);

   float diffuse = max(dot(normal, lightDir) , 0.0f);
   FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambientIntensity);
}