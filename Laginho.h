#include <glad/glad.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library
#include <iostream>
#include "../Cube.h"
#include "../sphere.h"
#include "Shader.h"
#pragma once
class LaginhoModel
{

public:
	LaginhoModel();
	void drawModel(int drawMode, Shader* shader, glm::mat4 objectMatrix);
	void drawLetter(float x, float y, float z, Shader* shader, glm::mat4 objectMatrix);




};
