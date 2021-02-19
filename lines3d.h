#include <GL/glew.h>	// include GL Extension Wrangler
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>	// include GLFW helper library
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
