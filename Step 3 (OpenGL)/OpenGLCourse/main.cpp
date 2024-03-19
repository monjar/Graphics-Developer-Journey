#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"




// Vertices coordinates
GLfloat vertices[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // Lower left corner
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 0.0f, 1.0f, 0.0f,1.0f, // Lower right corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f ,0.0f, 0.0f, 1.0f,1.0f, // Upper corner
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,1.0f, 0.0f, 0.0f,1.0f,
	0.5f / 2,  0.5f * float(sqrt(3)) / 6, 0.0f,0.0f, 1.0f, 0.0f,1.0f,
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f, 0.0f, 0.0f, 1.0f,1.0f
};


GLuint indices[] = {


	0,3,5,
	3,2,4,
	5, 4, 1
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

	vao1.LinkAttrib(vbo1, 0, 3, GL_FLOAT, 7 * sizeof(float), (void*)0);
	vao1.LinkAttrib(vbo1, 1, 4, GL_FLOAT, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	vao1.Unbind();
	vbo1.Unbind();
	ebo1.Unbind();

	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.07f, 0.07f, 0.2f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();
		vao1.Bind();
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
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