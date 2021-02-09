#include <glad/glad.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library
#include <iostream>

#pragma once
class Lines3d
{

public:
	Lines3d();
	int getIndicesSize();
	GLuint getVAO();
	void drawLines();
	GLuint shaderProgram;

private:
	GLuint vao;
	void compileShader();
};

