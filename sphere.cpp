#include "sphere.h"

#include <vector>
#include <iostream>

#include <math.h>
#define _USE_MATH_DEFINES
# define M_PI          3.141592653589793238462643383279502884L /* pi */
Sphere::Sphere(float x, float y , float z, float radius, float elongatedLength)
{
   
    m_vao = 0;
    m_vboVertex = 0;
    m_vboIndex = 0;

   
    init(x, y, z, radius, elongatedLength);
}

Sphere::~Sphere()
{

}
const int na = 36;        // vertex grid size
const int nb = 18;
const int na3 = na * 3;     // line in grid size
const int nn = nb * na3;    // whole grid size
GLfloat sphere_pos[nn]; // vertex
GLfloat sphere_nor[nn]; // normal
//GLfloat sphere_col[nn];   // color
GLuint  sphere_ix[na * (nb - 1) * 6];    // indices
GLuint sphere_vbo[4] = { -1,-1,-1,-1 };
GLuint sphere_vao[4] = { -1,-1,-1,-1 };
void Sphere::init(float xOrigin, float yOrigin, float zOrigin, float radius, float elongatedLength)
{
    // generate the sphere data
    GLfloat x, y, z, a, b, da, db, r = 1;
    int ia, ib, ix, iy;
    da = 2.0 * M_PI / GLfloat(na);
    db = M_PI / GLfloat(nb - 1);
    // [Generate sphere point data]
    // spherical angles a,b covering whole sphere surface
    for (ix = 0, b = -0.5 * M_PI, ib = 0; ib < nb; ib++, b += db)
        for (a = 0.0, ia = 0; ia < na; ia++, a += da, ix += 3)
        {
            // unit sphere
            x = cos(b) * cos(a);
            y = cos(b) * sin(a);
            z = sin(b);
            sphere_pos[ix + 0] = (x+xOrigin) * radius;
            sphere_pos[ix + 1] = (y + yOrigin)* elongatedLength;
            sphere_pos[ix + 2] = (z+zOrigin) * radius;
            sphere_nor[ix + 0] = (x + xOrigin);
            sphere_nor[ix + 1] = (y + yOrigin);
            sphere_nor[ix + 2] = (z + zOrigin);
        }
    // [Generate GL_TRIANGLE indices]
    for (ix = 0, iy = 0, ib = 1; ib < nb; ib++)
    {
        for (ia = 1; ia < na; ia++, iy++)
        {
            // first half of QUAD
            sphere_ix[ix] = iy;      ix++;
            sphere_ix[ix] = iy + 1;    ix++;
            sphere_ix[ix] = iy + na;   ix++;
            // second half of QUAD
            sphere_ix[ix] = iy + na;   ix++;
            sphere_ix[ix] = iy + 1;    ix++;
            sphere_ix[ix] = iy + na + 1; ix++;
        }
        // first half of QUAD
        sphere_ix[ix] = iy;       ix++;
        sphere_ix[ix] = iy + 1 - na;  ix++;
        sphere_ix[ix] = iy + na;    ix++;
        // second half of QUAD
        sphere_ix[ix] = iy + na;    ix++;
        sphere_ix[ix] = iy - na + 1;  ix++;
        sphere_ix[ix] = iy + 1;     ix++;
        iy++;
    }
    // [VAO/VBO stuff]
    GLuint i;
    glGenVertexArrays(4, sphere_vao);
    glGenBuffers(4, sphere_vbo);
    glBindVertexArray(sphere_vao[0]);
    i = 0; // vertex
    glBindBuffer(GL_ARRAY_BUFFER, sphere_vbo[i]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sphere_pos), sphere_pos, GL_STATIC_DRAW);
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
    i = 1; // indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphere_vbo[i]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sphere_ix), sphere_ix, GL_STATIC_DRAW);
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, 4, GL_UNSIGNED_INT, GL_FALSE, 0, 0);
    i = 2; // normal
    glBindBuffer(GL_ARRAY_BUFFER, sphere_vbo[i]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sphere_nor), sphere_nor, GL_STATIC_DRAW);
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
    /*
        i=3; // color
        glBindBuffer(GL_ARRAY_BUFFER,sphere_vbo[i]);
        glBufferData(GL_ARRAY_BUFFER,sizeof(sphere_col),sphere_col,GL_STATIC_DRAW);
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i,3,GL_FLOAT,GL_FALSE,0,0);
    */
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
}

    

void Sphere::draw()
{
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glBindVertexArray(sphere_vao[0]);
    //  glDrawArrays(GL_POINTS,0,sizeof(sphere_pos)/sizeof(GLfloat));                   // POINTS ... no indices for debug
    glDrawElements(GL_TRIANGLES, sizeof(sphere_ix) / sizeof(GLuint), GL_UNSIGNED_INT, 0);    // indices (choose just one line not both !!!)
    glBindVertexArray(0);
}