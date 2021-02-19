#ifndef SPHERE_H
#define SPHERE_H
#include <glad/glad.h>	

class Sphere
{
public:
    Sphere(float x, float y, float z, float radius, float elongatedLength);
    ~Sphere();
    void init(float x, float y, float z, float radius, float elongatedLength);
    void draw();

private:
    
    GLuint m_vao, m_vboVertex, m_vboIndex;
    int numsToDraw;
};

#endif // SPHERE_H