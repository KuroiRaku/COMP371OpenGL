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
	void drawModel(Texture* boxTexture, Texture* metalTexture, Shader* shader, glm::mat4 objectMatrix);

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

	Cube cube1;
	Cube cube2;
	Cube cube3;
	Cube cube4;
	Cube cube5;
	Cube cube6;
};


