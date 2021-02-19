#include <GL/glew.h>	// include GL Extension Wrangler
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>	// include GLFW helper library
#include <iostream>

#pragma once
class AlessandroModel
{

public:
	AlessandroModel();
	void drawModel(int drawMode);

private:
	void setLetterO(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin);
	void setLetterA(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin);
	void setNumber4(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin);
	void setNumber1(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin);

	GLuint vao_O;
	GLuint vao_A;
	GLuint vao_4;
	GLuint vao_1;
	GLfloat lineSize;
	GLenum mode;
};
