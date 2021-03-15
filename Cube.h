#pragma once
#include <glad/glad.h>	
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Cube
{
	
public:
	GLuint vao_Cube;
	int indiciesC;
	void drawModel();
	Cube(float x, float y, float z, float tallNess);
	Cube() {};
	void SetCube(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat edgeLength, GLfloat tallNess);
	glm::mat4 cubeMatrix = glm::mat4(1.0f);
};

