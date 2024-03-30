#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<vector>

#include<string>


#include"Texture.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"


class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;


	VAO vao;
	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);
	// Draws the mesh
	void Draw
	(
		Shader& shader,
		Camera& camera,
		glm::mat4 matrix = glm::mat4(1.0f),
		glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
	);
};
#endif