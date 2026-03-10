#ifndef SHADER_H
#define SHADER_H

#ifndef GLAD_H
#define GLAD_H
#include <glad/glad.h>
#endif

#ifndef GLM_H
#define GLM_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat2;
using glm::mat3;
using glm::mat4;
#endif

#ifndef GENERICS_H
#define GENERICS_H
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#endif

using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::stringstream;

class Shader
{
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath);

	void use() const;

	void setBool(const string& name, bool value) const;
	void setInt(const string& name, int value) const;
	void setFloat(const string& name, float value) const;
	void setVec3(const string& name, vec3& vec) const;
	void setMat2(const string& name, mat2& mat) const;
	void setMat3(const string& name, mat3& mat) const;
	void setMat4(const string& name, mat4& mat) const;

private:
};

#endif