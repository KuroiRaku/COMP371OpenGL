#pragma once
#include <glad/glad.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library
#include <iostream>
#include "Texture.h"

#include <glad/glad.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library
#include <iostream>
#include "Cube.h"
#include "sphere.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class LModel
{

public:
	LModel();
	void drawLetter(Texture* boxTexture, Shader* shader, glm::mat4 objectMatrix);

	//for the side
	glm::mat4 sphereMatrix = glm::mat4(1.f);
	//for the bottom
	glm::mat4 cubeMatrix = glm::mat4(1.f);

	Cube bottomSide = Cube(0, 0, 0, 0.5f, 1.f, 0.25f);
	Cube bottom = Cube(1, 0, 0, 0.5f, 1.f, 0.25f);
	Sphere side2 = Sphere(-1, 2, 0, 0.25, 1);
	Sphere side = Sphere(-1, 1, 0, 0.25, 1);
};