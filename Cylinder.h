<<<<<<< Updated upstream
#pragma once
///////////////////////////////////////////////////////////////////////////////
// Cylinder.h
// ==========
// Cylinder for OpenGL with (base radius, top radius, height, sectors, stacks)
// The min number of sectors (slices) is 3 and the min number of stacks are 1.
// - base radius: the radius of the cylinder at z = -height/2
// - top radius : the radiusof the cylinder at z = height/2
// - height     : the height of the cylinder along z-axis
// - sectors    : the number of slices of the base and top caps
// - stacks     : the number of subdivisions along z-axis
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2018-03-27
// UPDATED: 2019-12-02
///////////////////////////////////////////////////////////////////////////////

#ifndef GEOMETRY_CYLINDER_H
#define GEOMETRY_CYLINDER_H

#include <vector>
#include <glad/glad.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library
#include "Shader.h"

struct vertex {
    GLfloat x, y, z, s, t, u;
};

 // vector of structs

struct cylin {
    GLfloat x, y, z;
};
=======

#include <vector>
#include <glad/glad.h>	
#include <glfw/glfw3.h>	
#include "Shader.h"




#include <iostream>
#include <iomanip>
#include <cmath>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>






>>>>>>> Stashed changes


class Cylinder
{
public:
<<<<<<< Updated upstream
    // ctor/dtor
    Cylinder(float Length, float size, float radius);

    Cylinder() {};
    

    // draw in VertexArray mode
    void draw(Shader* shader);          // draw all


protected:

private:
   
    int indicesCylinder;

    GLuint vao_Cylinder;

};

#endif
=======
    int indiciesC;
    GLuint vaoC;
    Cylinder() {

        
    };


    Cylinder(float length, float scale, float diametre) {
    
        initCylinder(length, scale, diametre);
    };

   
    void initCylinder(float length, float scale, float diametre) {
       
            GLfloat vertices[] =
            {
                    0, 0, 0 , // 0 0
                0,-diametre * scale,0, //  1
                 -diametre * scale,0,0, // 2
                    0,diametre* scale,0,// 3
                      diametre* scale,0,0,// 4
                -(diametre * glm::cos(45)) * scale,-(diametre * glm::cos(45)) * scale,0,//  5
                -(diametre * glm::cos(45)) * scale,(diametre * glm::cos(45))* scale,0, // 6
                (diametre * glm::cos(45))* scale,(diametre * glm::cos(45))* scale,0,// 7
                (diametre * glm::cos(45))* scale,-(diametre * glm::cos(45)) * scale,0,// 8
                0, 0, length * scale, //origin 9
                0,-diametre * scale,length * scale, //10
                -(diametre * glm::cos(45)) * scale,-(diametre * glm::cos(45)) * scale,length * scale,//11
                -diametre * scale,0,length * scale,//12
                -(diametre * glm::cos(45)) * scale,(diametre * glm::cos(45)) * scale,length * scale,//13
                0,diametre * scale,length * scale,//14
                (diametre * glm::cos(45)) * scale,(diametre * glm::cos(45)) * scale,length * scale,//15
                diametre * scale,0,length * scale,//16
                (diametre * glm::cos(45)) * scale,-(diametre * glm::cos(45)) * scale,length * scale//17
            };

            int indices[] =
            {
                0,1,5,
                0,5,2,
                0,2,6,
                0,6,3,
                0,3,7,
                0,7,4,
                0,4,8,
                0,8,1,
                9,11,10,
                9,12,11,
                9,13,12,
                9,14,13,
                9,15,14,
                9,16,15,
                9,17,16,
                9,10,17,
                1,10,5,
                5,10,11,
                5,11,2,
                2,11,12,
                2,12,6,
                6,12,13,
                6,13,3,
                3,13,14,
                3,14,7,
                7,14,15,
                7,15,4,
                4,15,16,
                4,16,8,
                8,16,17,
                8,16,1,
                1,16,10

            };




            glGenVertexArrays(1, &this->vaoC);
            glBindVertexArray(this->vaoC);

            GLuint vertices_VBO;
            glGenBuffers(1, &vertices_VBO);
            glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);
            glBufferData(GL_ARRAY_BUFFER, (sizeof(vertices) / sizeof(vertices[0])) * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
            indiciesC = (sizeof(indices) / sizeof(indices[0]));
            GLuint EBO;
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiciesC * sizeof(int), indices, GL_STATIC_DRAW);

            glBindVertexArray(0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        };
   
    
    void draw(Shader* shader) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);
        glBindVertexArray(this->vaoC);
        glDrawElements(GL_TRIANGLES, indiciesC, GL_UNSIGNED_INT, NULL);
    };


    

};




>>>>>>> Stashed changes


