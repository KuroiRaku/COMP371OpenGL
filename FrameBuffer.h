#pragma once
#include <glad/glad.h>

class FrameBuffer {
public:

	void create();
	void bind();
	void unbind();
	void destroy();
	void bindTexture();
	void unbindTexture();

	GLuint getFBOID() { return m_fboID; }
	GLuint getTextureID() { return m_textureID; }

private:

	GLuint m_fboID = 0;
	GLuint m_textureID = 0;

};
