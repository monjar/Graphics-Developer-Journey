#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include<iostream>
#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<cerrno>



std::string get_file_contents(const char* filename);

class Shader {

public:
	GLuint ID;
	Shader(const char* vertexFile, const char* fragmentFile);

	void Activate();
	void Delete();

private:
	// Checks if the different Shaders have compiled properly
	void CompileErrors(unsigned int shader, const char* type);
};

#endif 
