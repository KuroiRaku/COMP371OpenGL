#include <glad/glad.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library
#include <iostream>
#include "Texture.h";

#pragma once
class AlessandroModel
{

public:
	AlessandroModel();
	void drawModel(int drawMode, Texture * boxTexture, Texture * metalTexture, float shearX, float shearY, bool shearTransformation);

private:
	void setLetterO(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin, float shearX, float shearY);
	void setLetterA(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin, float shearX, float shearY);
	void setNumber4(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin, float shearX, float shearY);
	void setNumber1(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin, float shearX, float shearY);

	GLuint vao_O;
	GLuint vao_A;
	GLuint vao_4;
	GLuint vao_1;
	GLfloat lineSize;
	GLfloat distance;
	GLenum mode;
};
