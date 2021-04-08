#include <glad/glad.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library
#include <iostream>
#include "../Cube.h"
#include "../sphere.h"
#include "Shader.h"
#include "Texture.h"
#pragma once
class SModel
{

public:
	SModel();
	void drawModel(int drawMode, Texture* boxTexture);
	void drawLetter(float x, float y, float z, Texture* boxTexture);




};

