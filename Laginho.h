#include <glad/glad.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library
#include <iostream>
#include "Texture.h";

#pragma once
class LaginhoModel
{

public:
	LaginhoModel();
	void drawModel(int drawMode, Texture* boxTexture, Texture* metalTexture, float shearX, float shearY);

private:
	void setLetterA(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin, float shearX, float shearY);
	void setLetterH(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin, float shearX, float shearY);
	void setNumber4(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin, float shearX, float shearY);
	void setNumber0(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin, float shearX, float shearY);


	GLuint vao_A;
	GLuint vao_H;
	GLuint vao_4;
	GLuint vao_0;
	GLfloat distance;
	GLfloat lineSize;
	GLenum mode;
};

