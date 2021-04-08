#include "GroundPlane2.h"




// Small hack for the texture here
// Because textures only display correctly here facing the camera
// Going to create it facing the camera and then rotate it

GroundPlane2::GroundPlane2() {

    groundMatrix = ground.cubeMatrix;

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float planeVertices[] = {
        // positions            // normals         
         25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,
        -25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,
        -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,

         25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,
        -25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,
         25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,
    };
    // plane VAO
    unsigned int planeVBO;
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindVertexArray(0);

}

void GroundPlane2::drawGround(Texture* tileTexture) {
    tileTexture->Bind();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBindVertexArray(this->planeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    tileTexture->Unbind();
}