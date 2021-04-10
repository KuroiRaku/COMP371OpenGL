#pragma once
#include <glad/glad.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library
#include <glm/glm.hpp>
#include <string>

using namespace std;

class Texture
{
private:
	unsigned int m_RendererID;
	string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture(const string& path, bool noRepeat);
	~Texture();
	Texture();
	bool activeTexture;

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
};

