#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>


int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL Learning", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create window =(";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();

	glViewport(0, 0, 800, 800);
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}