#include "Laginho.h"
using namespace std;


LaginhoModel::LaginhoModel() {

}

void LaginhoModel::drawModel(int drawMode, Shader* shader, glm::mat4 objectMatrix)
{


	drawLetter(0, 0, 0, shader, objectMatrix);
}

void LaginhoModel::drawLetter(float x, float y, float z, Shader* shader, glm::mat4 objectMatrix)
{


Cube cube = Cube(-1, 0, 0,4);
	cube.drawModel();


	cube = Cube(1, 0, 0,4);
	cube.drawModel();
	

	Sphere s = Sphere(0, 0, 0, 1, 0.25);
	s.draw();
	s = Sphere(0, 17, 0, 1, 0.25);
	s.draw();


	



}
