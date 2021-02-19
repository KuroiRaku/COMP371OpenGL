#include <GL/glew.h>	// include GL Extension Wrangler
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>	// include GLFW helper library
#include <iostream>

#pragma once
class DannModel
{

public:
	DannModel();
	void drawModel(int drawMode);

private:
	void setLetterD(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin);
	void setLetterN(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin);
	void setNumber4(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin);
	void setNumber7(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin);

	GLuint vao_D;
	GLuint vao_N;
	GLuint vao_4;
	GLuint vao_7;
	GLfloat lineSize;
	GLenum mode;
	int indiciesD;
	int indiciesN;
	int indicies4;
	int indicies7;
};
