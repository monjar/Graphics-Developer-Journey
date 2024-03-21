#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"




// Vertices coordinates
GLfloat vertices[] =
{
	-0.5f, -0.5f , 0.0f,	1.0f, 0.0f, 0.0f, 1.0f,		0.0f, 0.0f,
	-0.5f, 0.5f , 0.0f,		0.0f, 1.0f, 0.0f,1.0f, 		0.0f, 1.0f,
	0.5f, 0.5f , 0.0f,		0.0f, 0.0f, 1.0f,1.0f,		1.0f, 1.0f,
	0.5f, -0.5f , 0.0f,		1.0f, 0.0f, 0.0f,1.0f,		1.0f, 0.0f,
};


GLuint indices[] = {
	0,2,1,
	0,3,2
};

GLFWwindow* initWindow() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	return glfwCreateWindow(800, 800, "OpenGL Learning", NULL, NULL);
}



int main() {

	
	GLFWwindow* window = initWindow();
	if (window == NULL) {
		std::cout << "Failed to create window =(";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);




	//Initialize Glad
	gladLoadGL();

	//Setting the viewport size
	glViewport(0, 0, 800, 800);

	Shader shaderProgram("default.vert", "default.frag");

	VAO vao1;
	vao1.Bind();
	VBO vbo1(vertices, sizeof(vertices));
	EBO ebo1(indices, sizeof(indices));

	vao1.LinkAttrib(vbo1, 0, 3, GL_FLOAT, 9 * sizeof(float), (void*)0);
	vao1.LinkAttrib(vbo1, 1, 4, GL_FLOAT, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	vao1.LinkAttrib(vbo1, 2, 2, GL_FLOAT, 9 * sizeof(float), (void*)(7 * sizeof(float)));
	vao1.Unbind();
	vbo1.Unbind();
	ebo1.Unbind();

	GLuint uniformId = glGetUniformLocation(shaderProgram.ID, "scale");


	int imgWidth, imgHeight, numColorChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load("birdy.png", &imgWidth, &imgHeight, &numColorChannels, 0);

	GLuint texture;
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//S ==> X / T ==> Y / I ==> Z
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, some4d vector as color);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0");
	shaderProgram.Activate();
	glUniform1i(tex0Uni, 0);
	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.07f, 0.07f, 0.2f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();
		glUniform1f(uniformId, 0.5);
		glBindTexture(GL_TEXTURE_2D, texture);


		vao1.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	vao1.Delete();
	vbo1.Delete();
	ebo1.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}