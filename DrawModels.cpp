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
	
	
	
}



void DrawModel::setLetterK()
{
	DrawCube(0, 5, 0, 1);
	glBindVertexArray(this->vao_Cube);
	glDrawArrays(GL_QUADS, 0, 24);

	
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

void DrawModel::DrawCube(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat edgeLength)
{
	GLfloat halfSide = edgeLength * 0.5f;

	GLfloat vertices[] =
	{
		// front face
		centerX - halfSide, centerY + halfSide, centerZ + halfSide, // top left
		centerX + halfSide, centerY + halfSide, centerZ + halfSide, // top right
		centerX + halfSide, centerY - halfSide, centerZ + halfSide, // bottom right
		centerX - halfSide, centerY - halfSide, centerZ + halfSide, // bottom left

		// back face
		centerX - halfSide, centerY + halfSide, centerZ - halfSide, // top left
		centerX + halfSide, centerY + halfSide, centerZ - halfSide, // top right
		centerX + halfSide, centerY - halfSide, centerZ - halfSide, // bottom right
		centerX - halfSide, centerY - halfSide, centerZ - halfSide, // bottom left

		// left face
		centerX - halfSide, centerY + halfSide, centerZ + halfSide, // top left
		centerX - halfSide, centerY + halfSide, centerZ - halfSide, // top right
		centerX - halfSide, centerY - halfSide, centerZ - halfSide, // bottom right
		centerX - halfSide, centerY - halfSide, centerZ + halfSide, // bottom left

		// right face
		centerX + halfSide, centerY + halfSide, centerZ + halfSide, // top left
		centerX + halfSide, centerY + halfSide, centerZ - halfSide, // top right
		centerX + halfSide, centerY - halfSide, centerZ - halfSide, // bottom right
		centerX + halfSide, centerY - halfSide, centerZ + halfSide, // bottom left

		// top face
		centerX - halfSide, centerY + halfSide, centerZ + halfSide, // top left
		centerX - halfSide, centerY + halfSide, centerZ - halfSide, // top right
		centerX + halfSide, centerY + halfSide, centerZ - halfSide, // bottom right
		centerX + halfSide, centerY + halfSide, centerZ + halfSide, // bottom left

		// top face
		centerX - halfSide, centerY - halfSide, centerZ + halfSide, // top left
		centerX - halfSide, centerY - halfSide, centerZ - halfSide, // top right
		centerX + halfSide, centerY - halfSide, centerZ - halfSide, // bottom right
		centerX + halfSide, centerY - halfSide, centerZ + halfSide  // bottom left
	};

	glGenVertexArrays(1, &this->vao_Cube);
	glBindVertexArray(this->vao_Cube);

	GLuint vertices_VBO;
	glGenBuffers(1, &vertices_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(vertices) / sizeof(vertices[0])) * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);


	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}