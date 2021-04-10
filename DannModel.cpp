#include "DannModel.h"
using namespace std;


DannModel::DannModel() {
	GLfloat xOrigin = 0.0f;
	GLfloat yOrigin = 0.0f;
	GLfloat zOrigin = 0.0f;

	lineSize = 0.4f * 2;

	distance = 2.5f;
	
	
	setLetterD(xOrigin - (3 * distance), yOrigin, zOrigin, 0, 0);
	setNumber7(xOrigin + (1 * distance), yOrigin, zOrigin, 0, 0);
	setLetterN(xOrigin - (1 * distance), yOrigin, zOrigin, 0,0);
	setNumber4(xOrigin + (3 * distance), yOrigin, zOrigin, 0,0);

	mode = GL_TRIANGLES;
}

void DannModel::drawModel(int drawMode, Texture* boxTexture, Texture* metalTexture, float shearX, float shearY, Shader* shader,  glm::mat4 objectMatrix)
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

	metalTexture->Bind();
	Cube cube = Cube(0, 0, 0, 4, 0, 0);
	cube.drawModel();
	Sphere s = Sphere(2, 2, 0, 2, 0.5);
	s.sphereMatrix = glm::rotate(s.sphereMatrix, glm::radians(50.f), glm::vec3(0, 0, 1));
	s.sphereMatrix = objectMatrix * s.sphereMatrix;
	GLuint mm_loc = shader->GetUniformLocation("mm");
	glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(s.sphereMatrix));
	s.drawModel();
	s = Sphere(0.2, 4, 0, 2, 0.5);
	glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(objectMatrix));
	s.sphereMatrix = glm::rotate(s.sphereMatrix, glm::radians(50.f), glm::vec3(0, 0, -1));
	s.sphereMatrix = objectMatrix * s.sphereMatrix;
	mm_loc = shader->GetUniformLocation("mm");
	glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(s.sphereMatrix));
	s.drawModel();
	

	metalTexture->Unbind();
}

void DannModel::setLetterN(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin, float shearX, float shearY)
{
	
}

void DannModel::setNumber4(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin, float shearX, float shearY)
{
	
}

void DannModel::setNumber7(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin, float shearX, float shearY)
{
	
}

void DannModel::setLetterD(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin, float shearX, float shearY)
{
	
		
}