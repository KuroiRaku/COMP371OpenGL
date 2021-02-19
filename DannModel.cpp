#include "DannModel.h"
using namespace std;


DannModel::DannModel() {
	GLfloat xOrigin = 0.0f;
	GLfloat yOrigin = 0.0f;
	GLfloat zOrigin = 0.0f;

	lineSize = 0.4f * 2;

	GLfloat distance = 2.5f;


	setLetterD(xOrigin - (3 * distance), yOrigin, zOrigin);
	setNumber7(xOrigin + (1 * distance), yOrigin, zOrigin);
	setLetterN(xOrigin - (1 * distance), yOrigin, zOrigin);
	setNumber4(xOrigin + (3 * distance), yOrigin, zOrigin);

	mode = GL_TRIANGLES;
}

void DannModel::drawModel(int drawMode)
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


	//D Model
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
}

void DannModel::setLetterN(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin)
{
	GLfloat vertices[] =
	{
		// FRONT POSITIONS
		0.5f * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, // bottom left 0
		1.5f * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, //bottom right 1
		1.5f * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin, //top right 2
		0.5f * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin, //top right (left) 3

		0.5f * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize, // bottom left 4
		1.5f * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize, //bottom right 5
		1.5f * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin - lineSize, //top right 6
		0.5f * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin - lineSize, //top right (left) 7
		//Right
		1.5f * lineSize + xOrigin, 0.5f * lineSize + yOrigin, zOrigin, //8
		1.5f * lineSize + xOrigin, 0.5f * lineSize + yOrigin, zOrigin - lineSize,//9

		1.5f * lineSize + xOrigin, 1.5f * lineSize + yOrigin, zOrigin,//10
		1.5f * lineSize + xOrigin, 1.5f * lineSize + yOrigin, zOrigin - lineSize,//11
		3.0f * lineSize + xOrigin, 0.5f * lineSize + yOrigin, zOrigin,//12
		3.0f * lineSize + xOrigin, 0.5f * lineSize + yOrigin, zOrigin - lineSize,//13
		3.0f * lineSize + xOrigin, 1.5f * lineSize + yOrigin, zOrigin,//14
		3.0f * lineSize + xOrigin, 1.5f * lineSize + yOrigin, zOrigin - lineSize,//15
		2.5f * lineSize + xOrigin, 0.5f * lineSize + yOrigin, zOrigin,//16
		2.5f * lineSize + xOrigin, 0.5f * lineSize + yOrigin, zOrigin - lineSize,//17
		2.5f * lineSize + xOrigin, -2.0f * lineSize + yOrigin, zOrigin, // bottom left 18
		2.5f * lineSize + xOrigin, -2.0f * lineSize + yOrigin, zOrigin - lineSize, // bottom left  19
		3.0f * lineSize + xOrigin, -2.0f * lineSize + yOrigin, zOrigin, // bottom left 20
		3.0f * lineSize + xOrigin, -2.0f * lineSize + yOrigin, zOrigin - lineSize, // bottom left  21


	};
	int indicies[] =
	{
		// FRONT INDICIES
		0,1,2,
		2,3,0,
		// BACK INDICIES
		5,4,7,
		7,6,5,

			//Left Side
		4,0,3,
		3,7,4,

		//Right Side
		1,5,6,
		6,2,1,

		//Bottom
		0,4,5,
		5,1,0,




		//Top
		2,6,7,
		7,3,2,
		//Side
		8,12,14,
		14,10,8,

		13,9,11,
		11,15,13,

		12,8,9,
		9,13,12,

		10,14,15,
		15,11,10,

		18,16,12,
		12,20,18,

		18,20,12,
		12,16,18,

		19,17,13,
		13,21,19,

		18,16,17,
		17,19,18,

		20,21,13,
		13,12,20,

		12,13,15,
		15,14,12,

		19,21,20,
		20,18,19,





	};
	glGenVertexArrays(1, &this->vao_N);
	glBindVertexArray(this->vao_N);
	GLuint vertices_VBO;
	glGenBuffers(1, &vertices_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(vertices) / sizeof(vertices[0])) * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	indiciesN = (sizeof(indicies) / sizeof(indicies[0]));
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiciesN * sizeof(int), indicies, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void DannModel::setNumber4(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin)
{
	GLfloat vertices[] =
	{
		// FRONT POSITIONS
		0.5f * lineSize + xOrigin, -2.5f * lineSize + yOrigin, zOrigin, //  0
		1.5f * lineSize + xOrigin, -2.5f * lineSize + yOrigin, zOrigin, // 1
		1.5f * lineSize + xOrigin, 2.5f * lineSize + yOrigin, zOrigin, // 2
		0.5f * lineSize + xOrigin, 2.5f * lineSize + yOrigin, zOrigin, // 3
		0.5f * lineSize + xOrigin, 1.5f * lineSize + yOrigin, zOrigin, // 4
		-0.5f * lineSize + xOrigin, 1.5f * lineSize + yOrigin, zOrigin, // 5
		-0.5f * lineSize + xOrigin, 2.5f * lineSize + yOrigin, zOrigin, // 6
		-1.5f * lineSize + xOrigin, 2.5f * lineSize + yOrigin, zOrigin, // 7
		-1.5f * lineSize + xOrigin, yOrigin, zOrigin, // 8
		0.5f * lineSize + xOrigin, yOrigin, zOrigin, // 9

		// BACK POSITIONS
		0.5f * lineSize + xOrigin, -2.5f * lineSize + yOrigin, zOrigin - lineSize, //  10
		1.5f * lineSize + xOrigin, -2.5f * lineSize + yOrigin, zOrigin - lineSize, // 11
		1.5f * lineSize + xOrigin, 2.5f * lineSize + yOrigin, zOrigin - lineSize, // 12
		0.5f * lineSize + xOrigin, 2.5f * lineSize + yOrigin, zOrigin - lineSize, //  13
		0.5f * lineSize + xOrigin, 1.5f * lineSize + yOrigin, zOrigin - lineSize, // 14
		-0.5f * lineSize + xOrigin, 1.5f * lineSize + yOrigin, zOrigin - lineSize, // 15
		-0.5f * lineSize + xOrigin, 2.5f * lineSize + yOrigin, zOrigin - lineSize, // 16
		-1.5f * lineSize + xOrigin, 2.5f * lineSize + yOrigin, zOrigin - lineSize, // 17
		-1.5f * lineSize + xOrigin, yOrigin, zOrigin - lineSize, // 18
		0.5f * lineSize + xOrigin, yOrigin, zOrigin - lineSize, // 19

		1.5f * lineSize + xOrigin, + yOrigin, zOrigin, // 20
		1.5f * lineSize + xOrigin, +yOrigin, zOrigin - lineSize, // 21
		2.5f * lineSize + xOrigin, +yOrigin, zOrigin, // 22
		2.5f * lineSize + xOrigin, +yOrigin, zOrigin - lineSize, // 23

		1.5f * lineSize + xOrigin, 0.5f * lineSize +yOrigin, zOrigin, // 24 unsused
		1.5f * lineSize + xOrigin, 0.5f * lineSize +yOrigin, zOrigin - lineSize, // 25 unsused
		2.5f * lineSize + xOrigin, 0.5f * lineSize +yOrigin, zOrigin, // 26 unused for now
		2.5f * lineSize + xOrigin, 0.5f * lineSize +yOrigin, zOrigin - lineSize, // 27 unused
	};

	int indicies[] =
	{

		0,1,2,
		2,3,0,
		9,4,5,
		9,5,8,
		8,5,7,
		5,6,7,
		17,16,15,
		17,15,18,
		18,15,19,
		15,14,19,
		10,13,12,
		12,11,10,
		1,11,12,
		12,2,1,
		2,12,13,
		2,13,3,
		1,0,10,
		1,10,11,
		4,3,14,
		3,13,14,
		4,15,5,
		4,14,15,
		5,15,6,
		15,16,6,
		7,6,16,
		16,17,7,
		8,7,18,
		7,17,18,
		9,8,18,
		9,18,19,
		0,9,10,
		9,19,10,


	};

	glGenVertexArrays(1, &this->vao_4);
	glBindVertexArray(this->vao_4);

	GLuint vertices_VBO;
	glGenBuffers(1, &vertices_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(vertices) / sizeof(vertices[0])) * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	indicies4 = (sizeof(indicies) / sizeof(indicies[0]));
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies4 * sizeof(int), indicies, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void DannModel::setNumber7(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin)
{
	GLfloat vertices[] =
	{
		//FRONT POSITION
		-0.5f * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, //bottom left
		0.5f * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, //bottom right
		0.5f * lineSize + xOrigin, 3 * lineSize + yOrigin, zOrigin, //top right
		-2.0f * lineSize + xOrigin, 3 * lineSize + yOrigin, zOrigin, // top left
		-2.0f * lineSize + xOrigin, 2*lineSize + yOrigin, zOrigin, //under left
		-0.5f * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin, //middle tucked
		//BACK POSITION
		-0.5f * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize, //bottom left
		0.5f * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize, //bottom right
		0.5f * lineSize + xOrigin, 3 * lineSize + yOrigin, zOrigin - lineSize, //top right
		-2.0f * lineSize + xOrigin, 3 * lineSize + yOrigin, zOrigin - lineSize, // top left
		-2.0f * lineSize + xOrigin, 2 *lineSize + yOrigin, zOrigin - lineSize, //under left
		-0.5f * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin - lineSize, //middle tucked
	};

	int indicies[] =
	{
		// FRONT INDICIES
		0,1,2,
		0,2,5,
		5,2,3,
		5,3,4,
		// BACK INDICIES
		6,8,7,
		6,11,8,
		11,9,8,
		11,10,9,
		// SIDES
		1,7,8, //right
		8,2,1,
		0,6,1, //bottom
		1,6,7,
		2,8,9, //top
		9,3,2,
		0,5,6, //left long
		11,6,5,
		5,4,10, //bottom tuck
		10,11,5,
		3,9,10, //left tuck
		4,3,10,
	};

	glGenVertexArrays(1, &this->vao_7);
	glBindVertexArray(this->vao_7);

	GLuint vertices_VBO;
	glGenBuffers(1, &vertices_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(vertices) / sizeof(vertices[0])) * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	indicies7 = (sizeof(indicies) / sizeof(indicies[0]));
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies7 * sizeof(int), indicies, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void DannModel::setLetterD(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin)
{
	GLfloat vertices[] =
	{
		// FRONT POSITION
		-2.0f * lineSize + xOrigin, -2.0f * lineSize + yOrigin, zOrigin, //outer bottom left
		2.0f * lineSize + xOrigin, -2.0f * lineSize + yOrigin, zOrigin, //outer bottom right
		2.0f * lineSize + xOrigin, 4.0f * lineSize + yOrigin, zOrigin, //outer top right
		-2.0f * lineSize + xOrigin, 4.0f * lineSize + yOrigin, zOrigin, //outer top left
		-1.5f * lineSize + xOrigin, -1.5f * lineSize + yOrigin, zOrigin, //inner bottom left
		1.0f * lineSize + xOrigin, -1.5f * lineSize + yOrigin, zOrigin, //inner bottom right
		1.0f * lineSize + xOrigin, 3.5f * lineSize + yOrigin, zOrigin, //inner top right
		-1.5f * lineSize + xOrigin, 3.5f * lineSize + yOrigin, zOrigin, //inner top left
		// BACK POSITION
		-2.0f * lineSize + xOrigin, -2.0f * lineSize + yOrigin, zOrigin - lineSize, //outer bottom left
		2.0f * lineSize + xOrigin, -2.0f * lineSize + yOrigin, zOrigin - lineSize, //outer bottom right
		2.0f * lineSize + xOrigin, 4.0f * lineSize + yOrigin, zOrigin - lineSize, //outer top right
		-2.0f * lineSize + xOrigin, 4.0f * lineSize + yOrigin, zOrigin - lineSize, //outer top left
		-1.5f * lineSize + xOrigin, -1.5f * lineSize + yOrigin, zOrigin - lineSize, //inner bottom left
		1.0f * lineSize + xOrigin, -1.5f * lineSize + yOrigin, zOrigin - lineSize, //inner bottom right
		1.0f * lineSize + xOrigin, 3.5f * lineSize + yOrigin, zOrigin - lineSize, //inner top right
		-1.5f * lineSize + xOrigin, 3.5f * lineSize + yOrigin, zOrigin - lineSize, //inner top left
	};

	int indicies[] =
	{
		// FRONT INDICIES
		0,1,4,
		4,1,5,
		1,2,5,
		2,6,5,
		2,7,6,
		2,3,7,
		3,0,7,
		7,0,4,
		// BACK INDICIES
		8,12,9,
		12,13,9,
		9,13,10,
		10,13,14,
		10,14,15,
		10,15,11,
		11,15,8,
		15,12,8,
		// OUTER SIDES
		0,3,11, //left
		11,8,0,
		3,2,10, //top
		3,10,11,
		0,8,1, //bottom
		1,8,9,
		1,10,2, //right
		1,9,10,
		// INNER SIDES
		4,15,7, //left
		15,4,12,
		7,14,6, //top
		7,15,14,
		4,5,12, //bottom
		5,13,12,
		5,6,14, //right
		5,14,13
	};

	glGenVertexArrays(1, &this->vao_D);
	glBindVertexArray(this->vao_D);

	GLuint vertices_VBO;
	glGenBuffers(1, &vertices_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(vertices) / sizeof(vertices[0])) * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	indiciesD= (sizeof(indicies) / sizeof(indicies[0]));
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,indiciesD * sizeof(int), indicies, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
