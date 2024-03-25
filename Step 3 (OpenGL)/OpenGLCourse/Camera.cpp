#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position) {


	Camera::width = width;
	Camera::height = height;
	Camera::Position = position;
}

void Camera::Matrix(float FOVDeg, float near, float far, Shader& shader, const char* uniform) {
	//Initialize matrices
	glm::mat4 viewMat = glm::mat4(1.0f);
	glm::mat4 projMat = glm::mat4(1.0f);


	viewMat = glm::lookAt(Position, Position + Orientation, Up);
	projMat = glm::perspective(glm::radians(FOVDeg), (float)width / (float)height, near, far);

	GLuint uniLocation = glGetUniformLocation(shader.ID, uniform);

	glUniformMatrix4fv(uniLocation, 1, GL_FALSE, glm::value_ptr(projMat * viewMat));
}