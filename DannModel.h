#include <glad/glad.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library
#include <iostream>
#include "Texture.h"
#include "Cube.h"
#include "sphere.h"
#include "Shader.h"

#pragma once
class DannModel
{

public:
	DannModel();
	void drawModel(int drawMode, Texture* boxTexture, Texture* metalTexture, float shearX, float shearY, Shader* shader, glm::mat4 objectMatrix);

private:
	void setLetterD(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin, float shearX, float shearY);
	void setLetterN(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin, float shearX, float shearY);
	void setNumber4(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin, float shearX, float shearY);
	void setNumber7(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin, float shearX, float shearY);

	GLuint vao_D;
	GLuint vao_N;
	GLuint vao_4;
	GLuint vao_7;
	GLfloat lineSize;
	GLfloat distance;
	GLenum mode;
	int indiciesD;
	int indiciesN;
	int indicies4;
	int indicies7;
};


