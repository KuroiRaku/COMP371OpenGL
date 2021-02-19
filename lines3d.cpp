#include "lines3d.h"

Lines3d::Lines3d() 
{

	cylinderX = Cylinder(2.5f,1.f, 0.5);
	cylinderY = Cylinder(2.5f,1.f, 0.5);
	cylinderZ = Cylinder(2.5f,1.f, 0.5);

	matrix_X = glm::mat4(1.f);
	matrix_Y = glm::mat4(1.f);
	matrix_Z = glm::mat4(1.f);

	matrix_X = glm::rotate(matrix_X, glm::radians(90.f), glm::vec3(0, 1, 0));
	matrix_Y = glm::rotate(matrix_Y, glm::radians(90.f), glm::vec3(-1, 0, 0));
	matrix_Z = glm::rotate(matrix_Z, glm::radians(0.f), glm::vec3(-1, 0, 0));
	
}


void Lines3d::drawLines(GLint mm, Shader* shader, glm::mat4 objectMatrix)
{
	GLuint mm_loc = shader->GetUniformLocation("mm");
	matrix_X = objectMatrix * matrix_X;
	glUniform3fv(shader->GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(1, 0, 0)));
	glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(matrix_X));
	cylinderX.draw(shader);
	matrix_Y = objectMatrix * matrix_Y;
	glUniform3fv(shader->GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(0, 1, 0)));
	glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(matrix_Y));
	cylinderY.draw(shader);
	matrix_Z = objectMatrix * matrix_Z;
	glUniform3fv(shader->GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(0, 0, 1)));
	glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(matrix_Z));
	cylinderZ.draw(shader);

	//glUniformMatrix4fv(mm, 1, 0, glm::value_ptr(objectMatrix));

}

