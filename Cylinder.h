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


class Cylinder
{
public:
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

