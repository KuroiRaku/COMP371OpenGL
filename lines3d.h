#include <glad/glad.h>	
#include <glfw/glfw3.h>	
#include <iostream>
#include "Shader.h"
#include "Cylinder.h"
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>


#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Shader.h"
#include "Cylinder.h"


class Lines3d
{

public:
<<<<<<< Updated upstream
	Lines3d();

	void drawLines(GLint mm, Shader* shader, glm::mat4 objectMatrix);

	Cylinder cylinderX;
	Cylinder cylinderY;
	Cylinder cylinderZ;

	glm::mat4 matrix_X;
	glm::mat4 matrix_Y;
	glm::mat4 matrix_Z;
=======

	glm::mat4 matX;
	glm::mat4 matY;
	glm::mat4 matZ;
	Cylinder cX;
	Cylinder cY;
	Cylinder cZ;


	void drawLines(GLint mm, Shader* shader, glm::mat4 objectMatrix) {
		GLuint mm_loc = shader->GetUniformLocation("mm");
		matX = objectMatrix * matX;
		glUniform3fv(shader->GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(1, 0, 0)));
		glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(matX));
		cX.draw(shader);
		matY = objectMatrix * matY;
		glUniform3fv(shader->GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(0, 1, 0)));
		glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(matY));
		cY.draw(shader);
		matZ = objectMatrix * matZ;
		glUniform3fv(shader->GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(0, 0, 1)));
		glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(matZ));
		cZ.draw(shader);
		glUniform3fv(shader->GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(1, 1, 1)));//Back to grey for grid
		glUniformMatrix4fv(mm, 1, 0, glm::value_ptr(objectMatrix));
	
	
	};
	Lines3d() {
		cX = Cylinder(2.5f, 1, 0.25f);
		cY = Cylinder(2.5f, 1, 0.25f);
		cZ = Cylinder(2.5f, 1, 0.25f);


		matX = glm::mat4(1.f);
		matX = glm::rotate(matX, glm::radians(90.f), glm::vec3(0, 1, 0));
		matY = glm::mat4(1.f);
		matY = glm::rotate(matY, glm::radians(90.f), glm::vec3(-1, 0, 0));
		matZ = glm::mat4(1.f);
		matZ = glm::rotate(matZ, glm::radians(0.f), glm::vec3(-1, 0, 0));
	};


>>>>>>> Stashed changes

};


