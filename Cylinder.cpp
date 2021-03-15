///////////////////////////////////////////////////////////////////////////////
// https://github.com/arunkumarsadhana/opengl_cylinder_shaders/blob/master/Project2_opengl_cylinder/Source.cpp
///////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <iomanip>
#include <cmath>
#include "Cylinder.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static const int N = 5;
static const int M = 3;

float toRadians(float degrees) { return (degrees * 2.0f * 3.14159f) / 360.0f; }

///////////////////////////////////////////////////////////////////////////////
// ctor
///////////////////////////////////////////////////////////////////////////////
Cylinder::Cylinder(float Length, float size, float radius)
{
    GLfloat vertices[] =
    {
        // bottom circle
        0, 0, 0 , //origin
        0,-radius *size,0,
        -(radius * glm::cos(45)) * size,-(radius * glm::cos(45)) * size,0,
        -radius * size,0,0,
        -(radius * glm::cos(45)) * size,(radius * glm::cos(45))* size,0,
        0,radius * size,0,
        (radius * glm::cos(45))* size,(radius * glm::cos(45))* size,0,
        radius * size,0,0,
        (radius * glm::cos(45))* size,-(radius * glm::cos(45)) * size,0,

        //upper part
        0, 0, Length* size, //origin
        0,-radius * size,Length* size,
        -(radius * glm::cos(45)) * size,-(radius * glm::cos(45)) * size,Length* size,
        -radius * size,0,Length * size,
        -(radius * glm::cos(45)) * size,(radius * glm::cos(45))* size,Length* size,
        0,radius * size,Length* size,
        (radius * glm::cos(45))* size,(radius * glm::cos(45))* size,Length* size,
        radius * size,0,Length* size,
        (radius * glm::cos(45))* size,-(radius * glm::cos(45)) * size,Length* size
    };

    int indices[] =
    {
        // Bottom
        0,1,2,
        0,2,3,
        0,3,4,
        0,4,5,
        0,5,6,
        0,6,7,
        0,7,8,
        0,8,1,

        //Upper Circle
        9,11,10,
        9,12,11,
        9,13,12,
        9,14,13,
        9,15,14,
        9,16,15,
        9,17,16,
        9,10,17,

        //Side
        1,10,2,
        2,10,11,
        2,11,3,
        3,11,12,

        //Quarter Arc
        3,12,4,
        4,12,13,
        4,13,5,
        5,13,14,

        //Another Quarter Arc
        5,14,6,
        6,14,15,
        6,15,7,
        7,15,16,

        //Final Quarter Arc
        7,16,8,
        8,16,17,
        8,16,1,
        1,16,10

    };




    glGenVertexArrays(1, &this->vao_Cylinder);
    glBindVertexArray(this->vao_Cylinder);

    GLuint vertices_VBO;
    glGenBuffers(1, &vertices_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);
    glBufferData(GL_ARRAY_BUFFER, (sizeof(vertices) / sizeof(vertices[0])) * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);


    indicesCylinder = (sizeof(indices) / sizeof(indices[0]));
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCylinder * sizeof(int), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}



///////////////////////////////////////////////////////////////////////////////
// draw a cylinder in VertexArray mode
// OpenGL RC must be set before calling it
///////////////////////////////////////////////////////////////////////////////
void Cylinder::draw(Shader* shader)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBindVertexArray(this->vao_Cylinder);
    glDrawElements(GL_TRIANGLES, indicesCylinder, GL_UNSIGNED_INT, NULL);

    //glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, NULL);

}