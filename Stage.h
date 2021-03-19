#include <glad/glad.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library
#include <iostream>
#include "../Cube.h"
#include "Texture.h";
#pragma once
class Stage
{

public:
	Stage();
	void drawModel(int drawMode, Texture* texture);
	void drawStage(float x, float y, float z);




};