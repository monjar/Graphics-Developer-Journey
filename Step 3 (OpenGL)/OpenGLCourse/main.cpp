#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>


// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";



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


	// Vertices coordinates
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f ,// Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
		0.5f / 2,  0.5f * float(sqrt(3)) / 6, 0.0f,
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,
	};


	GLuint indices[] = {


		0,3,5,
		3,2,4,
		5, 4, 1
	};

	//Initialize Glad
	gladLoadGL();

	//Setting the viewport size
	glViewport(0, 0, 800, 800);

	//Create a reference to a shader of type vertex
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//loading up the shader with source code
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//compiling the loaded shader
	glCompileShader(vertexShader);

	//Doing the same thing for fragment shader
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragShader);

	//Create a reference for shader program
	GLuint shaderProgram = glCreateProgram();

	//Attach and link the 2 shaders to the program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);

	//Delete the shaders because they are now in the pro	
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);


	GLuint VAO, VBO, IBO;
	// The ordering is important
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	glfwSwapBuffers(window);
	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.07f, 0.07f, 0.2f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
	glDeleteProgram(shaderProgram);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}