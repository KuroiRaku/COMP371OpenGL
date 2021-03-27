#include "Laginho.h"


LaginhoModel::LaginhoModel() {
	GLfloat xOrigin = 0.0f;
	GLfloat yOrigin = 0.0f;
	GLfloat zOrigin = 0.0f;

	lineSize = 0.4f * 2;

	distance = 2.0f;

	setLetterA(xOrigin - (3 * distance), yOrigin, zOrigin, 0, 0);
	setLetterH(xOrigin - (1 * distance), yOrigin, zOrigin,0,0);
    setNumber4(xOrigin + (1 * distance), yOrigin, zOrigin,0 ,0);
	setNumber0(xOrigin + (3 * distance), yOrigin, zOrigin,0,0);
	mode = GL_TRIANGLES;
}

void LaginhoModel::drawModel(int drawMode, Texture* boxTexture, Texture* metalTexture, float shearX, float shearY)
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

	//H Model
	setLetterH(0 - (3 * distance), 0, 0, shearX, shearY);
	glBindVertexArray(this->vao_H);
	glDrawElements(mode, 200, GL_UNSIGNED_INT, NULL);

	//A Model
	setLetterA(0 - (1 * distance), 0, 0, shearX, shearY);
	glBindVertexArray(this->vao_A);
	glDrawElements(mode, 144, GL_UNSIGNED_INT, NULL);

	boxTexture->Unbind();
	metalTexture->Bind();

	//O Model
	setNumber0(0 + (1 * distance), 0, 0, shearX, shearY);
	glBindVertexArray(this->vao_0);
	glDrawElements(mode, 96, GL_UNSIGNED_INT, NULL);

	//4 Model
	setNumber4(0 + (3 * distance), 0, 0, shearX, shearY);
	glBindVertexArray(this->vao_4);
	glDrawElements(mode, 96, GL_UNSIGNED_INT, NULL);

	metalTexture->Unbind();
}

