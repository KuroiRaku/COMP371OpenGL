#include <glad/glad.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library
#include "Texture.h"
#include "LoadedCube.h"
#include "Cube2.h"

#pragma once

class GroundPlain
{
public:
	GroundPlain();
	void drawGround(Texture * tileTexture);
	Cube2 ground = Cube2(-25, -25, 0, 50, 50, 0);
	glm::mat4 groundMatrix = glm::mat4(1.0f);
};

