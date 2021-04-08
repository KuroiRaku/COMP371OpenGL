#include "Cube.h"

Cube::Cube(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat tallNess, GLfloat width, GLfloat length) {
	SetCube(centerX, centerY, centerZ, 1, tallNess, width, length);
}
void Cube::SetCube(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat edgeLength, GLfloat tallNess, GLfloat width, GLfloat length)
{
	GLfloat halfSide = edgeLength * 0.5f;

	const int NUMBER_OF_VERTICIES = 72;
	const int ORIGINAL_STRIDE = 3; // initially each row has 3 positions
	GLfloat vertices[NUMBER_OF_VERTICIES] =
	{
		// front face
		centerX - halfSide,				centerY + halfSide + tallNess,		centerZ + halfSide + length, // top left 0
		centerX + halfSide + width ,	centerY + halfSide + tallNess,		centerZ + halfSide + length, // top right  1
		centerX + halfSide + width ,	centerY - halfSide,					centerZ + halfSide + length, // bottom right 2
		centerX - halfSide,				centerY - halfSide,					centerZ + halfSide + length, // bottom left 3

		// back face
		centerX - halfSide,				centerY + halfSide + tallNess,		centerZ - halfSide, // top left 4 
		centerX + halfSide + width ,	centerY + halfSide + tallNess,		centerZ - halfSide,  // top right 5
		centerX + halfSide + width ,	centerY - halfSide,					centerZ - halfSide , // bottom right 6 
		centerX - halfSide,				centerY - halfSide,					centerZ - halfSide ,// bottom left 7

		// left face
		centerX - halfSide, centerY + halfSide + tallNess, centerZ + halfSide + length , // top left 8
		centerX - halfSide, centerY + halfSide + tallNess, centerZ - halfSide,// top right 9
		centerX - halfSide, centerY - halfSide, centerZ - halfSide, // bottom right 10
		centerX - halfSide, centerY - halfSide, centerZ + halfSide + length,// bottom left 11

		// right face
		centerX + halfSide + width, centerY + halfSide + tallNess, centerZ + halfSide + length, // top left 12
		centerX + halfSide + width, centerY + halfSide + tallNess, centerZ - halfSide , // top right 13
		centerX + halfSide + width, centerY - halfSide, centerZ - halfSide , // bottom right 14
		centerX + halfSide + width, centerY - halfSide, centerZ + halfSide + length,// bottom left 15

		// top face
		centerX - halfSide, centerY + halfSide + tallNess, centerZ + halfSide + length,// top left 16
		centerX - halfSide, centerY + halfSide + tallNess, centerZ - halfSide, // top right 17
		centerX + halfSide + width, centerY + halfSide + tallNess, centerZ - halfSide , // bottom right 18
		centerX + halfSide + width, centerY + halfSide + tallNess, centerZ + halfSide + length, // bottom left 19

		// bot face
		centerX - halfSide, centerY - halfSide, centerZ + halfSide + length,// top left 20
		centerX - halfSide, centerY - halfSide, centerZ - halfSide , // top right 21
		centerX + halfSide + width, centerY - halfSide, centerZ - halfSide, // bottom right 22
		centerX + halfSide + width, centerY - halfSide, centerZ + halfSide + length, // bottom left 23
	};

	const int NUMBER_OF_INDICIES = 36;

	int indicies[36] =
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

	// initializes size of norms aray
	glm::vec3 norms[NUMBER_OF_VERTICIES / ORIGINAL_STRIDE];

	// calculates norms for a model based of their existing vertexes and indicies and puts it in a separate norms array
	for (int i = 0; i < NUMBER_OF_INDICIES; i += ORIGINAL_STRIDE) {
		int p1 = indicies[i];
		int p2 = indicies[i+1];
		int p3 = indicies[i+2];

		glm::vec3 point1 = glm::vec3(vertices[p1 * ORIGINAL_STRIDE], vertices[(p1 * ORIGINAL_STRIDE) + 1], vertices[(p1 * ORIGINAL_STRIDE) + 2]);
		glm::vec3 point2 = glm::vec3(vertices[p2 * ORIGINAL_STRIDE], vertices[(p2 * ORIGINAL_STRIDE) + 1], vertices[(p2 * ORIGINAL_STRIDE) + 2]);
		glm::vec3 point3 = glm::vec3(vertices[p3 * ORIGINAL_STRIDE], vertices[(p3 * ORIGINAL_STRIDE) + 1], vertices[(p3 * ORIGINAL_STRIDE) + 2]);

		glm::vec3 vector_u = point2 - point1;
		glm::vec3 vector_v = point3 - point1;

		glm::vec3 normal = glm::vec3(
			(vector_u.y * vector_v.z) - (vector_u.z * vector_v.y),
			(vector_u.z * vector_v.x) - (vector_u.x * vector_v.z),
			(vector_u.x * vector_v.y) - (vector_u.y * vector_v.x)
		);

		norms[p1] = normal;
		norms[p2] = normal;
		norms[p3] = normal;
	}

	// This is the new array we use that includes the norms
	const int SIZE_OF_NEW_ARRAY = 144;
	GLfloat vertices_norms[SIZE_OF_NEW_ARRAY];

	// this for loop takes the values of our initial verticies and puts them together in a new array with our norms
	for (int i = 0; i < 72; i += ORIGINAL_STRIDE) {
		int norms_row = i / ORIGINAL_STRIDE;
		vertices_norms[i*2] = vertices[i];
		vertices_norms[(i*2)+1] = vertices[i+1];
		vertices_norms[(i*2)+2] = vertices[i+2];
		vertices_norms[(i * 2) + 3] = norms[norms_row].x;
		vertices_norms[(i * 2) + 4] = norms[norms_row].y;
		vertices_norms[(i * 2) + 5] = norms[norms_row].z;
	}

	/*
	* The idea
	* Set Vector U to (Triangle.p2 minus Triangle.p1)
	Set Vector V to (Triangle.p3 minus Triangle.p1)

	Set Normal.x to (multiply U.y by V.z) minus (multiply U.z by V.y)
	Set Normal.y to (multiply U.z by V.x) minus (multiply U.x by V.z)
	Set Normal.z to (multiply U.x by V.y) minus (multiply U.y by V.x)

	Returning Normal
	*/

	glGenVertexArrays(1, &this->vao_Cube);
	glBindVertexArray(this->vao_Cube);

	GLuint vertices_VBO;
	glGenBuffers(1, &vertices_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(vertices_norms) / sizeof(vertices_norms[0])) * sizeof(GLfloat), vertices_norms, GL_STATIC_DRAW);

	// position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);

	//normals attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

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
