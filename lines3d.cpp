#include "lines3d.h"

Lines3d::Lines3d() {

	cylinderX = Cylinder(2.5f, 1.f, 0.125);
	cylinderY = Cylinder(2.5f, 1.f, 0.125);
	cylinderZ = Cylinder(2.5f, 1.f, 0.125);

	coneX = Cone(1.5f, 1.f, 0.5);
	coneY = Cone(1.5f, 1.f, 0.5);
	coneZ = Cone(1.5f, 1.f, 0.5);

	matrix_X = glm::mat4(1.f);
	matrix_Y = glm::mat4(1.f);
	matrix_Z = glm::mat4(1.f);

	matrix_X_Cone = glm::mat4(1.f);
	matrix_Y_Cone = glm::mat4(1.f);
	matrix_Z_Cone = glm::mat4(1.f);

	matrix_X = glm::rotate(matrix_X, glm::radians(90.f), glm::vec3(0, 1, 0));
	matrix_Y = glm::rotate(matrix_Y, glm::radians(90.f), glm::vec3(-1, 0, 0));
	matrix_Z = glm::rotate(matrix_Z, glm::radians(0.f), glm::vec3(-1, 0, 0));

	matrix_X_Cone = glm::translate(matrix_X_Cone, glm::vec3(2.5, 0, 0));
	matrix_Y_Cone = glm::translate(matrix_Y_Cone, glm::vec3(0, 2.5, 0));
	matrix_Z_Cone = glm::translate(matrix_Z_Cone, glm::vec3(0, 0, 2.5));

	matrix_X_Cone = glm::rotate(matrix_X_Cone, glm::radians(90.f), glm::vec3(0, 1, 0));
	matrix_Y_Cone = glm::rotate(matrix_Y_Cone, glm::radians(90.f), glm::vec3(-1, 0, 0));
	matrix_Z_Cone = glm::rotate(matrix_Z_Cone, glm::radians(0.f), glm::vec3(-1, 0, 0));

}

void Lines3d::drawLines(Shader* shader, glm::mat4 objectMatrix)
{	
	glUniform3fv(shader->GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(1, 0, 0)));
	glUniformMatrix4fv(shader->GetUniformLocation("mm"), 1, 0, glm::value_ptr(objectMatrix * matrix_X));
	cylinderX.draw(shader);

	glUniformMatrix4fv(shader->GetUniformLocation("mm"), 1, 0, glm::value_ptr(objectMatrix * matrix_X_Cone));
	coneX.draw(shader);
	
	glUniform3fv(shader->GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(0, 1, 0)));
	glUniformMatrix4fv(shader->GetUniformLocation("mm"), 1, 0, glm::value_ptr(objectMatrix * matrix_Y));
	cylinderY.draw(shader);

	glUniformMatrix4fv(shader->GetUniformLocation("mm"), 1, 0, glm::value_ptr(objectMatrix * matrix_Y_Cone));
	coneY.draw(shader);
	
	glUniform3fv(shader->GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(0, 0, 1)));
	glUniformMatrix4fv(shader->GetUniformLocation("mm"), 1, 0, glm::value_ptr(objectMatrix * matrix_Z));
	cylinderZ.draw(shader);

	glUniformMatrix4fv(shader->GetUniformLocation("mm"), 1, 0, glm::value_ptr(objectMatrix * matrix_Z_Cone));
	coneZ.draw(shader);

	glUniform3fv(shader->GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
}

