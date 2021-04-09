#include <glad/glad.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library
#include <iostream>
#include "../Cube.h"
#include "Texture.h";
#include "Shader.h"
#pragma once
class Stage
{

public:
	Stage();
	void drawModel(int drawMode, Texture* texture , Shader* shader, glm::mat4 objectMatrix);
	void drawStage(float x, float y, float z, Shader* shader, glm::mat4 objectMatrix);




};