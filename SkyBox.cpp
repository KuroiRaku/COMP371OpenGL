#include "SkyBox.h"

SkyBox::SkyBox() {
	GLfloat xOrigin = 0.0f;
	GLfloat yOrigin = 0.0f;
	GLfloat zOrigin = 0.0f;

	lineSize = 0.4f * 2;

	distance = 2.5f;

	GLfloat cubeSizing = (lineSize * 75*2); // div by 2 because each side
	GLfloat cP = cubeSizing / 2.0f;

	cube1 = Cube(-cP, -cP, -cP,					2, cubeSizing, cubeSizing);		// bottom
	cube2 = Cube(-cP, -cP, -cP,						cubeSizing, 0, cubeSizing);
	cube3 = Cube(cP, -cP, -cP,						cubeSizing, 0, cubeSizing);
	cube4 = Cube(-cP, cP, -cP,						2, cubeSizing, cubeSizing);	// top
	cube5 = Cube(-cP, -cP, cP,						cubeSizing, cubeSizing, 0);
	cube6 = Cube(-cP, -cP, -cP,						cubeSizing, cubeSizing, 0);

	mode = GL_TRIANGLES;
}

void SkyBox::drawModel(Texture* boxTexture, Texture* metalTexture, Shader* shader, glm::mat4 objectMatrix)
{

	boxTexture->Bind();
	
	cube1.drawModel();
	 
	cube2.drawModel();
	 
	cube3.drawModel();
	
	cube4.drawModel();
	
	cube5.drawModel();
	
	cube6.drawModel();

	boxTexture->Unbind();
}