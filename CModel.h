#include "../Cube.h"
#include "../sphere.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#pragma once
class CModel
{

public:
	CModel();
	void drawModel(int drawMode, Shader* shader, glm::mat4 objectMatrix);
	void drawLetter(float x, float y, float z, Shader* shader, glm::mat4 objectMatrix);
};

