#pragma once

#include <glad/glad.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library
#include <iostream>
#include "../Cube.h"
#include "Texture.h";
#include "LoadedCube.h"
#include "Cube2.h"

class Stage
{

public:
	Stage();
	void drawModel(int drawMode, Texture* texture);
	void drawStage(float x, float y, float z);

	Cube2 stageFloor = Cube2(0, 2, 0, 0, 20, 5);
	Cube2 leg1 = Cube2(0, 0, 0, 2, 0, 0);
	Cube2 leg2 = Cube2(0, 0, 5, 2, 0, 0);
	Cube2 leg3 = Cube2(20, 0, 0, 2, 0, 0);
	Cube2 leg4 = Cube2(20, 0, 5, 2, 0, 0);

	Cube2 pillar = Cube2(19, 2, 0, 10, 0, 0);
	Cube2 pillar2 = Cube2(1, 2, 0, 10, 0, 0);
	Cube2 beam = Cube2(1, 12, 0, 0, 18, 0);

};