#include "CModel.h"

CModel::CModel()
{
}

void CModel::drawModel(int drawMode, Shader* shader, glm::mat4 objectMatrix)
{
	drawLetter(0, 0, 0, shader, objectMatrix);
}

void CModel::drawLetter(float x, float y, float z, Shader* shader, glm::mat4 objectMatrix)
{
	Cube cube = Cube(0, 0, 0, 0.5f, 1.f, 0.25f);
	cube.drawModel();
	cube = Cube(1, 0, 0, 0.5f, 1.f, 0.25f);
	cube.drawModel();

	cube = Cube(0, 5, 0, 0.5f, 1.f, 0.25f);
	cube.drawModel();
	cube = Cube(1, 5, 0, 0.5f, 1.f, 0.25f);
	cube.drawModel();

	Sphere side = Sphere(-1, 1, 0, 0.25, 1);
	side.draw();
	Sphere side2 = Sphere(-1, 2, 0, 0.25, 1);
	side.draw();
}
