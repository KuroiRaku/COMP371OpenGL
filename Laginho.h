#include <glad/glad.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library
#include <iostream>

#pragma once
class LaginhoModel
{

public:
	LaginhoModel();
	void drawModel(int drawMode);

private:
	void setLetterA(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin);
	void setLetterH(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin);
	void setNumber4(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin);
	void setNumber0(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin);


	GLuint vao_A;
	GLuint vao_H;
	GLuint vao_4;
	GLuint vao_0;
	GLfloat lineSize;
	GLenum mode;
};

