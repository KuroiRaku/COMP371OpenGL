#include <glad/glad.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library
#include "Texture.h"
#include "LoadedCube.h"
#include "Cube2.h"
#include "Cube.h"

#pragma once

class GroundPlane2
{
public:
	GroundPlane2();

	void drawGround(Texture* tileTexture);
	Cube ground = Cube(-25, -25, 0, 50, 50, 0);
	glm::mat4 groundMatrix = glm::mat4(1.0f);

	unsigned int planeVAO;
};


