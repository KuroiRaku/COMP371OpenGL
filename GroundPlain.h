#include <glad/glad.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library
#include "Texture.h"
#include "Cube.h"

#pragma once

class GroundPlain
{
public:
	GroundPlain();
	void drawGround(Texture * tileTexture);

private:
	GLuint vao_ground;
	Cube plane = Cube(-25, -25, -2, 75, 75, 1);
};

