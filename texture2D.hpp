#include "texture.hpp"

class Texture2D : public Texture
{
public:

	Texture2D(const char* filename, int channelCount, GLenum format);

	void setParameter(GLenum pname, GLint param, Type type) const;

	void bind() const override;

	void unbind() const override;


private:



};