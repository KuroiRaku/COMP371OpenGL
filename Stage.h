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

	Cube stageFloor = Cube(0, 2, 0, 0, 20, 5);
	Cube leg = Cube(0, 0, 0, 2, 0, 0);
	Cube leg2 = Cube(0, 0, 5, 2, 0, 0);
	Cube leg3 = Cube(20, 0, 0, 2, 0, 0);
	Cube leg4 = Cube(20, 0, 5, 2, 0, 0);

	Cube pillar = Cube(19, 2, 0, 10, 0, 0);
	Cube pillar2 = Cube(1, 2, 0, 10, 0, 0);
	Cube beam = Cube(1, 12, 0, 0, 18, 0);
};