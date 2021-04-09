#include "Stage.h"
using namespace std;


Stage::Stage()
{
	GLfloat xOrigin = 0.0f;
	GLfloat yOrigin = 0.0f;
	GLfloat zOrigin = 0.0f;
	GLfloat distance = 2.5f;


}

void Stage::drawModel(int drawMode, Texture* texture,  Shader* shader, glm::mat4 objectMatrix)
{
	texture->Bind();
	drawStage(0, 0, 0, shader, objectMatrix);
	texture->Unbind();
}

void Stage::drawStage(float x, float y, float z, Shader* shader, glm::mat4 objectMatrix)
{
	Cube stageFloor = Cube(0, 2, 0,0, 20, 5);
	stageFloor.drawModel();
	Cube leg = Cube(0, 0, 0, 2, 0, 0);
	leg.drawModel();
	leg = Cube(0, 0, 5, 2, 0, 0);
	leg.drawModel();
	leg = Cube(20, 0, 0, 2, 0, 0);
	leg.drawModel();
	leg = Cube(20, 0, 5, 2, 0, 0);
	leg.drawModel();


	Cube pillar = Cube(19, 2, 0, 10, 0, 0);
	pillar.drawModel();
    pillar = Cube(1, 2, 0, 10, 0, 0);
	pillar.drawModel();

	Cube beam = Cube(1, 12, 0, 0, 18, 0);
	beam.drawModel();
}
