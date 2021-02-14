#include "LeCherngModel.h"

LeCherngModel::LeCherngModel() {
	GLfloat xOrigin = 0.0f;
	GLfloat yOrigin = 2.0f;
	GLfloat zOrigin = -10.0f;

	lineSize = 0.4f * 2;

	GLfloat distance = 2.0f;

	setLetterL(xOrigin - (3 * distance), yOrigin, (zOrigin * -2));
	setLetterG(xOrigin - (1 * distance), yOrigin, (zOrigin * -2));
	setNumber4(xOrigin + (1 * distance), yOrigin, (zOrigin *-2));
	setNumber4_2(xOrigin + (3 * distance), yOrigin, zOrigin *-2);

	mode = GL_TRIANGLES;
}

void LeCherngModel::drawModel(int drawMode)
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


	//G Model
	glBindVertexArray(this->vao_G);
	glDrawElements(mode, indiciesG, GL_UNSIGNED_INT, NULL);

	//4 Model
	glBindVertexArray(this->vao_4);
	glDrawElements(mode, 96, GL_UNSIGNED_INT, NULL);

	//the second 4 Model
	glBindVertexArray(this->vao_4_2);
	glDrawElements(mode, 96, GL_UNSIGNED_INT, NULL);

	//L Model
	glBindVertexArray(this->vao_L);
	glDrawElements(mode, indiciesL, GL_UNSIGNED_INT, NULL);
}

