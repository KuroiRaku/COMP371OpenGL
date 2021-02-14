#pragma once
#include <glad/glad.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library
#include <iostream>

#pragma once
class LeCherngModel
{

public:
	LeCherngModel();
	void drawModel(int drawMode);

private:
	void setLetterL(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin);
	void setLetterG(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin);
	void setNumber4(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin);
	void setNumber4_2(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin);

	GLuint vao_L;
	GLuint vao_G;
	GLuint vao_4;
	GLuint vao_4_2;
	GLfloat lineSize;
	GLenum mode;
	int indiciesL;
	int indiciesG;
};