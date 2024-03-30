#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec2 aTex;

out vec4 color;
out vec2 texCoord;
out vec3 normal;
out vec3 pos;

uniform mat4 camMatrix;
uniform mat4 model;

uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;
void main()
{
	pos =vec3(model * translation * -rotation * scale * vec4(aPos, 1.0f));
   gl_Position = camMatrix * vec4(pos, 1.0);
   color = aColor;
   texCoord =  mat2(0.0, -1.0, 1.0, 0.0) * aTex;
   normal = normalize(aNormal);
}