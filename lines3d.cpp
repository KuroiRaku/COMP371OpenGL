#include "lines3d.h"

Lines3d::Lines3d() {

	GLfloat lineSize = 0.4f * 7; // 7 times the size of 1 grid unit

	GLfloat vertices_lines[] =
	{
		// position		// color
		0.0f,0.0f,0.0f, 1.0f, 0.0f, 0.0f,
		0.0f,lineSize,0.0f, 1.0f, 0.0f, 0.0f,
		0.0f,0.0f,0.0f, 0.0f, 1.0f, 0.0f,
		lineSize,0.0f,0.0f, 0.0f, 1.0f, 0.0f,
		0.0f,0.0f,0.0f, 0.0f, 0.0f, 1.0f,
		0.0f,0.0f,lineSize, 0.0f, 0.0f, 1.0f,
	};

	int indicies_lines[] =
	{
		0,1,
		2,3,
		3,4
	};

	glGenVertexArrays(1, &this->vao);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(this->vao);

	GLuint vertices_VBO_lines;
	glGenBuffers(1, &vertices_VBO_lines);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO_lines);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(float), vertices_lines, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);  //3*sizeof(GLfloat) is the offset of 3 float numbers
	glEnableVertexAttribArray(0);

	//color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint EBO_lines;
	glGenBuffers(1, &EBO_lines);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_lines);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * sizeof(int), indicies_lines, GL_STATIC_DRAW);
	glBindVertexArray(0);
}

GLuint Lines3d::getVAO()
{
	return this->vao;
}

int Lines3d::getIndicesSize()
{
	return 6;
}

void Lines3d::drawLines()
{
	glBindVertexArray(this->vao);
	glDrawArrays(GL_LINES, 0, 6);
}

