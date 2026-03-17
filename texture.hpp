#include "stb_image.h"

#ifndef GLAD_H
#define GLAD_H
#include <glad/glad.h>
#endif

#ifndef GLFW_H
#define GLFW_H
#include <glfw/glfw3.h>
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

enum Type
{
	FLOAT,
	INT
};

class Texturec
{
public:

	virtual void setParameter(GLenum pname, GLint param, Type type) const = 0;

	void activate(GLenum slot) const { glActiveTexture(slot); }

	virtual void bind() const = 0;
	virtual void unbind() const = 0;

	int getWidth() const { return width; }
	int getHeight() const { return height; }

	virtual ~Texturec() {};

protected:
	unsigned int ID;
	int width, height, nrChannels;
	GLenum detectedFormat;

private:

};