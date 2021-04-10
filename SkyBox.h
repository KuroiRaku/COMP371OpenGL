#include <glad/glad.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library
#include <iostream>
#include "Texture.h"
#include "Cube.h"
#include "sphere.h"
#include "Shader.h"

#pragma once
class SkyBox
{

public:
	SkyBox();
	void drawModel(int drawMode, Texture* boxTexture, Texture* metalTexture, float shearX, float shearY, Shader* shader, glm::mat4 objectMatrix);

private:


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

	Cube cube;

};


