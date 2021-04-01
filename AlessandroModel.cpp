#include "AlessandroModel.h"

AlessandroModel::AlessandroModel() {
	
	GLfloat xOrigin = 0.0f;
	GLfloat yOrigin = 0.0f;
	GLfloat zOrigin = 0.0f;

	lineSize = 0.4f * 2;

	distance = 2.0f;

	setLetterA(xOrigin - (3 * distance), yOrigin, zOrigin, 0.f, 0.f);
	setLetterO(xOrigin - (1 * distance), yOrigin, zOrigin, 0.f, 0.f);
	setNumber1(xOrigin + (1 * distance), yOrigin, zOrigin, 0.f, 0.f);
	setNumber4(xOrigin + (3 * distance), yOrigin, zOrigin, 0.f, 0.f);
	
	mode = GL_TRIANGLES;
}

void AlessandroModel::drawModel(int drawMode, Texture * boxTexture, Texture * metalTexture, float shearX, float shearY, bool shearTransformation)
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

	//A Model
	if (shearTransformation) {
		setLetterA(0 - (3 * distance), 0, 0, shearX, shearY);
	}
	glBindVertexArray(this->vao_A);
	glDrawElements(mode, 144, GL_UNSIGNED_INT, NULL);

	//O Model
	if (shearTransformation) {
		setLetterO(0 - (1 * distance), 0, 0, shearX, shearY);
	}
	glBindVertexArray(this->vao_O);
	glDrawElements(mode, 96, GL_UNSIGNED_INT, NULL);

	boxTexture->Unbind();
	metalTexture->Bind();

	//1 Model
	if (shearTransformation) {
		setNumber1(0 + (1 * distance), 0, 0, shearX, shearY);
	}
	glBindVertexArray(this->vao_1);
	glDrawElements(mode, 60, GL_UNSIGNED_INT, NULL);

	//4 Model
	if (shearTransformation) {
		setNumber4(0 + (3 * distance), 0, 0, shearX, shearY);
	}
	glBindVertexArray(this->vao_4);
	glDrawElements(mode, 96, GL_UNSIGNED_INT, NULL);

	metalTexture->Unbind();
}

