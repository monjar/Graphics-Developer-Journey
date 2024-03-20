#ifndef EBO_CLASS_H
#define EBO_CLASS_H


#include<glad/glad.h>

class EBO
{
public:
	GLuint ID;
	EBO(GLuint* vertices, GLsizeiptr size);


	void Bind();
	void Unbind();
	void Delete();

};



#endif