#include "grid.h"


Grid::Grid() {
    std::vector<glm::vec3> vertices;
    std::vector<glm::uvec4> indices;
    int slices = 128;
    float grid_size = 50.0f;
    float offset = grid_size / 2.0; // centers the grid


    for (int j = 0; j <= slices; ++j) {
        for (int i = 0; i <= slices; ++i) {
            float x = ((float)i * grid_size/ (float)slices) - offset;
            float y = 0;
            float z = ((float)j * grid_size/ (float)slices) - offset;
            vertices.push_back(glm::vec3(x, y, z));
        }
    }

    for (int j = 0; j < slices; ++j) {
        for (int i = 0; i < slices; ++i) {

            int row1 = j * (slices + 1);
            int row2 = (j + 1) * (slices + 1);

            indices.push_back(glm::uvec4(row1 + i, row1 + i + 1, row1 + i + 1, row2 + i + 1));
            indices.push_back(glm::uvec4(row2 + i + 1, row2 + i, row2 + i, row1 + i));

        }
    }

    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), glm::value_ptr(vertices[0]), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(glm::uvec4), glm::value_ptr(indices[0]), GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    this->length = (GLuint)indices.size() * 4;
}

GLuint Grid::getVAO() 
{
    return this->vao;
};

int Grid::getLength()
{
    return this->length;
}

void Grid::drawGrid()
{
    glBindVertexArray(this->vao);
    glDrawElements(GL_LINES, this->length, GL_UNSIGNED_INT, NULL);
}