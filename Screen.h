#include <glad/glad.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library
#include <iostream>
#include "../Cube.h"
#pragma once
class Screen
{

public:
	Screen();
	void drawModel(int drawMode);
	void drawScreen(float x, float y, float z);
};