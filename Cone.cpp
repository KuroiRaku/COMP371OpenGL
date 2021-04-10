
#include "Cone.h"

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
//Source: https://github.com/arunkumarsadhana/opengl_cylinder_shaders/blob/master/Project2_opengl_cylinder/Source.cpp Edited around PA1

Cone::Cone(float Length, float size, float radius)
{
    const int NUMBER_OF_VERTICIES = 54;
    const int ORIGINAL_STRIDE = 3;

    GLfloat vertices[] =
    {
        0, 0, 0 , //0
        0,-radius * size,0, //1
        -(radius * glm::cos(45)) * size,-(radius * glm::cos(45)) * size,0, //2
        -radius * size,0,0, //3
        -(radius * glm::cos(45)) * size,(radius * glm::cos(45)) * size,0, //4
        0,radius * size,0, //5
        (radius * glm::cos(45)) * size,(radius * glm::cos(45)) * size,0, //6
        radius * size,0,0, //7
        (radius * glm::cos(45)) * size,-(radius * glm::cos(45)) * size,0, //8
        //Gathering point
        0, 0, Length * size,  //9
        0, 0, Length * size, //10
        0, 0, Length * size, //11
        0, 0, Length * size, //12
        0, 0, Length * size, //13
        0, 0, Length * size, //14
        0, 0, Length * size, //15
        0, 0, Length * size, //16
        0, 0, Length * size //17
    };

    const int NUMBER_OF_INDICIES = 96;

    int indices[] =
    {
        // B
        0,1,2,
        0,2,3,
        0,3,4,
        0,4,5,
        0,5,6,
        0,6,7,
        0,7,8,
        0,8,1,
        //U
        9,11,10,
        9,12,11,
        9,13,12,
        9,14,13,
        9,15,14,
        9,16,15,
        9,17,16,
        9,10,17,
        //S
        1,10,2,
        2,10,11,
        2,11,3,
        3,11,12,
        //A
        3,12,4,
        4,12,13,
        4,13,5,
        5,13,14,
        //A2
        5,14,6,
        6,14,15,
        6,15,7,
        7,15,16,
        //A3
        7,16,8,
        8,16,17,
        8,16,1,
        1,16,10

    };
    //From our Cube, same code to create normals
    glm::vec3 norms[NUMBER_OF_VERTICIES / ORIGINAL_STRIDE];
    for (int i = 0; i < NUMBER_OF_INDICIES; i += ORIGINAL_STRIDE) {
        int p1 = indices[i];
        int p2 = indices[i + 1];
        int p3 = indices[i + 2];

        glm::vec3 point1 = glm::vec3(vertices[p1 * ORIGINAL_STRIDE], vertices[(p1 * ORIGINAL_STRIDE) + 1], vertices[(p1 * ORIGINAL_STRIDE) + 2]);
        glm::vec3 point2 = glm::vec3(vertices[p2 * ORIGINAL_STRIDE], vertices[(p2 * ORIGINAL_STRIDE) + 1], vertices[(p2 * ORIGINAL_STRIDE) + 2]);
        glm::vec3 point3 = glm::vec3(vertices[p3 * ORIGINAL_STRIDE], vertices[(p3 * ORIGINAL_STRIDE) + 1], vertices[(p3 * ORIGINAL_STRIDE) + 2]);

        glm::vec3 vector_u = point2 - point1;
        glm::vec3 vector_v = point3 - point1;

        glm::vec3 normal = glm::vec3(
            (vector_u.y * vector_v.z) - (vector_u.z * vector_v.y),
            (vector_u.z * vector_v.x) - (vector_u.x * vector_v.z),
            (vector_u.x * vector_v.y) - (vector_u.y * vector_v.x)
        );

        norms[p1] = normal;
        norms[p2] = normal;
        norms[p3] = normal;
    }
 
    const int SIZE_OF_NEW_ARRAY = 144;
    GLfloat vertices_norms[SIZE_OF_NEW_ARRAY];
    for (int i = 0; i < NUMBER_OF_VERTICIES; i += ORIGINAL_STRIDE) {
        int norms_row = i / ORIGINAL_STRIDE;
        vertices_norms[i * 2] = vertices[i];
        vertices_norms[(i * 2) + 1] = vertices[i + 1];
        vertices_norms[(i * 2) + 2] = vertices[i + 2];
        vertices_norms[(i * 2) + 3] = norms[norms_row].x;
        vertices_norms[(i * 2) + 4] = norms[norms_row].y;
        vertices_norms[(i * 2) + 5] = norms[norms_row].z;
    }
    glGenVertexArrays(1, &this->vao_Cylinder);
    glBindVertexArray(this->vao_Cylinder);
    GLuint vertices_VBO;
    glGenBuffers(1, &vertices_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);
    glBufferData(GL_ARRAY_BUFFER, (sizeof(vertices) / sizeof(vertices[0])) * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    //normals attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    indicesCylinder = (sizeof(indices) / sizeof(indices[0]));
    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCylinder * sizeof(int), indices, GL_STATIC_DRAW);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Cone::draw(Shader* shader)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBindVertexArray(this->vao_Cylinder);
    glDrawElements(GL_TRIANGLES, indicesCylinder, GL_UNSIGNED_INT, NULL);
}