void AlessandroModel::setLetterA(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin, float shearX, float shearY)
{
	GLfloat vertices[] =
	{
		// FRONT POSITION
		0.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, //bottom right (left)
		1.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, //bottom right (right)
		1.5 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY + shearY, zOrigin, //top right 
		-1.5 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY + shearY, zOrigin, //top left
		-1.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, //bottom left (left)
		-0.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, //bottom left (right)
		0.5 * lineSize + xOrigin, yOrigin, zOrigin, //hole [bottom right]
		0.5 * lineSize + xOrigin + shearX, 1 * lineSize + yOrigin + shearY, zOrigin, //hole [top right]
		-0.5 * lineSize + xOrigin, yOrigin, zOrigin, //hole [bottom left]
		-0.5 * lineSize + xOrigin + shearX, 1 * lineSize + yOrigin + shearY, zOrigin, //hole [top left]
		-0.5 * lineSize + xOrigin, -1 * lineSize + yOrigin, zOrigin, //U LEFT
		0.5 * lineSize + xOrigin, -1 * lineSize + yOrigin, zOrigin, //U RIGHT
		//BACK POSITION
		0.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize, //bottom right (left)
		1.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize, //bottom right (right)
		1.5 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY, zOrigin - lineSize, //top right 
		-1.5 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY, zOrigin - lineSize, //top left
		-1.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize, //bottom left (left)
		-0.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize, //bottom left (right)
		0.5 * lineSize + xOrigin, yOrigin, zOrigin - lineSize, //hole [bottom right]
		0.5 * lineSize + xOrigin, 1 * lineSize + yOrigin + shearY, zOrigin - lineSize, //hole [top right]
		-0.5 * lineSize + xOrigin, yOrigin, zOrigin - lineSize, //hole [bottom left]
		-0.5 * lineSize + xOrigin, 1 * lineSize + yOrigin + shearY, zOrigin - lineSize, //hole [top left]
		-0.5 * lineSize + xOrigin, -1 * lineSize + yOrigin, zOrigin - lineSize, //U LEFT
		0.5 * lineSize + xOrigin, -1 * lineSize + yOrigin, zOrigin - lineSize, //U RIGHT
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

void AlessandroModel::setNumber4(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin, float shearX, float shearY)
{
	GLfloat vertices[] =
	{
		// FRONT POSITIONS
		0.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, // bottom left
		1.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, //bottom right
		1.5 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY, zOrigin, //top right
		0.5 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY, zOrigin, //top right (left)
		0.5 * lineSize + xOrigin + shearX, 1 * lineSize + yOrigin + shearY, zOrigin, //top right (left) [bottom]
		-0.5 * lineSize + xOrigin + shearX, 1 * lineSize + yOrigin + shearY, zOrigin, //top left (right) [bottom]
		-0.5 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY, zOrigin, //top left (right)
		-1.5 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY, zOrigin, //top left
		-1.5 * lineSize + xOrigin + shearX, yOrigin + shearY, zOrigin, //top left (bottom)
		0.5 * lineSize + xOrigin, yOrigin, zOrigin, //middle under
		// BACK POSITIONS
		0.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize, // bottom left
		1.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize, //bottom right
		1.5 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY, zOrigin - lineSize, //top right
		0.5 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY, zOrigin - lineSize, //top right (left)
		0.5 * lineSize + xOrigin + shearX, 1 * lineSize + yOrigin + shearY, zOrigin - lineSize, //top right (left) [bottom]
		-0.5 * lineSize + xOrigin + shearX, 1 * lineSize + yOrigin + shearY, zOrigin - lineSize, //top left (right) [bottom]
		-0.5 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY, zOrigin - lineSize, //top left (right)
		-1.5 * lineSize + xOrigin + shearX, 2 * lineSize + yOrigin + shearY, zOrigin - lineSize, //top left
		-1.5 * lineSize + xOrigin + shearX, yOrigin + shearY, zOrigin - lineSize + shearY, //top left (bottom)
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

void AlessandroModel::setNumber1(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin, float shearX, float shearY)
{
	GLfloat vertices[] =
	{
		//FRONT POSITION
		-0.5 * lineSize + xOrigin,	-2 * lineSize + yOrigin,	zOrigin, //bottom left
		0.5 * lineSize + xOrigin,	-2 * lineSize + yOrigin,	zOrigin, //bottom right
		0.5 * lineSize + xOrigin + shearX,	2 * lineSize + yOrigin + shearY,		zOrigin, //top right
		-1.5 * lineSize + xOrigin + shearX,	2 * lineSize + yOrigin + shearY,		zOrigin, // top left
		-1.5 * lineSize + xOrigin,	lineSize + yOrigin,			zOrigin, //under left
		-0.5 * lineSize + xOrigin,	1 * lineSize + yOrigin,		zOrigin, //middle tucked
		//BACK POSITION
		-0.5 * lineSize + xOrigin,	-2 * lineSize + yOrigin,	zOrigin - lineSize, //bottom left
		0.5 * lineSize + xOrigin,	-2 * lineSize + yOrigin,	zOrigin - lineSize, //bottom right
		0.5 * lineSize + xOrigin + shearX,	2 * lineSize + yOrigin + shearY,		zOrigin - lineSize, //top right
		-1.5 * lineSize + xOrigin + shearX,	2 * lineSize + yOrigin + shearY,		zOrigin - lineSize, // top left
		-1.5 * lineSize + xOrigin,	lineSize + yOrigin,			zOrigin - lineSize, //under left
		-0.5 * lineSize + xOrigin,	1 * lineSize + yOrigin,		zOrigin - lineSize, //middle tucked
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

	glGenVertexArrays(1, &this->vao_1);
	glBindVertexArray(this->vao_1);

	GLuint vertices_VBO;
	glGenBuffers(1, &vertices_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(float), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(1);

	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 60 * sizeof(int), indicies, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void AlessandroModel::setLetterO(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin, float shearX, float shearY)
{
	// position 3, textureCoords 2
	GLfloat vertices_lines[] =
	{
		// FRONT POSITION	
		-2 * lineSize + xOrigin,	 -2 * lineSize + yOrigin,	zOrigin,  //outer bottom left 
		2 * lineSize + xOrigin,		-2 * lineSize + yOrigin,	zOrigin, //outer bottom right
		2 * lineSize + xOrigin + shearX,		2 * lineSize + yOrigin + shearY,		zOrigin,  //outer top right
		-2 * lineSize + xOrigin + shearX,	2 * lineSize + yOrigin + shearY,		zOrigin, //outer top left
		-1 * lineSize + xOrigin,	-1 * lineSize + yOrigin,	zOrigin, //inner bottom left 
		1 * lineSize + xOrigin,		-1 * lineSize + yOrigin,	zOrigin, //inner bottom right
		1 * lineSize + xOrigin + shearX,		1 * lineSize + yOrigin + shearY,		zOrigin, //inner top right
		-1 * lineSize + xOrigin + shearX,	1 * lineSize + yOrigin + shearY,		zOrigin, //inner top left
		// BACK POSITION
		-2 * lineSize + xOrigin,	-2 * lineSize + yOrigin,	zOrigin - lineSize,  //outer bottom left 
		2 * lineSize + xOrigin,		-2 * lineSize + yOrigin,	zOrigin - lineSize,  //outer bottom right
		2 * lineSize + xOrigin + shearX,		2 * lineSize + yOrigin + shearY,		zOrigin - lineSize, //outer top right
		-2 * lineSize + xOrigin + shearX,	2 * lineSize + yOrigin + shearY,		zOrigin - lineSize, //outer top left
		-1 * lineSize + xOrigin,	-1 * lineSize + yOrigin,	zOrigin - lineSize,  //inner bottom left 
		1 * lineSize + xOrigin,		-1 * lineSize + yOrigin,	zOrigin - lineSize,  //inner bottom right
		1 * lineSize + xOrigin + shearX,		1 * lineSize + yOrigin + shearY,		zOrigin - lineSize, //inner top right
		-1 * lineSize + xOrigin + shearX,	1 * lineSize + yOrigin + shearY,		zOrigin - lineSize, //inner top left
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

	glGenVertexArrays(1, &this->vao_O);
	glBindVertexArray(this->vao_O);

	GLuint vertices_VBO;
	glGenBuffers(1, &vertices_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);
	glBufferData(GL_ARRAY_BUFFER, 48 * sizeof(float), vertices_lines, GL_STATIC_DRAW);

	// position
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