#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTex;
layout (location = 3) in vec3 aNormal;

out vec4 color;
out vec2 texCoord;
out vec3 normal;
out vec3 pos;

uniform mat4 camMatrix;
uniform mat4 model;
void main()
{
	pos = vec3(model * vec4(aPos, 1.0f));
   gl_Position = camMatrix * vec4(pos, 1.0);
   color = aColor;
   texCoord = aTex;
   normal = normalize(aNormal);
}