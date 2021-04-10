#pragma once
#include <glad/glad.h>    
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Cylinder.h"
#include "Cube.h"

class SpotLight
{
public:
	void drawModel(GLfloat centerX, GLfloat centerY, GLfloat centerZ);
	SpotLight();
};

