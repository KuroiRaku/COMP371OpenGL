#include <glad/glad.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library
#include <iostream>
#include "Shader.h"
#include "Cylinder.h"
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Cone.h"
#include "Texture.h"
#pragma once
class Lines3d
{

public:
	Lines3d();

	void drawLines(Shader* shader, glm::mat4 objectMatrix, Texture* texture);

	Cylinder cX;
	Cylinder cZ;
	Cylinder cY;
	Cone coneX;
	Cone coneY;
	Cone coneZ;
	glm::mat4 m_X;
	glm::mat4 m_Y;
	glm::mat4 m_Z;
	glm::mat4 m_X_cone;
	glm::mat4 m_Y_cone;
	glm::mat4 m_Z_cone;

};
