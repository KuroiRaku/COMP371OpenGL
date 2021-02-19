#include "LModel.h"
using namespace std;


LModel::LModel() {
	GLfloat xOrigin = 0.0f;
	GLfloat yOrigin = 0.0f;
	GLfloat zOrigin = 0.0f;

	GLfloat distance = 2.5f;

	leftSide = Sphere(0, 0, 0, 0.25f, 1.0f);
	bottomSide = Cube(0, 0, 0, 0.5f, 1.f, 0.25f);

	sphereMatrix = glm::rotate(sphereMatrix, glm::radians(90.f), glm::vec3(-1, 0, 0));

	
}

void LModel::drawModel(int drawMode, Shader* shader, glm::mat4 objectMatrix)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	drawLetter(0, 0, 0, shader, objectMatrix);
}

void LModel::drawLetter(float x, float y, float z, Shader* shader, glm::mat4 objectMatrix)
{
	
	Cube bottom = Cube(0, 0, 0, 0.5f, 1.f, 0.25f);
	bottom.drawModel();
	bottom = Cube(1, 0, 0, 0.5f, 1.f, 0.25f);
	bottom.drawModel();

	Sphere side = Sphere(-1, 1, 0, 0.25, 1);
	side.draw();
	Sphere side2 = Sphere(-1, 2, 0, 0.25, 1);
	side.draw();

}
