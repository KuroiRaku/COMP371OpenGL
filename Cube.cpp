#include "Cube.h"

Cube::Cube(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat tallNess, GLfloat width, GLfloat length) {
    SetCube(centerX, centerY, centerZ, 1, tallNess, width, length);
}
void Cube::SetCube(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat edgeLength, GLfloat tallNess, GLfloat width, GLfloat length)
{
    GLfloat halfSide = edgeLength * 0.5f;

    GLfloat vertices[] =
    {

        // back face
centerX - halfSide, centerY - halfSide, centerZ - halfSide , 0.0f,  0.0f, -1.0f,// bottom left 7
centerX + halfSide + width , centerY + halfSide + tallNess, centerZ - halfSide ,0.0f,  0.0f, -1.0f, // top right 5
centerX + halfSide + width , centerY - halfSide, centerZ - halfSide , 0.0f,  0.0f, -1.0f,// bottom right 6 
centerX + halfSide + width , centerY + halfSide + tallNess, centerZ - halfSide ,0.0f,  0.0f, -1.0f, // top right 5
centerX - halfSide, centerY - halfSide, centerZ - halfSide , 0.0f,  0.0f, -1.0f,// bottom left 7
centerX - halfSide, centerY + halfSide + tallNess, centerZ - halfSide,0.0f,  0.0f, -1.0f, // top left 4 


        // front face
centerX - halfSide, centerY - halfSide, centerZ + halfSide + length, 0.0f,  0.0f, 1.0f, // bottom left 3
centerX + halfSide + width , centerY - halfSide, centerZ + halfSide + length, 0.0f,  0.0f, 1.0f, // bottom right 2
centerX + halfSide + width , centerY + halfSide + tallNess, centerZ + halfSide + length,  0.0f,  0.0f, 1.0f, // top right  1
centerX + halfSide + width , centerY + halfSide + tallNess, centerZ + halfSide + length,  0.0f,  0.0f, 1.0f, // top right  1
centerX - halfSide, centerY + halfSide + tallNess, centerZ + halfSide + length,  0.0f,  0.0f, 1.0f, // top left 0
centerX - halfSide, centerY - halfSide, centerZ + halfSide + length, 0.0f,  0.0f, 1.0f, // bottom left 3



        // left face
centerX - halfSide, centerY + halfSide + tallNess, centerZ + halfSide + length ,-1.0f,  0.0f,  0.0f, // top left 8
centerX - halfSide, centerY + halfSide + tallNess, centerZ - halfSide,-1.0f,  0.0f,  0.0f, // top right 9
centerX - halfSide, centerY - halfSide, centerZ - halfSide,-1.0f,  0.0f,  0.0f, // bottom right 10
centerX - halfSide, centerY - halfSide, centerZ - halfSide,-1.0f,  0.0f,  0.0f, // bottom right 10
centerX - halfSide, centerY - halfSide, centerZ + halfSide + length ,-1.0f,  0.0f,  0.0f, // bottom left 11
centerX - halfSide, centerY + halfSide + tallNess, centerZ + halfSide + length ,-1.0f,  0.0f,  0.0f, // top left 8

        // right face
centerX + halfSide + width, centerY + halfSide + tallNess, centerZ + halfSide + length, 1.0f,  0.0f,  0.0f,// top left 12
centerX + halfSide + width, centerY - halfSide, centerZ - halfSide , 1.0f,  0.0f,  0.0f,// bottom right 14
centerX + halfSide + width, centerY + halfSide + tallNess, centerZ - halfSide ,1.0f,  0.0f,  0.0f, // top right 13
centerX + halfSide + width, centerY - halfSide, centerZ - halfSide , 1.0f,  0.0f,  0.0f,// bottom right 14
centerX + halfSide + width, centerY + halfSide + tallNess, centerZ + halfSide + length, 1.0f,  0.0f,  0.0f,// top left 12
centerX + halfSide + width, centerY - halfSide, centerZ + halfSide + length,1.0f,  0.0f,  0.0f, // bottom left 15

        // bot face
centerX + halfSide + width, centerY - halfSide, centerZ - halfSide, 0.0f, -1.0f,  0.0f,// bottom right 22
centerX + halfSide + width, centerY - halfSide, centerZ + halfSide + length,0.0f, -1.0f,  0.0f, // bottom left 23
centerX - halfSide, centerY - halfSide, centerZ + halfSide + length,0.0f, -1.0f,  0.0f, // top left 20
centerX - halfSide, centerY - halfSide, centerZ + halfSide + length,0.0f, -1.0f,  0.0f, // top left 20
centerX - halfSide, centerY - halfSide, centerZ - halfSide , 0.0f, -1.0f,  0.0f,// top right 21
centerX + halfSide + width, centerY - halfSide, centerZ - halfSide, 0.0f, -1.0f,  0.0f,// bottom right 22


        // top face
centerX - halfSide, centerY + halfSide + tallNess, centerZ + halfSide + length,0.0f,  1.0f,  0.0f, // top left 16
centerX + halfSide + width, centerY + halfSide + tallNess, centerZ - halfSide ,0.0f,  1.0f,  0.0f, // bottom right 18
centerX - halfSide, centerY + halfSide + tallNess, centerZ - halfSide , 0.0f,  1.0f,  0.0f,// top right 17
centerX + halfSide + width, centerY + halfSide + tallNess, centerZ - halfSide ,0.0f,  1.0f,  0.0f, // bottom right 18
centerX - halfSide, centerY + halfSide + tallNess, centerZ + halfSide + length,0.0f,  1.0f,  0.0f, // top left 16
centerX + halfSide + width, centerY + halfSide + tallNess, centerZ + halfSide + length,0.0f,  1.0f,  0.0f, // bottom left 19


    };
    unsigned int VBO;
    glGenVertexArrays(1, &vao_Cube);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(vao_Cube);

    // position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    
    // normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)



}
void Cube::drawModel() {

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBindVertexArray(this->vao_Cube);
    glDrawArrays(GL_TRIANGLES, 0, 36);

}