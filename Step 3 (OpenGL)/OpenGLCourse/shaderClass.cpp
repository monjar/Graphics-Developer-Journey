#include "shaderClass.h"

std::string get_file_contents(const char* filename) {


	std::ifstream in(filename, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return contents;

	}
	throw(errno);
}


Shader::Shader(const char* vertexFile, const char* fragmentFile) {

	auto vertexStr = get_file_contents(vertexFile);
	auto fragmentStr = get_file_contents(fragmentFile);

	const char* vertexCode = vertexStr.c_str();
	const char* fragmentCode = fragmentStr.c_str();


	//Create a reference to a shader of type vertex
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//loading up the shader with source code
	glShaderSource(vertexShader, 1, &vertexCode, NULL);
	//compiling the loaded shader
	glCompileShader(vertexShader);
	CompileErrors(vertexShader, "VERTEX");

	//Doing the same thing for fragment shader
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragmentCode, NULL);
	glCompileShader(fragShader);
	CompileErrors(fragShader, "FRAGMENT");

	//Create a reference for shader program
	ID = glCreateProgram();

	//Attach and link the 2 shaders to the program
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragShader);
	glLinkProgram(ID);
	CompileErrors(ID, "PROGRAM");

	//Delete the shaders because they are now in the pro	
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);

}


void Shader::Activate() {
	glUseProgram(ID);
}

void Shader::Delete() {
	glDeleteProgram(ID);
}


// Checks if the different Shaders have compiled properly
void Shader::CompileErrors(unsigned int shader, const char* type)
{
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}