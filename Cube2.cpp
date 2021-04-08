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
	

	//GLfloat normals[24] = { *calculateNormals(vertices) };
	
	/*
	float normals[24];
	for (int i = 0; i < 24; i += 8)
	{
		int vec2_x = (i + 3) < 24 ? (i + 3) : (i + 3) - 24;
		int vec2_y = (i + 4) < 24 ? (i + 4) : (i + 4) - 24;
		int vec2_z = (i + 5) < 24 ? (i + 5) : (i + 5) - 24;

		int vec3_x = (i + 6) < 24 ? (i + 6) : (i + 6) - 24;
		int vec3_y = (i + 7) < 24 ? (i + 7) : (i + 7) - 24;
		int vec3_z = (i + 8) < 24 ? (i + 8) : (i + 8) - 24;

		glm::vec3 current_vec = glm::vec3(vertices[i], vertices[i + 1], vertices[i + 2]);
		glm::vec3 vec_2 = glm::vec3(vertices[vec2_x], vertices[vec2_y], vertices[vec2_z]);
		glm::vec3 vec_3 = glm::vec3(vertices[vec3_x], vertices[vec3_y], vertices[vec3_z]);
		glm::vec3 normal = glm::normalize(
			glm::cross(
				glm::vec3(vec_2) - glm::vec3(current_vec),
				glm::vec3(vec_3) - glm::vec3(current_vec)));

		// vec 1
		normals[i] = normal.x;
		normals[i + 1] = normal.y;
		normals[i + 2] = normal.z;

		// vec 2
		normals[vec2_x] = normal.x;
		normals[vec2_y] = normal.y;
		normals[vec2_z] = normal.z;

		// vec 3
		normals[vec3_x] = normal.x;
		normals[vec3_y] = normal.y;
		normals[vec3_z] = normal.z;
	}
	*/

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


GLfloat * Cube2::calculateNormals(GLfloat verts[]) {
	GLfloat norm[24];
	for (int i = 0; i < 24; i += 8)
	{
		int vec2_x = (i + 3) < 24 ? (i + 3) : (i + 3) - 24;
		int vec2_y = (i + 4) < 24 ? (i + 4) : (i + 4) - 24;
		int vec2_z = (i + 5) < 24 ? (i + 5) : (i + 5) - 24;

		int vec3_x = (i + 6) < 24 ? (i + 6) : (i + 6) - 24;
		int vec3_y = (i + 7) < 24 ? (i + 7) : (i + 7) - 24;
		int vec3_z = (i + 8) < 24 ? (i + 8) : (i + 8) - 24;

		glm::vec3 current_vec = glm::vec3(verts[i], verts[i + 1], verts[i + 2]);
		glm::vec3 vec_2 = glm::vec3(verts[vec2_x], verts[vec2_y], verts[vec2_z]);
		glm::vec3 vec_3 = glm::vec3(verts[vec3_x], verts[vec3_y], verts[vec3_z]);
		glm::vec3 normal = glm::normalize(
			glm::cross(
				glm::vec3(vec_2) - glm::vec3(current_vec),
				glm::vec3(vec_3) - glm::vec3(current_vec)));

		// vec 1
		norm[i] = normal.x;
		norm[i + 1] = normal.y;
		norm[i + 2] = normal.z;

		// vec 2
		norm[vec2_x] = normal.x;
		norm[vec2_y] = normal.y;
		norm[vec2_z] = normal.z;

		// vec 3
		norm[vec3_x] = normal.x;
		norm[vec3_y] = normal.y;
		norm[vec3_z] = normal.z;


	}
	return norm;
}


/*
Begin Function CalculateSurfaceNormal(Input Triangle) Returns Vector

Set Vector U to(Triangle.p2 minus Triangle.p1)
Set Vector V to(Triangle.p3 minus Triangle.p1)

Set Normal.x to(multiply U.y by V.z) minus(multiply U.z by V.y)
Set Normal.y to(multiply U.z by V.x) minus(multiply U.x by V.z)
Set Normal.z to(multiply U.x by V.y) minus(multiply U.y by V.x)

Returning Normal

End Function
*/

