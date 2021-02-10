#include <glad/glad.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library
#include <iostream>

#pragma once
class AlessandroModel
{

public:
	AlessandroModel();
	void drawModel();

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
};

