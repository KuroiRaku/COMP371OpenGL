#pragma once
#include <glad/glad.h>    
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class LoadedCube
{

public:
    LoadedCube(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat tallNess, GLfloat width, GLfloat length);

    void Init(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat tallNess, GLfloat width, GLfloat length);
    void drawModel();

    GLuint vao_Cube;
    glm::mat4 cubeMatrix = glm::mat4(1.0f);
    int indices_Size;
};

