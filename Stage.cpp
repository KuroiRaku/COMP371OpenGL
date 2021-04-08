#include "Stage.h"

using namespace std;


Stage::Stage()
{
	GLfloat xOrigin = 0.0f;
	GLfloat yOrigin = 0.0f;
	GLfloat zOrigin = 0.0f;
	GLfloat distance = 2.5f;


}

void Stage::drawModel(int drawMode, Texture* texture)
{
	texture->Bind();
	drawStage(0, 0, 0);
	texture->Unbind();
}

void Stage::drawStage(float x, float y, float z)
{
	
	stageFloor.drawModel();
	leg1.drawModel();
	leg2.drawModel();
	leg3.drawModel();
	leg4.drawModel();
	
	pillar.drawModel();
	pillar2.drawModel();
	beam.drawModel();
}
