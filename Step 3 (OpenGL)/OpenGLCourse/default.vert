#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTex;
out vec4 color;
out vec2 texCoord;
uniform float scale;


uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;
void main()
{
   gl_Position = projMat * viewMat * modelMat * vec4(aPos, 1.0);
   color = aColor;
   texCoord = aTex;
}