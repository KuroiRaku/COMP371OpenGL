#pragma once
#include <glad/glad.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library
#include <iostream>
class Cube
{
	
public:
	GLuint vao_Cube;
	int indiciesC;
	void drawModel();
	Cube(float x, float y, float z);
	Cube() {};
	void SetCube(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat edgeLength);
	
};

