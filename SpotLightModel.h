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
	void drawModel(Shader& shader, glm::mat4 objectMatrix);
	SpotLightModel(GLfloat centerX, GLfloat centerY, GLfloat centerZ);

	Cube cube = Cube(0.5f, 0.5f, 0, 1.0f, 1.0f, 1.0f);
	Cylinder cylinder = Cylinder(3.0f, 1.0f, 0.1f);

	
};

