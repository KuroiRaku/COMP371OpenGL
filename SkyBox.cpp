#include "SkyBox.h"

using namespace std;


SkyBox::SkyBox() {
	GLfloat xOrigin = 0.0f;
	GLfloat yOrigin = 0.0f;
	GLfloat zOrigin = 0.0f;

	

	mode = GL_TRIANGLES;
}

void SkyBox::drawModel(int drawMode, Texture* boxTexture, Texture* metalTexture, float shearX, float shearY, Shader* shader, glm::mat4 objectMatrix)
{


	GLfloat size = (0.8 * 75 * 2); // div by 2 because each side
	GLfloat position = size / 2.0f;

	

	boxTexture->Bind();
	cube = Cube(-position, -position, -position, 1, size, size);
	cube.drawModel();
	cube = Cube(-position, -position, -position, size, 0, size);
	cube.drawModel();
	cube = Cube(-position, position, -position, 1, size, size);
	cube.drawModel();
	cube = Cube(-position, -position, position, size, size, 0);
	cube.drawModel();
	cube = Cube(-position, -position, -position, size, size, 0);
	cube.drawModel();
	cube = Cube(position, -position, -position, size, 0, size);
	cube.drawModel();

	boxTexture->Unbind();
}