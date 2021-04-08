#pragma once
#include <glad/glad.h>    
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Cube2
{
public:
    GLuint vao_Cube;
    int indiciesC;
    void drawModel();
    Cube2(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat tallNess, GLfloat width, GLfloat length);
    Cube2() {};
    void SetCube(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat edgeLength, GLfloat tallNess, GLfloat width, GLfloat length);
    glm::mat4 cubeMatrix = glm::mat4(1.0f);
};

