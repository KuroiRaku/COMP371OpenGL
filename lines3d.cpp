#include "lines3d.h"

Lines3d::Lines3d() {

	cX = Cylinder(2.5f, 1.f, 0.125);
	cY = Cylinder(2.5f, 1.f, 0.125);
	cZ = Cylinder(2.5f, 1.f, 0.125);

	coneX = Cone(1.0f, 1.f, 0.5);
	coneY = Cone(1.0f, 1.f, 0.5);
	coneZ = Cone(1.0f, 1.f, 0.5);

	m_X = glm::mat4(1.f);
	m_Y = glm::mat4(1.f);
	m_Z = glm::mat4(1.f);

	m_X_cone = glm::mat4(1.f);
	m_Y_cone = glm::mat4(1.f);
	m_Z_cone = glm::mat4(1.f);



	m_X_cone = glm::translate(m_X_cone, glm::vec3(2.0, 0, 0));
	m_Y_cone = glm::translate(m_Y_cone, glm::vec3(0, 2.0, 0));
	m_Z_cone = glm::translate(m_Z_cone, glm::vec3(0, 0, 2.0));

	m_X = glm::rotate(m_X, glm::radians(90.f), glm::vec3(0, 1, 0));
	m_Y = glm::rotate(m_Y, glm::radians(90.f), glm::vec3(-1, 0, 0));
	m_Z = glm::rotate(m_Z, glm::radians(0.f), glm::vec3(-1, 0, 0));


	m_X_cone = glm::rotate(m_X_cone, glm::radians(90.f), glm::vec3(0, 1, 0));
	m_Y_cone = glm::rotate(m_Y_cone, glm::radians(90.f), glm::vec3(-1, 0, 0));
	m_Z_cone = glm::rotate(m_Z_cone, glm::radians(0.f), glm::vec3(-1, 0, 0));

}

void Lines3d::drawLines(Shader* shader, glm::mat4 objectMatrix, Texture* texture)
{
	texture->Bind();
	glUniform3fv(shader->GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(1, 0, 0)));
	glUniformMatrix4fv(shader->GetUniformLocation("mm"), 1, 0, glm::value_ptr(objectMatrix * m_X));
	cX.draw(shader);

	glUniformMatrix4fv(shader->GetUniformLocation("mm"), 1, 0, glm::value_ptr(objectMatrix * m_X_cone));
	coneX.draw(shader);
	texture->Unbind();

	glUniform3fv(shader->GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(0, 1, 0)));
	glUniformMatrix4fv(shader->GetUniformLocation("mm"), 1, 0, glm::value_ptr(objectMatrix * m_Y));
	cY.draw(shader);

	glUniformMatrix4fv(shader->GetUniformLocation("mm"), 1, 0, glm::value_ptr(objectMatrix * m_Y_cone));
	coneY.draw(shader);

	glUniform3fv(shader->GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(0, 0, 1)));
	glUniformMatrix4fv(shader->GetUniformLocation("mm"), 1, 0, glm::value_ptr(objectMatrix * m_Z));
	cZ.draw(shader);

	glUniformMatrix4fv(shader->GetUniformLocation("mm"), 1, 0, glm::value_ptr(objectMatrix * m_Z_cone));
	coneZ.draw(shader);

	glUniform3fv(shader->GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
}