void LeCherngModel::setLetterL(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin)
{
	GLfloat vertices[] =
	{
		// FRONT POSITION
		-2 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin, //top left (left) 
		-1 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin, //top left (right)
		-1 * lineSize + xOrigin, -1 * lineSize + yOrigin, zOrigin, //bottom left (right top)
		-2 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, //bottom left (left corner)
		1.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, //bottom right (bottom)
		1.5 * lineSize + xOrigin, -1 * lineSize + yOrigin, zOrigin, //bottom right (above)

		//BACK POSITION
		-2 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin - lineSize, //top left (left) 
		-1 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin - lineSize, //top left (right)
		-1 * lineSize + xOrigin, -1 * lineSize + yOrigin, zOrigin - lineSize, //bottom left (right top)
		-2 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize, //bottom left (left corner)
		1.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize, //bottom right (bottom)
		1.5 * lineSize + xOrigin, -1 * lineSize + yOrigin, zOrigin - lineSize, //bottom right (above)
	}; //12 * 3 = 36

	int indicies[] =
	{
		//front
		0,1,2,
		0,2,3,
		2,3,5,
		2,4,5,
		// back indicies
		6, 7, 8,
		6, 8, 9,
		8, 9, 10,
		8, 10, 11,
		// Sides
		0,1,7, //top
		0,6,7,
		2,1,8, //top left (right)
		1,7,8,
		0,3,9, //top left +bottom left
		6,9,0,
		3,4,9, //bottom left + bottom right
		4,10,9,
		5,4,10, //bottom right bottom + bottom right above
		5,11,10,
		2,8,1, //bottom left (right) + top left (right)
		1,8,7
		
	};// 20 * 3 () =  60 

	glGenVertexArrays(1, &this->vao_L);
	glBindVertexArray(this->vao_L);

	GLuint vertices_VBO;
	glGenBuffers(1, &vertices_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(vertices) / sizeof(vertices[0])) * sizeof(float), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

	indiciesL = (sizeof(indicies) / sizeof(indicies[0]));
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiciesL * sizeof(int), indicies, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void LeCherngModel::setNumber4(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin)
{
	GLfloat vertices[] =
	{
		// FRONT POSITIONS
		0.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, // bottom left
		1.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, //bottom right
		1.5 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin, //top right
		0.5 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin, //top right (left)
		0.5 * lineSize + xOrigin, 1 * lineSize + yOrigin, zOrigin, //top right (left) [bottom]
		-0.5 * lineSize + xOrigin, 1 * lineSize + yOrigin, zOrigin, //top left (right) [bottom]
		-0.5 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin, //top left (right)
		-1.5 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin, //top left
		-1.5 * lineSize + xOrigin, yOrigin, zOrigin, //top left (bottom)
		0.5 * lineSize + xOrigin, yOrigin, zOrigin, //middle under
		// BACK POSITIONS
		0.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize, // bottom left
		1.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize, //bottom right
		1.5 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin - lineSize, //top right
		0.5 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin - lineSize, //top right (left)
		0.5 * lineSize + xOrigin, 1 * lineSize + yOrigin, zOrigin - lineSize, //top right (left) [bottom]
		-0.5 * lineSize + xOrigin, 1 * lineSize + yOrigin, zOrigin - lineSize, //top left (right) [bottom]
		-0.5 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin - lineSize, //top left (right)
		-1.5 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin - lineSize, //top left
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
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 96 * sizeof(int), indicies, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void LeCherngModel::setNumber4_2(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin)
{
	GLfloat vertices[] =
	{
		// FRONT POSITIONS
		0.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, // bottom left
		1.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, //bottom right
		1.5 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin, //top right
		0.5 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin, //top right (left)
		0.5 * lineSize + xOrigin, 1 * lineSize + yOrigin, zOrigin, //top right (left) [bottom]
		-0.5 * lineSize + xOrigin, 1 * lineSize + yOrigin, zOrigin, //top left (right) [bottom]
		-0.5 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin, //top left (right)
		-1.5 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin, //top left
		-1.5 * lineSize + xOrigin, yOrigin, zOrigin, //top left (bottom)
		0.5 * lineSize + xOrigin, yOrigin, zOrigin, //middle under
		// BACK POSITIONS
		0.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize, // bottom left
		1.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize, //bottom right
		1.5 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin - lineSize, //top right
		0.5 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin - lineSize, //top right (left)
		0.5 * lineSize + xOrigin, 1 * lineSize + yOrigin, zOrigin - lineSize, //top right (left) [bottom]
		-0.5 * lineSize + xOrigin, 1 * lineSize + yOrigin, zOrigin - lineSize, //top left (right) [bottom]
		-0.5 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin - lineSize, //top left (right)
		-1.5 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin - lineSize, //top left
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

	glGenVertexArrays(1, &this->vao_4_2);
	glBindVertexArray(this->vao_4_2);

	GLuint vertices_VBO;
	glGenBuffers(1, &vertices_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);
	glBufferData(GL_ARRAY_BUFFER, 60 * sizeof(float), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 96 * sizeof(int), indicies, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void LeCherngModel::setLetterG(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin)
{
	GLfloat vertices_lines[] =
	{
		// FRONT POSITION	
		2 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin, //outer top right (Above) 
		2 * lineSize + xOrigin, 1.5 * lineSize + yOrigin, zOrigin, //outer top right (Bottom)
		-1 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin, 
		-1 * lineSize + xOrigin, 1.5 * lineSize + yOrigin, zOrigin, 
		-2 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin, 
		-2 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, 
		-1 * lineSize + xOrigin, -1 * lineSize + yOrigin, zOrigin, 
		2 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, 
		2 * lineSize + xOrigin, -1 * lineSize + yOrigin, zOrigin, 
		1 * lineSize + xOrigin, -1 * lineSize + yOrigin, zOrigin, 
		2 * lineSize + xOrigin, 0 * lineSize + yOrigin, zOrigin, 
		1 * lineSize + xOrigin, 0 * lineSize + yOrigin, zOrigin, 
		0 * lineSize + xOrigin, 0 * lineSize + yOrigin, zOrigin, 
		0 * lineSize + xOrigin, 0.5 * lineSize + yOrigin, zOrigin, 
		2 * lineSize + xOrigin, 0.5 * lineSize + yOrigin, zOrigin, 
		// BACK POSITION
		2 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin - lineSize, //outer top right (Above)
		2 * lineSize + xOrigin, 1.5 * lineSize + yOrigin, zOrigin - lineSize, //outer top right (Bottom)
		-1 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin - lineSize,
		-1 * lineSize + xOrigin, 1.5 * lineSize + yOrigin, zOrigin - lineSize,
		-2 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin - lineSize,
		-2 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize,
		-1 * lineSize + xOrigin, -1 * lineSize + yOrigin, zOrigin - lineSize,
		2 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize,
		2 * lineSize + xOrigin, -1 * lineSize + yOrigin, zOrigin - lineSize,
		1 * lineSize + xOrigin, -1 * lineSize + yOrigin, zOrigin - lineSize,
		2 * lineSize + xOrigin, 0 * lineSize + yOrigin, zOrigin - lineSize,
		1 * lineSize + xOrigin, 0 * lineSize + yOrigin, zOrigin - lineSize,
		0 * lineSize + xOrigin, 0 * lineSize + yOrigin, zOrigin - lineSize,
		0 * lineSize + xOrigin, 0.5 * lineSize + yOrigin, zOrigin - lineSize,
		2 * lineSize + xOrigin, 0.5 * lineSize + yOrigin, zOrigin - lineSize,
	}; //30*3 = 90

	int indicies_lines[] =
	{
		// FRONT INDICIES
		0,1,2,
		2,3,1,
		2,4,5,
		2,5,6,
		5,6,7,
		8,7,6,
		9,8,10,
		11,9,10,
		14,12,10,
		14,12,13,
		// BACK INDICIES
		15,16,17,
		17,18,16,
		17,19,20,
		17,20,21,
		20,21,22,
		23,22,21,
		24,23,25,
		26,24,25,
		29,18,25,
		29,27,26,
		// SIDES
		0,1,16, //top right side 
		16,15,0,
		4,19,15, //top
		15,4,0,
		1,3,16, // inner top
		16,18,3, 
		3,6,21, //inner left
		21,18,3,
		6,9,24,
		24,6,21,
		9,11,26, //bottom
		26,24,9,
		12,10,25,
		25,27,12,
		13,12,27,
		27,28,13,
		13,14,29,
		29,28,13,
		14,7,22, //bottom right
		22,29,14,
		5,7,22, //bottom
		22,20,5,
		4,5,20, //left
		20,19,4
	}; //(24 + 20) *3  = 132

	glGenVertexArrays(1, &this->vao_G);
	glBindVertexArray(this->vao_G);

	GLuint vertices_VBO;
	glGenBuffers(1, &vertices_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(vertices_lines) / sizeof(vertices_lines[0])) * sizeof(float), vertices_lines, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);  //3*sizeof(GLfloat) is the offset of 3 float numbers

	indiciesG = (sizeof(indicies_lines) / sizeof(indicies_lines[0]));
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiciesG * sizeof(int), indicies_lines, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}