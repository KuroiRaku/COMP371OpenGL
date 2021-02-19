#include "LModel.h"
using namespace std;


LModel::LModel() {
	GLfloat xOrigin = 0.0f;
	GLfloat yOrigin = 0.0f;
	GLfloat zOrigin = 0.0f;

	GLfloat distance = 2.5f;

	leftSide = Sphere(0, 0, 0, 0.25f, 1.0f);
	bottomSide = Cube(0, 0, 0, 0.5f, 1.f, 0.25f);

	sphereMatrix = glm::rotate(sphereMatrix, glm::radians(90.f), glm::vec3(1, 0, 0));

	
}

void LModel::drawModel(int drawMode, Shader* shader, glm::mat4 objectMatrix)
{

	drawLetter(0, 0, 0, shader, objectMatrix);
}

void LModel::drawLetter(float x, float y, float z, Shader* shader, glm::mat4 objectMatrix)
{
	GLuint mm = shader->GetUniformLocation("mm");
	//Rotation of sphere is done like so
	sphereMatrix = objectMatrix * sphereMatrix;
	glUniformMatrix4fv(mm, 1, 0, glm::value_ptr(sphereMatrix));
	leftSide.draw();
	//Cancelling rotation for next 
	cubeMatrix = objectMatrix * cubeMatrix;
	glUniformMatrix4fv(mm, 1, 0, glm::value_ptr(cubeMatrix));
	bottomSide.drawModel();
}
