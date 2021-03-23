#pragma once
#include <glad/glad.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library
#include <iostream>
#include "Texture.h"

#pragma once
class LeCherngModel
{

public:
	LeCherngModel();
	void drawModel(int drawMode, Texture* boxTexture, Texture* metalTexture, float shearX, float shearY);

private:
	void setLetterL(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin, float shearX, float shearY);
	void setLetterG(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin, float shearX, float shearY);
	void setNumber4(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin, float shearX, float shearY);
	void setNumber4_2(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin, float shearX, float shearY);

	GLuint vao_L;
	GLuint vao_G;
	GLuint vao_4;
	GLuint vao_4_2;
	GLfloat lineSize;
	GLfloat distance;
	GLenum mode;
	int indiciesL;
	int indiciesG;
};