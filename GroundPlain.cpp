#include "GroundPlain.h"

// Small hack for the texture here
// Because textures only display correctly here facing the camera
// Going to create it facing the camera and then rotate it

GroundPlain::GroundPlain() {
	GLfloat plain_size = 30.0f;
	//x,y,z
	GLfloat vertices_lines[] =
	{
		-1 * plain_size,	-1 * plain_size,	0.0f,	//top left
		plain_size,			-1 * plain_size,	0.0f,	//top right
		-1 * plain_size,	plain_size,			0.0f,	//bottom left
		plain_size,			plain_size,			0.0f,	//bottom right
	};

	int indicies_lines[] =
	{
		0,1,2,
		2,1,3	
	};

	glGenVertexArrays(1, &this->vao_ground);
	glBindVertexArray(this->vao_ground);

	GLuint vertices_VBO;
	glGenBuffers(1, &vertices_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertices_lines, GL_STATIC_DRAW);

	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(1);


	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(int), indicies_lines, GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GroundPlain::drawGround(Texture * tileTexture) {
	tileTexture->Bind();

	glBindVertexArray(this->vao_ground);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);// num = indicies

	tileTexture->Unbind();
}