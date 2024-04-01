#ifndef VBO_CLASS_H
#define VBO_CLASS_H


#include<vector>
#include<glm/glm.hpp>
#include<glad/glad.h>



struct Vertex {

	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texCord;
};
class VBO
{
public:
	GLuint ID;
	VBO(std::vector<Vertex>& vertices);


	void Bind();
	void Unbind();
	void Delete();

};



#endif