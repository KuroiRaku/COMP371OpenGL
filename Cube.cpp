// Sourced online

#include "Cube.h"

Cube::Cube(float x, float y, float z) {
	SetCube(x, y, z, 1);
}

// TODO: CHANGE THE EDGE LENGTH TO PROPER MEASUREMENTS
void Cube::SetCube(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat edgeLength)
{
	GLfloat gridUnitLength = 0.4f * 2;
	GLfloat halfSide = edgeLength * 0.5f;

	// width:	1		gridUnitLength
	// height:	0.5		gridUnitLength
	// depth:	0.25	gridUnitLenght

	// going to divide by 2 because we do +-
	GLfloat xLength = (1 * gridUnitLength) / 2;
	GLfloat yLength = (0.5 * gridUnitLength) / 2;
	GLfloat zLength = (0.25 * gridUnitLength) / 2;

	GLfloat vertices[] =
	{
		// front face
		centerX - xLength, centerY + yLength, centerZ + zLength, // top left 0
		centerX + xLength, centerY + yLength, centerZ + zLength, // top right  1
		centerX + xLength, centerY - yLength, centerZ + zLength, // bottom right 2
		centerX - xLength, centerY - yLength, centerZ + zLength, // bottom left 3

		// back face
		centerX - xLength, centerY + yLength, centerZ - zLength, // top left 4 
		centerX + xLength, centerY + yLength, centerZ - zLength, // top right 5
		centerX + xLength, centerY - yLength, centerZ - zLength, // bottom right 6 
		centerX - xLength, centerY - yLength, centerZ - zLength, // bottom left 7

		// left face
		centerX - xLength, centerY + yLength, centerZ + zLength, // top left 8
		centerX - xLength, centerY + yLength, centerZ - zLength, // top right 9
		centerX - xLength, centerY - yLength, centerZ - zLength, // bottom right 10
		centerX - xLength, centerY - yLength, centerZ + zLength, // bottom left 11

		// right face
		centerX + xLength, centerY + yLength, centerZ + zLength, // top left 12
		centerX + xLength, centerY + yLength, centerZ - zLength, // top right 13
		centerX + xLength, centerY - yLength, centerZ - zLength, // bottom right 14
		centerX + xLength, centerY - yLength, centerZ + zLength, // bottom left 15

		// top face
		centerX - xLength, centerY + yLength, centerZ + zLength, // top left 16
		centerX - xLength, centerY + yLength, centerZ - zLength, // top right 17
		centerX + xLength, centerY + yLength, centerZ - zLength, // bottom right 18
		centerX + xLength, centerY + yLength, centerZ + zLength, // bottom left 19

		// top face
		centerX - xLength, centerY - yLength, centerZ + zLength, // top left 20
		centerX - xLength, centerY - yLength, centerZ - zLength, // top right 21
		centerX + xLength, centerY - yLength, centerZ - zLength, // bottom right 22
		centerX + xLength, centerY - yLength, centerZ + zLength  // bottom left 23
	};

	int indicies[] =
	{
		3,2,1,
		1,0,3,

		6,7,4,
		4,5,6,

		8,9,10,
		10,11,8,

		13,12,15,
		15,14,13,

		19,18,17,
		17,16,19,

	22,23,20,
	20,21,22,

	};
	glGenVertexArrays(1, &this->vao_Cube);
	glBindVertexArray(this->vao_Cube);

	GLuint vertices_VBO;
	glGenBuffers(1, &vertices_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(vertices) / sizeof(vertices[0])) * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	indiciesC = (sizeof(indicies) / sizeof(indicies[0]));
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiciesC * sizeof(int), indicies, GL_STATIC_DRAW);


	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}
void Cube::drawModel() {

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(this->vao_Cube);
	glDrawElements(GL_TRIANGLES, indiciesC, GL_UNSIGNED_INT, NULL);

}
