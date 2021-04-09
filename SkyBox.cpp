#include "SkyBox.h"

using namespace std;


SkyBox::SkyBox() {
	GLfloat xOrigin = 0.0f;
	GLfloat yOrigin = 0.0f;
	GLfloat zOrigin = 0.0f;

	lineSize = 0.4f * 2;

	distance = 2.5f;




	mode = GL_TRIANGLES;
}

void SkyBox::drawModel(int drawMode, Texture* boxTexture, Texture* metalTexture, float shearX, float shearY, Shader* shader, glm::mat4 objectMatrix)
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
	Cube cube = Cube(0, 0, 0, 2, 75, 75);
	cube.drawModel();
	 cube = Cube(0, 75, 0, 2, 75, 75);
	cube.drawModel();
	 cube = Cube(0, 0, 0, 75, 0, 75);
	cube.drawModel();
	cube = Cube(75, 0, 0, 75, 0, 75);
	cube.drawModel();
	cube = Cube(0, 0, 75, 75, 75, 0);
	cube.drawModel();
	cube = Cube(0, 0, 0, 75, 75, 0);
	cube.drawModel();
	metalTexture->Unbind();
}