#include "Laginho.h"
#include "Cube.h"
#include "sphere.h"

LaginhoModel::LaginhoModel() {
	GLfloat xOrigin = 0.0f;
	GLfloat yOrigin = 0.0f;
	GLfloat zOrigin = 0.0f;

	lineSize = 0.4f * 2;

	distance = 2.0f;

	
	mode = GL_TRIANGLES;
}

void LaginhoModel::drawModel(int drawMode, Texture* boxTexture, Texture* metalTexture, float shearX, float shearY)
{

	if (drawMode == 0) {
		mode = GL_POINTS;
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	}
	else if (drawMode == 1)
	{
		mode = GL_TRIANGLES;
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		mode = GL_TRIANGLES;
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	boxTexture->Bind();

	Cube cube = Cube(-1, 0, 0, 4, 0, 0);
	cube.drawModel();


	cube = Cube(1, 0, 0, 4, 0, 0);
	cube.drawModel();


	Sphere s = Sphere(0, 0, 0, 1, 0.25);
	s.draw();
	s = Sphere(0, 17, 0, 1, 0.25);
	s.draw();

	metalTexture->Unbind();
}
