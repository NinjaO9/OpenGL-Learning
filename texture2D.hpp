#include "texture.hpp"

class Texture2D : public Texturec
{
public:

	Texture2D(const char* filename);

	void setParameter(GLenum pname, GLint param, Type type) const;

	void bind() const override;

	void unbind() const override;


private:



};