#include <glad/glad.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library
#include "Cube.h"
#include "Sphere.h"
#include <iostream>

#pragma once
class QuizModelsAlessandro
{
public:
	QuizModelsAlessandro();
	void drawLetterK();
	void drawLetterR();
	void drawLetterE();
	void drawLetterS();
	void drawLetterL();
	void drawLetterI();
	void setLetterK(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin);
	void setLetterR(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin);
	void setLetterE(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin);
	void setLetterS(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin);
	void setLetterL(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin);
	void setLetterI(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin);

private:


	GLfloat lineSize;
};

