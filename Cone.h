#pragma once
#include <Shader.h>
#include <glad\glad.h>

class Cone
{
public:
    // ctor/dtor


    Cone(float Length, float size, float radius);

    Cone() {};


    // draw in VertexArray mode
    void draw(Shader* shader);          // draw all


protected:

private:

    int indicesCylinder;

    GLuint vao_Cylinder;
};

