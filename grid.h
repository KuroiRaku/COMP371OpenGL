#include <GL/glew.h>	// include GL Extension Wrangler
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>	// include GLFW helper library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#pragma once
class Grid
{
public:
	Grid();
	GLuint getVAO();
	int getLength();
	void drawGrid();

private:
	GLuint vao;
	int length;
};
