#include <glad/glad.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library
#include <iostream>
#include "../Cube.h"
#include "../sphere.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#pragma once
class LModel
{

public:
	LModel();
	void drawModel(int drawMode, Shader* shader, glm::mat4 objectMatrix);
	void drawLetter(float x, float y, float z, Shader* shader, glm::mat4 objectMatrix);
	
	//for the side
	glm::mat4 sphereMatrix = glm::mat4(1.f);
	//for the bottom
	glm::mat4 cubeMatrix = glm::mat4(1.f);

	Sphere leftSide;
	Cube bottomSide;
};
