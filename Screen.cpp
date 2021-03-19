#include "Screen.h"
#include <time.h>
Screen::Screen()
{
	GLfloat xOrigin = 0.0f;
	GLfloat yOrigin = 0.0f;
	GLfloat zOrigin = 0.0f;
	GLfloat distance = 2.5f;


}

void Screen::drawModel(int drawMode, Texture* texture)
{
	texture->Bind();
	drawScreen(0, 0, 0);
	texture->Unbind();
}

void Screen::drawScreen(float x, float y, float z)
{
	Cube stageFloor = Cube(2, 3, 0, 8, 16, 0);
	stageFloor.drawModel();
}