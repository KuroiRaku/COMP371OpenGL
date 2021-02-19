#include "DrawModel.h"

using namespace std;

/*
* //D Model
	glBindVertexArray(this->vao_D);
	glDrawElements(mode, indiciesD, GL_UNSIGNED_INT, NULL);

	//7 Model
	glBindVertexArray(this->vao_7);
	glDrawElements(mode, indicies7, GL_UNSIGNED_INT, NULL);

	//4 Model
	glBindVertexArray(this->vao_4);
	glDrawElements(mode, indicies4, GL_UNSIGNED_INT, NULL);

	//N Model
	glBindVertexArray(this->vao_N);
	glDrawElements(mode, indiciesN, GL_UNSIGNED_INT, NULL);
*/
DrawModel::DrawModel() {
	
	GLfloat xOrigin = 0.0f;
	GLfloat yOrigin = 0.0f;
	GLfloat zOrigin = 0.0f;

	lineSize = 0.4f * 2;

	GLfloat distance = 2.0f;

	setLetterK(xOrigin - (3 * distance), yOrigin, zOrigin);
	

	mode = GL_TRIANGLES;
	
}

void DrawModel::drawModel(int drawMode) {
	


	
}


void DrawModel::setLetterK(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin)
{
	

}

void DrawModel::setLetterA()
{
	
}

void DrawModel::setLetterO()
{
	
}

void DrawModel::setLetterU()
{
	
}
void DrawModel::setLetterS()
{

}

