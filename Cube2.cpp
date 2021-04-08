#include "Cube2.h"

#include "Cube.h"

Cube2::Cube2(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat tallNess, GLfloat width, GLfloat length) {
	SetCube(centerX, centerY, centerZ, 1, tallNess, width, length);
}
void Cube2::SetCube(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat edgeLength, GLfloat tallNess, GLfloat width, GLfloat length)
{
	GLfloat halfSide = edgeLength * 0.5f;

	GLfloat vertices[] =
	{
		centerX + halfSide + width, centerY - halfSide, centerZ - halfSide,
		centerX + halfSide + width, centerY - halfSide, centerZ + halfSide + length,
		centerX - halfSide, centerY - halfSide, centerZ + halfSide + length,
		centerX - halfSide, centerY - halfSide, centerZ - halfSide,

		centerX + halfSide + width, centerY + halfSide + tallNess, centerZ - halfSide,
		centerX + halfSide + width, centerY + halfSide + tallNess, centerZ + halfSide + length,
		centerX - halfSide, centerY + halfSide + tallNess, centerZ + halfSide + length,
		centerX - halfSide, centerY + halfSide + tallNess, centerZ - halfSide,
	};

	int indicies[] =
	{
		// Front.
		0,1,2,
		0,2,3,

		// Side left.
		2,7,3,
		2,6,7,

		// Back.
		7,6,5,
		7,5,4,

		// Side Right.
		1,0,4,
		1,4,5,

		// Top.
		1,5,2,
		2,5,6,

		// Bottom.
		5,0,3,
		5,3,7
	};

	float normals[] =
	{
		0, 0, -1,
		-1,0,0,
		0,0,1,
		0,0,1,
		1,0,0,
		1,0,0,
		0,1,0,
		0,-1,0
	};

	glGenVertexArrays(1, &this->vao_Cube);
	glBindVertexArray(this->vao_Cube);

	GLuint vertices_VBO;
	glGenBuffers(1, &vertices_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(vertices) / sizeof(vertices[0])) * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	GLuint normals_VBO;
	glGenBuffers(1, &normals_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, normals_VBO);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(normals) / sizeof(normals[0])) * sizeof(float), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	indiciesC = (sizeof(indicies) / sizeof(indicies[0]));
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiciesC * sizeof(int), indicies, GL_STATIC_DRAW);


	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void Cube2::drawModel() {

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(this->vao_Cube);
	glDrawElements(GL_TRIANGLES, indiciesC, GL_UNSIGNED_INT, NULL);

}

