#include <glad/glad.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library
#include <iostream>
#include "Shader.h"
#include "Cylinder.h"
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Cone.h"

#pragma once
class Lines3d
{

public:
	Lines3d();

	void drawLines(Shader* shader, glm::mat4 objectMatrix);

	Cylinder cylinderX;
	Cone coneX;
	Cylinder cylinderY;
	Cone coneY;
	Cylinder cylinderZ;
	Cone coneZ;

	glm::mat4 matrix_X;
	glm::mat4 matrix_Y;
	glm::mat4 matrix_Z;

	glm::mat4 matrix_X_Cone;
	glm::mat4 matrix_Y_Cone;
	glm::mat4 matrix_Z_Cone;

};
