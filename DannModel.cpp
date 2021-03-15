#include "DannModel.h"
using namespace std;


DannModel::DannModel() {
	GLfloat xOrigin = 0.0f;
	GLfloat yOrigin = 0.0f;
	GLfloat zOrigin = 0.0f;

	

	GLfloat distance = 2.5f;
	


	
}

void DannModel::drawModel(int drawMode, Shader* shader, glm::mat4 objectMatrix)
{
	
	


	drawLetter(0, 0, 0, shader, objectMatrix);
}

void DannModel::drawLetter(float x, float y, float z, Shader* shader, glm::mat4 objectMatrix)
{
	/*
	Cube cube = Cube(0, 0, 0);
	cube.cubeMatrix = glm::scale(cube.cubeMatrix, glm::vec3(0,1,0));
	cube.cubeMatrix = objectMatrix * cube.cubeMatrix;
	GLuint mm_loc2 = shader->GetUniformLocation("mm");
	glUniformMatrix4fv(mm_loc2, 1, 0, glm::value_ptr(cube.cubeMatrix));
	cube.drawModel();
	*/
	Cube cube = Cube(0, 0, 0,4);
	cube.drawModel();
	Sphere s = Sphere(2,2,0, 2, 0.5);
	s.sphereMatrix = glm::rotate(s.sphereMatrix, glm::radians(50.f), glm::vec3(0, 0, 1));
	s.sphereMatrix = objectMatrix * s.sphereMatrix;
	GLuint mm_loc = shader->GetUniformLocation("mm");
	glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(s.sphereMatrix));
	s.draw();
	//Cancelling rotation for next object
	s = Sphere(0.2, 4,0, 2, 0.5);
	glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(objectMatrix));
<<<<<<< Updated upstream
	cube.drawModel();
}



