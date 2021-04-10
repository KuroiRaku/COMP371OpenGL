#include <glad/glad.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library
#include <iostream>
#include "../Cube.h"
#include "../sphere.h"
#include "Shader.h"
#include "Texture.h"
#pragma once
class EModel
{

public:
	EModel();
	void drawLetter(Texture* boxTexture, Shader* shader, glm::mat4 objectMatrix);

	Cube cube = Cube(0, 0, 0, 0.5f, 1.f, 0.25f);
	Cube cube2 = Cube(1, 0, 0, 0.5f, 1.f, 0.25f);
	Cube cube3 = Cube(0, 3, 0, 0.5f, 1.f, 0.25f);
	Cube cube4 = Cube(1, 3, 0, 0.5f, 1.f, 0.25f);
	Cube cube5 = Cube(0, 5, 0, 0.5f, 1.f, 0.25f);
	Cube cube6 = Cube(1, 5, 0, 0.5f, 1.f, 0.25f);

	Sphere side = Sphere(-1, 1, 0, 0.25, 1);
	Sphere side2 = Sphere(-1, 2, 0, 0.25, 1);
};

