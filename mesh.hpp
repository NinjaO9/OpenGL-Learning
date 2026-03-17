#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "shader.hpp"

using std::string;
using std::vector;

using glm::vec2;
using glm::vec3;

struct Vertex {
	vec3 Position;
	vec3 Normal;
	vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	string type;
	string path;
};

class Mesh {
public:
	
	vector<Vertex> verticies;
	vector<unsigned int> indicies;
	vector<Texture> textures;

	Mesh(vector<Vertex> verticies, vector<unsigned int> indicies, vector<Texture> textures);

	void Draw(Shader& shader);

private:

	unsigned int VAO, VBO, EBO;

	void setupMesh();
};