#include <glad/glad.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library
#include <iostream>
#include "sphere.h"
#pragma once
class DrawModel
{

public:
	DrawModel();
	void drawModel(int drawMode);
	void DrawCube(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat edgeLength);
	void setLetterK();
	void setLetterA();
	void setLetterO();
	void setLetterU();
	void setLetterS();

private:

/*
GLuint vao_K;
	GLuint vao_A;
	GLuint vao_O;
	GLuint vao_U;
	GLuint vao_S;

*/
	Sphere sphere = Sphere();
	GLuint vao_Cube;
	GLfloat lineSize;
	GLenum mode;
};
#pragma once
