#include "SModel.h"

using namespace std;


SModel::SModel() {

}

void SModel::drawModel(int drawMode, Texture* boxTexture)
{


	drawLetter(0, 0, 0, boxTexture);
}

void SModel::drawLetter(float x, float y, float z, Texture* boxTexture)
{
	boxTexture->Bind();
	Sphere s = Sphere(0.5, 21, 0, 1.5, 0.25);
	s.draw();
	Cube cube = Cube(-0.5, 3, 0, 2, 0, 0);
	cube.drawModel();
	s = Sphere(0.5, 10, 0, 1.5, 0.25);
	s.draw();
	cube = Cube(1.5, 0, 0, 2, 0, 0);
	cube.drawModel();
	s = Sphere(0.5, -1, 0, 1.5, 0.25);
	s.draw();
	boxTexture->Unbind();
}
