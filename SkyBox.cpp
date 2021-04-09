#include "SkyBox.h"

using namespace std;


SkyBox::SkyBox() {
	GLfloat xOrigin = 0.0f;
	GLfloat yOrigin = 0.0f;
	GLfloat zOrigin = 0.0f;

	lineSize = 0.4f * 2;

	distance = 2.5f;

	GLfloat cubeSizing = (lineSize * 75*2); // div by 2 because each side
	GLfloat cP = cubeSizing / 2.0f;

	//(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat tallNess, GLfloat width, GLfloat length)
	/*
	cube1 = Cube(0, 0, -cubePositioning, 2, cubeSizing, cubeSizing); // bottom
	cube2 = Cube(0, 0, 0, cubeSizing, 0, cubeSizing);
	cube3 = Cube(cubeSizing, 0, 0, cubeSizing, 0, cubeSizing);
	cube4 = Cube(0, cubePositioning, 0, 2, cubeSizing, cubeSizing); // top
	cube5 = Cube(0, 0, cubeSizing, cubeSizing, cubeSizing, 0);
	cube6 = Cube(0, 0, 0, cubeSizing, cubeSizing, 0); // side


	cube1 = Cube(0, -1*cubePositioning, 0,		0.5, cubeSizing, cubeSizing);
	cube2 = Cube(-1*cubePositioning, 0, 0,		cubeSizing, 0, cubeSizing);
	cube3 = Cube(cubePositioning, 0, 0,			cubeSizing, 0, cubeSizing);
	cube4 = Cube(0, cubePositioning, 0,			0.5, cubeSizing, cubeSizing);
	cube5 = Cube(0, 0, cubePositioning,			cubeSizing, cubeSizing, 0); 
	cube6 = Cube(0, 0, -1*cubePositioning,		cubeSizing, cubeSizing, 0); 
		*/


	cube1 = Cube(-cP, -cP, -cP,					2, cubeSizing, cubeSizing);		// bottom
	cube2 = Cube(-cP, -cP, -cP,						cubeSizing, 0, cubeSizing);
	cube3 = Cube(cP, -cP, -cP,						cubeSizing, 0, cubeSizing);
	cube4 = Cube(-cP, cP, -cP,						2, cubeSizing, cubeSizing);	// top
	cube5 = Cube(-cP, -cP, cP,						cubeSizing, cubeSizing, 0);
	cube6 = Cube(-cP, -cP, -cP,						cubeSizing, cubeSizing, 0);

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
	
	cube1.drawModel();
	 
	cube2.drawModel();
	 
	cube3.drawModel();
	
	cube4.drawModel();
	
	cube5.drawModel();
	
	cube6.drawModel();

	boxTexture->Unbind();
}