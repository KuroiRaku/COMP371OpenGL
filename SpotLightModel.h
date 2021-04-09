#pragma once
#include <glad/glad.h>    
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Cube.h"
#include "Cylinder.h"

class SpotLightModel
{
public:
	void drawModel(GLfloat centerX, GLfloat centerY, GLfloat centerZ);
	SpotLightModel();
};