void LaginhoModel::setLetterA(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin, float shearX, float shearY)
{
	GLfloat vertices[] =
	{
		// FRONT POSITION
		0.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, // 0 bottom right (left)
		1.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, //1 bottom right (right)
		1.5 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY, zOrigin, //2 top right 
		-1.5 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY, zOrigin, //3top left
		-1.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, // 4 bottom left (left)
		-0.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, //5bottom left (right)
		0.5 * lineSize + xOrigin, yOrigin, zOrigin, //6hole [bottom right]
		0.5 * lineSize + xOrigin + shearX, 1 * lineSize + yOrigin + shearY, zOrigin, //7hole [top right]
		-0.5 * lineSize + xOrigin, yOrigin, zOrigin, //8hole [bottom left]
		-0.5 * lineSize + xOrigin + shearX, 1 * lineSize + yOrigin + shearY, zOrigin, //9hole [top left]
		-0.5 * lineSize + xOrigin, -1 * lineSize + yOrigin, zOrigin, //10U LEFT
		0.5 * lineSize + xOrigin, -1 * lineSize + yOrigin, zOrigin, //11U RIGHT
		//BACK POSITION
		0.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize, //12bottom right (left)
		1.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize, //13bottom right (right)
		1.5 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY, zOrigin - lineSize, //14top right 
		-1.5 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY, zOrigin - lineSize, //15top left
		-1.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize, //16bottom left (left)
		-0.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize, //17bottom left (right)
		0.5 * lineSize + xOrigin, yOrigin, zOrigin - lineSize, //18hole [bottom right]
		0.5 * lineSize + xOrigin + shearX, 1 * lineSize + yOrigin + shearY, zOrigin - lineSize, //19hole [top right]
		-0.5 * lineSize + xOrigin, yOrigin, zOrigin - lineSize, //20hole [bottom left]
		-0.5 * lineSize + xOrigin + shearX, 1 * lineSize + yOrigin + shearY, zOrigin - lineSize, //21hole [top left]
		-0.5 * lineSize + xOrigin, -1 * lineSize + yOrigin, zOrigin - lineSize, //22U LEFT
		0.5 * lineSize + xOrigin, -1 * lineSize + yOrigin, zOrigin - lineSize, //23U RIGHT
	};

	int indicies[] =
	{
		0,1,11,
		1,6,11,
		1,2,6,
		6,2,7,
		7,2,3,
		7,3,9,
		9,3,8,
		8,3,4,
		8,4,10,
		10,4,5,
		10,11,8, //middle
		11,6,8,

		// back indicies
		20, 18, 23,
		20, 23, 22,
		17, 16, 22,
		22, 16, 20,
		16, 15, 20,
		20, 15, 21,
		21, 15, 19,
		15, 14, 19,
		19, 14, 18,
		18, 14, 13,
		23, 18, 13,
		23, 13, 12,
		// Sides
		1,13,2,
		13,14,2,
		2,14,3,
		14,15,3,
		3,15,16,
		3,16,4,
		4,16,5,
		16,17,5,
		5,17,22,
		5,22,10,
		11,10,22,
		11,22,23,
		0,11,12,
		11,23,12,
		0,12,1,
		1,12,13,
		//middle sides
		8,6,18,
		18,20,8,
		6,7,18,
		18,7,19,
		7,9,21,
		7,21,19,
		8,20,21,
		8,21,9
	};// 48 () = 144

	glGenVertexArrays(1, &this->vao_A);
	glBindVertexArray(this->vao_A);

	GLuint vertices_VBO;
	glGenBuffers(1, &vertices_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);
	glBufferData(GL_ARRAY_BUFFER, 72 * sizeof(float), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(1);

	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 144 * sizeof(int), indicies, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void LaginhoModel::setNumber4(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin, float shearX, float shearY)
{
	GLfloat vertices[] =
	{
		// FRONT POSITIONS
		0.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, // bottom left
		1.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, //bottom right
		1.5 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY, zOrigin, //top right
		0.5 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY, zOrigin, //top right (left)
		0.5 * lineSize + xOrigin, 1 * lineSize + yOrigin, zOrigin, //top right (left) [bottom]
		-0.5 * lineSize + xOrigin, 1 * lineSize + yOrigin, zOrigin, //top left (right) [bottom]
		-0.5 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY, zOrigin, //top left (right)
		-1.5 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY, zOrigin, //top left
		-1.5 * lineSize + xOrigin, yOrigin, zOrigin, //top left (bottom)
		0.5 * lineSize + xOrigin, yOrigin, zOrigin, //middle under
		// BACK POSITIONS
		0.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize, // bottom left
		1.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize, //bottom right
		1.5 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY, zOrigin - lineSize, //top right
		0.5 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY, zOrigin - lineSize, //top right (left)
		0.5 * lineSize + xOrigin, 1 * lineSize + yOrigin, zOrigin - lineSize, //top right (left) [bottom]
		-0.5 * lineSize + xOrigin, 1 * lineSize + yOrigin, zOrigin - lineSize, //top left (right) [bottom]
		-0.5 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY, zOrigin - lineSize, //top left (right)
		-1.5 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY, zOrigin - lineSize, //top left
		-1.5 * lineSize + xOrigin, yOrigin, zOrigin - lineSize, //top left (bottom)
		0.5 * lineSize + xOrigin, yOrigin, zOrigin - lineSize, //middle under
	};

	int indicies[] =
	{
		// FRONT INDICIES
		0,1,2,
		2,3,0,
		9,4,5,
		9,5,8,
		8,5,7,
		5,6,7,
		// BACK INDICIES
		17,16,15,
		17,15,18,
		18,15,19,
		15,14,19,
		10,13,12,
		12,11,10,
		// SIDE INDICIES
		1,11,12, //right long
		12,2,1,
		2,12,13, //right top
		2,13,3,
		1,0,10, //bottom lowest
		1,10,11,
		4,3,14, //top U
		3,13,14,
		4,15,5,
		4,14,15,
		5,15,6,
		15,16,6,
		7,6,16, // top left
		16,17,7,
		8,7,18, //left long
		7,17,18,
		9,8,18,//bottom U
		9,18,19,
		0,9,10, //bottom left
		9,19,10
	};

	glGenVertexArrays(1, &this->vao_4);
	glBindVertexArray(this->vao_4);

	GLuint vertices_VBO;
	glGenBuffers(1, &vertices_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);
	glBufferData(GL_ARRAY_BUFFER, 60 * sizeof(float), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(1);

	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 96 * sizeof(int), indicies, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void LaginhoModel::setLetterH(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin, float shearX, float shearY)
{
	GLfloat vertices[] =
	{
		//FRONT POSITION
		-2 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, //0
		-1.0 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin,//1
		-1.0 * lineSize + xOrigin + shearX, 2 * lineSize + shearY + yOrigin, zOrigin, //2
		-2.0 * lineSize + xOrigin + shearX, 2 * lineSize + shearY + yOrigin, zOrigin, //3
		
		//BACK POSITION
		-2 * lineSize + xOrigin, -2 * lineSize + yOrigin,  zOrigin - lineSize,//4
		-1.0 * lineSize + xOrigin, -2 * lineSize + yOrigin,  zOrigin - lineSize,//5
		-1.0 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY,  zOrigin - lineSize,//6
		-2.0 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY,  zOrigin - lineSize,//7

		//Middle
		0.0 * lineSize + xOrigin + shearX, yOrigin + shearY, zOrigin, //8 hole [bottom right]
		0.0 * lineSize + xOrigin, -1 * lineSize + yOrigin, zOrigin, //9 hole [top right]
		-1.0 * lineSize + xOrigin + shearX, yOrigin + shearY, zOrigin, //10 hole [bottom left]
		-1.0 * lineSize + xOrigin, -1 * lineSize + yOrigin, zOrigin, //11 hole [top left]
		//Back
		0.0 * lineSize + xOrigin + shearX, yOrigin + shearY, zOrigin - lineSize,//12
		0.0 * lineSize + xOrigin, -1 * lineSize + yOrigin, zOrigin - lineSize,//13
		-1.0 * lineSize + xOrigin + shearX, yOrigin + shearY, zOrigin - lineSize,//14
		-1.0 * lineSize + xOrigin, -1 * lineSize + yOrigin, zOrigin - lineSize,//15

		//Right Leg 
		0 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin,//16
		1.0 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin,//17
		1.0 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY, zOrigin,//18
		0.0 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY, zOrigin,//19

		//BACK POSITION
		0 * lineSize + xOrigin, -2 * lineSize + yOrigin,  zOrigin - lineSize,//20
		1.0 * lineSize + xOrigin, -2 * lineSize + yOrigin,  zOrigin - lineSize,//21
		1.0 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY,  zOrigin - lineSize,//22
		0.0 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY,  zOrigin - lineSize,//23

	};

	int indicies[] =
	{
		// FRONT INDICIES
		0,1,2,
		2,3,0,

		//Left Top 
		2,7,3,
		6,7,2,
		// BACK INDICIES
		4,6,5,
		4,7,6,

		//Left Side
		0,3,7,
		7,4,0,

		//Right Side 
		1,6,2,
		6,1,5,

		//Bottom
		0,4,1,
		4,5,1,

		//Middle 
		9,8,10,
		10,11,9,

		12,15,14,
		15,12,13,

		//Top
		8,14,10,
		14,8,12,

		//Bottom 
		15,9,11,
		13,9,15,


		//Right Side 
		16,17,18,
		18,19,16,

		22,20,23,
		20,22,21,

		//Left
		23,16,19,
		16,23,20,

		//
		17,22,18,
		17,21,22,

		//TOP 
		18,23,19,
		23,18,22,
		//Bottom 
		16,21,17,
		21,16,20
	};

	glGenVertexArrays(1, &this->vao_H);
	glBindVertexArray(this->vao_H);

	GLuint vertices_VBO;
	glGenBuffers(1, &vertices_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);
	glBufferData(GL_ARRAY_BUFFER, 100 * sizeof(float), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(1);

	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 200 * sizeof(int), indicies, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void LaginhoModel::setNumber0(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin, float shearX, float shearY)
{
	GLfloat vertices_lines[] =
	{
		// FRONT POSITION	
		-2 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, //outer bottom left 
		1.0 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, //outer bottom right
		1.0 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin +shearY, zOrigin, //outer top right
		-2 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY, zOrigin, //outer top left
		-1 * lineSize + xOrigin, -1 * lineSize + yOrigin, zOrigin, //inner bottom left 
		0.0 * lineSize + xOrigin, -1 * lineSize + yOrigin, zOrigin, //inner bottom right
		0.0 * lineSize + xOrigin + shearX, 1 * lineSize + yOrigin + shearY, zOrigin, //inner top right
		-1 * lineSize + xOrigin + shearX, 1 * lineSize + yOrigin + shearY, zOrigin, //inner top left
		// BACK POSITION
		-2 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize, //outer bottom left 
		1.0 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize, //outer bottom right
		1.0 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY, zOrigin - lineSize, //outer top right
		-2 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY, zOrigin - lineSize, //outer top left
		-1 * lineSize + xOrigin, -1 * lineSize + yOrigin, zOrigin - lineSize, //inner bottom left 
		0.0 * lineSize + xOrigin, -1 * lineSize + yOrigin, zOrigin - lineSize, //inner bottom right
		0.0 * lineSize + xOrigin + shearX, 1 * lineSize + yOrigin + shearY, zOrigin - lineSize, //inner top right
		-1 * lineSize + xOrigin + shearX, 1 * lineSize + yOrigin + shearY, zOrigin - lineSize, //inner top left
	};

	int indicies_lines[] =
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

	glGenVertexArrays(1, &this->vao_0);
	glBindVertexArray(this->vao_0);

	GLuint vertices_VBO;
	glGenBuffers(1, &vertices_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);
	glBufferData(GL_ARRAY_BUFFER, 48 * sizeof(float), vertices_lines, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(1);

	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 96 * sizeof(int), indicies_lines, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}