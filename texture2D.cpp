#include "texture2D.hpp"

Texture2D::Texture2D(const char* filename)
{
	glGenTextures(1, &ID);
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);

	bind();


	if (data)
	{
		if (nrChannels == 1)
		{
			detectedFormat = GL_RED;
		}
		else if (nrChannels == 3)
		{
			detectedFormat = GL_RGB;
		}
		else if (nrChannels == 4)
		{
			detectedFormat = GL_RGBA;
		}
		cout << "Channel count: " << nrChannels << endl;
		glTexImage2D(GL_TEXTURE_2D, 0, detectedFormat, width, height, 0, detectedFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		cout << "Successfully generated texture; ID:" << ID << endl;

	}
	else
	{
		cout << "Failed to generate texture; ID:" << ID << endl;
	}

	stbi_image_free(data);
	unbind();
}

void Texture2D::setParameter(GLenum pname, GLint param, Type type) const
{
	if (type == INT)
	{
		glTexParameteri(GL_TEXTURE_2D, pname, param);
	}
	else if (type == FLOAT)
	{
		glTexParameterf(GL_TEXTURE_2D, pname, param);
	}
}

void Texture2D::bind() const
{
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture2D::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, ID);
}
