#ifndef SPHERE_H
#define SPHERE_H
#include <glad/glad.h>	
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Sphere
{
public:
    Sphere(float x, float y, float z, float xLength, float yLength);
    ~Sphere();
    void init(float x, float y, float z, float xLength, float yLength);
    void draw();
    glm::mat4 sphereMatrix = glm::mat4(1.0f);
private:
    
    int lats, longs;
    bool isInited;
    GLuint m_vao, m_vboVertex, m_vboIndex;
    int numsToDraw;
};

#endif // SPHERE_H