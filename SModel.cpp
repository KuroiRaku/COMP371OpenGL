#include "SModel.h"

using namespace std;


SModel::SModel() {

}

void SModel::drawModel(int drawMode, Shader* shader, glm::mat4 objectMatrix)
{


	drawLetter(0, 0, 0, shader, objectMatrix);
}

void SModel::drawLetter(float x, float y, float z, Shader* shader, glm::mat4 objectMatrix)
{
	
	Sphere s = Sphere(0.5, 21, 0,1.5, 0.25);
	s.draw();
	Cube cube = Cube(-0.5, 3, 0, 2);
	cube.drawModel();

	s = Sphere(0.5, 10, 0, 1.5, 0.25);
	s.draw();

	cube = Cube(1.5, 0, 0, 2);
	cube.drawModel();


	s = Sphere(0.5, -1, 0, 1.5, 0.25);
	s.draw();
}
