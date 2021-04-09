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
	stageFloor.drawModel();
	leg.drawModel();
	leg2.drawModel();
	leg3.drawModel();
	leg4.drawModel();

	pillar.drawModel();
	pillar2.drawModel();

	beam.drawModel();
}
