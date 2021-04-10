#include <glad/glad.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library
#include <iostream>
#include "Texture.h";
#include "Shader.h"
#include "Cube.h"
#include "sphere.h"

#pragma once
class CModel
{

public:
	CModel();
	void drawModel(Texture * boxTexture, Shader* shader, glm::mat4 objectMatrix);

private:

	GLuint vao_O;
	GLuint vao_A;
	GLuint vao_4;
	GLuint vao_1;
	GLfloat lineSize;
	GLfloat distance;
	GLenum mode;

	Cube cube = Cube(0, 0, 0, 0.5f, 1.f, 0.25f);
	Cube cube2 = Cube(1, 0, 0, 0.5f, 1.f, 0.25f);
	Cube cube3 = Cube(0, 5, 0, 0.5f, 1.f, 0.25f);
	Cube cube4 = Cube(1, 5, 0, 0.5f, 1.f, 0.25f);
	Sphere side = Sphere(-1, 1, 0, 0.25, 1);
	Sphere side2 = Sphere(-1, 2, 0, 0.25, 1);
};