void DannModel::setLetterN(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin)
{
	GLfloat vertices[] =
	{
		// FRONT POSITIONS
		0.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, // bottom left 0
		1.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, //bottom right 1
		1.5 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin, //top right 2
		0.5 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin, //top right (left) 3

		0.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize, // bottom left 4
		1.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize, //bottom right 5 
		1.5 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin - lineSize, //top right 6
		0.5 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin - lineSize, //top right (left) 7
		//Right 
		1.5 * lineSize + xOrigin, 0.5 * lineSize + yOrigin, zOrigin, //8
		1.5 * lineSize + xOrigin, 0.5 * lineSize + yOrigin, zOrigin - lineSize,//9

		1.5 * lineSize + xOrigin, 1.5 * lineSize + yOrigin, zOrigin,//10
		1.5 * lineSize + xOrigin, 1.5 * lineSize + yOrigin, zOrigin - lineSize,//11
		3.0 * lineSize + xOrigin, 0.5 * lineSize + yOrigin, zOrigin,//12
		3.0 * lineSize + xOrigin, 0.5 * lineSize + yOrigin, zOrigin - lineSize,//13
		3.0 * lineSize + xOrigin, 1.5 * lineSize + yOrigin, zOrigin,//14
		3.0 * lineSize + xOrigin, 1.5 * lineSize + yOrigin, zOrigin - lineSize,//15
		2.5 * lineSize + xOrigin, 0.5 * lineSize + yOrigin, zOrigin,//16
		2.5 * lineSize + xOrigin, 0.5 * lineSize + yOrigin, zOrigin - lineSize,//17
		2.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, // bottom left 18
		2.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize, // bottom left  19
		3.0 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, // bottom left 20
		3.0 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize, // bottom left  21


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
		0.5 * lineSize + xOrigin, -2.5 * lineSize + yOrigin, zOrigin, //  0
		1.5 * lineSize + xOrigin, -2.5 * lineSize + yOrigin, zOrigin, // 1
		1.5 * lineSize + xOrigin, 2.5 * lineSize + yOrigin, zOrigin, // 2
		0.5 * lineSize + xOrigin, 2.5 * lineSize + yOrigin, zOrigin, // 3
		0.5 * lineSize + xOrigin, 1.5 * lineSize + yOrigin, zOrigin, // 4
		-0.5 * lineSize + xOrigin, 1.5 * lineSize + yOrigin, zOrigin, // 5
		-0.5 * lineSize + xOrigin, 2.5 * lineSize + yOrigin, zOrigin, // 6
		-1.5 * lineSize + xOrigin, 2.5 * lineSize + yOrigin, zOrigin, // 7
		-1.5 * lineSize + xOrigin, yOrigin, zOrigin, // 8
		0.5 * lineSize + xOrigin, yOrigin, zOrigin, // 9

		// BACK POSITIONS
		0.5 * lineSize + xOrigin, -2.5 * lineSize + yOrigin, zOrigin - lineSize, //  10
		1.5 * lineSize + xOrigin, -2.5 * lineSize + yOrigin, zOrigin - lineSize, // 11
		1.5 * lineSize + xOrigin, 2.5 * lineSize + yOrigin, zOrigin - lineSize, // 12
		0.5 * lineSize + xOrigin, 2.5 * lineSize + yOrigin, zOrigin - lineSize, //  13
		0.5 * lineSize + xOrigin, 1.5 * lineSize + yOrigin, zOrigin - lineSize, // 14
		-0.5 * lineSize + xOrigin, 1.5 * lineSize + yOrigin, zOrigin - lineSize, // 15
		-0.5 * lineSize + xOrigin, 2.5 * lineSize + yOrigin, zOrigin - lineSize, // 16
		-1.5 * lineSize + xOrigin, 2.5 * lineSize + yOrigin, zOrigin - lineSize, // 17
		-1.5 * lineSize + xOrigin, yOrigin, zOrigin - lineSize, // 18
		0.5 * lineSize + xOrigin, yOrigin, zOrigin - lineSize, // 19

		1.5 * lineSize + xOrigin, + yOrigin, zOrigin, // 20
		1.5 * lineSize + xOrigin, +yOrigin, zOrigin - lineSize, // 21
		2.5 * lineSize + xOrigin, +yOrigin, zOrigin, // 22
		2.5 * lineSize + xOrigin, +yOrigin, zOrigin - lineSize, // 23

		1.5 * lineSize + xOrigin,0.5 * lineSize +yOrigin, zOrigin, // 24 unsused
		1.5 * lineSize + xOrigin,0.5 * lineSize +yOrigin, zOrigin - lineSize, // 25 unsused
		2.5 * lineSize + xOrigin,0.5 * lineSize +yOrigin, zOrigin, // 26 unused for now
		2.5 * lineSize + xOrigin,0.5 * lineSize +yOrigin, zOrigin - lineSize, // 27 unused
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
		-0.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, //bottom left
		0.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin, //bottom right
		0.5 * lineSize + xOrigin, 3 * lineSize + yOrigin, zOrigin, //top right
		-2.0 * lineSize + xOrigin, 3 * lineSize + yOrigin, zOrigin, // top left
		-2.0 * lineSize + xOrigin, 2*lineSize + yOrigin, zOrigin, //under left
		-0.5 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin, //middle tucked
		//BACK POSITION
		-0.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize, //bottom left
		0.5 * lineSize + xOrigin, -2 * lineSize + yOrigin, zOrigin - lineSize, //bottom right
		0.5 * lineSize + xOrigin, 3 * lineSize + yOrigin, zOrigin - lineSize, //top right
		-2.0 * lineSize + xOrigin, 3 * lineSize + yOrigin, zOrigin - lineSize, // top left
		-2.0 * lineSize + xOrigin, 2 *lineSize + yOrigin, zOrigin - lineSize, //under left
		-0.5 * lineSize + xOrigin, 2 * lineSize + yOrigin, zOrigin - lineSize, //middle tucked
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
=======
	s.sphereMatrix = glm::rotate(s.sphereMatrix, glm::radians(50.f), glm::vec3(0, 0, -1));
	s.sphereMatrix = objectMatrix * s.sphereMatrix;
	 mm_loc = shader->GetUniformLocation("mm");
	glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(s.sphereMatrix));
	s.draw();
>>>>>>> Stashed changes
}



