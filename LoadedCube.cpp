#include "LoadedCube.h"
#include <vector>
#include "ObjLoaderIndex.h"

LoadedCube::LoadedCube(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat tallNess, GLfloat width, GLfloat length)
{
    Init(centerX, centerY, centerZ, tallNess, width, length);
}

void LoadedCube::Init(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat tallNess, GLfloat width, GLfloat length)
{
	std::vector<int> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> UVs;
	cubeMatrix = glm::translate(glm::mat4(1.f), glm::vec3(centerX, centerY, centerZ));
	cubeMatrix = glm::scale(cubeMatrix, glm::vec3(width, tallNess, length));

	indices_Size = indices.size();

	// loading a cube
	loadOBJ("resources/objects/cube.obj", indices, vertices, normals, UVs);

	// This is for beginners if they have no idea what's the deal with VAO and VBO.
	glGenVertexArrays(1, &vao_Cube);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(vao_Cube); //if you take this off nothing will show up because you haven't linked the VAO to the VBO
							//you have to bind before putting the point

	GLuint vertices_VBO;
	glGenBuffers(1, &vertices_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);  //3*sizeof(GLfloat) is the offset of 3 float numbers
	glEnableVertexAttribArray(0);

	GLuint normals_VBO;
	glGenBuffers(1, &normals_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, normals_VBO);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);  //3*sizeof(GLfloat) is the offset of 3 float numbers
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices.front(), GL_STATIC_DRAW);

	// Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
	glBindVertexArray(0);
}

void LoadedCube::drawModel()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(this->vao_Cube);
	glDrawElements(GL_TRIANGLES, indices_Size, GL_UNSIGNED_INT, NULL);
}
