#include "Cube.h"

Cube::Cube(float x, float y, float z, float length, float width, float depth) {
	SetCube(x, y, z, 1, length,width,depth);
}
void Cube::SetCube(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat edgeLength, float length, float width, float depth)
{
	GLfloat halfSide = edgeLength * 0.5f;

	GLfloat vertices[] =
	{
		// front face
		(centerX - halfSide) * width, (centerY + halfSide) *length, (centerZ + halfSide )*depth, // top left 0
		(centerX + halfSide)* width, (centerY + halfSide)* length, (centerZ + halfSide)* depth, // top right  1
		(centerX + halfSide)* width, (centerY - halfSide)* length, (centerZ + halfSide)* depth, // bottom right 2
		(centerX - halfSide)* width, (centerY - halfSide)* length, (centerZ + halfSide)* depth, // bottom left 3

		// back face
		(centerX - halfSide)* width, (centerY + halfSide)* length, (centerZ - halfSide)* depth, // top left 4 
		(centerX + halfSide)* width, (centerY + halfSide)* length, (centerZ - halfSide)* depth, // top right 5
		(centerX + halfSide)* width, (centerY - halfSide)* length, (centerZ - halfSide)* depth, // bottom right 6 
		(centerX - halfSide)* width, (centerY - halfSide)* length, (centerZ - halfSide)* depth, // bottom left 7

		// left face
		(centerX - halfSide)* width, (centerY + halfSide)* length, (centerZ + halfSide)* depth, // top left 8
		(centerX - halfSide)* width, (centerY + halfSide)* length, (centerZ - halfSide)* depth, // top right 9
		(centerX - halfSide)* width, (centerY - halfSide)* length, (centerZ - halfSide)* depth, // bottom right 10
		(centerX - halfSide)* width, (centerY - halfSide)* length, (centerZ + halfSide)* depth, // bottom left 11

		// right face
		(centerX + halfSide)* width, (centerY + halfSide)* length, (centerZ + halfSide)* depth, // top left 12
		(centerX + halfSide)* width, (centerY + halfSide)* length, (centerZ - halfSide)* depth, // top right 13
		(centerX + halfSide)* width, (centerY - halfSide)* length, (centerZ - halfSide)* depth, // bottom right 14
		(centerX + halfSide)* width, (centerY - halfSide)*length, (centerZ + halfSide)* depth, // bottom left 15

		// top face
		(centerX - halfSide)* width, (centerY + halfSide)* length, (centerZ + halfSide)* depth, // top left 16
		(centerX - halfSide)* width, (centerY + halfSide)* length, (centerZ - halfSide)* depth, // top right 17
		(centerX + halfSide)* width, (centerY + halfSide)* length, (centerZ - halfSide)* depth, // bottom right 18
		(centerX + halfSide)* width, (centerY + halfSide)* length, (centerZ + halfSide)* depth, // bottom left 19

		// top face
		(centerX - halfSide)* width, (centerY - halfSide)* length, (centerZ + halfSide)* depth, // top left 20
		(centerX - halfSide)* width, (centerY - halfSide)* length, (centerZ - halfSide)* depth, // top right 21
		(centerX + halfSide)* width, (centerY - halfSide)* length, (centerZ - halfSide)* depth, // bottom right 22
		(centerX + halfSide)* width, (centerY - halfSide)* length, (centerZ + halfSide)* depth  // bottom left 23
	};

	int indicies[] =
	{
		 3,2,1,
		1,0,3,

		4,6,7,
		4,5,6,

		8,9,10,
		10,11,8,

		13,12,15,
		15,14,13,

		19,18,17,
		17,16,19,

		22,23,20,
		22,20,21,
		
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
void Cube:: drawModel() {
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(this->vao_Cube);
	glDrawElements(GL_TRIANGLES, indiciesC, GL_UNSIGNED_INT, NULL);

}
