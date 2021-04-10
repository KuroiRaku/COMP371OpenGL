#include "LModel.h"


LModel::LModel() {

	sphereMatrix = glm::rotate(sphereMatrix, glm::radians(90.f), glm::vec3(-1, 0, 0));

}

void LModel::drawLetter(Texture* boxTexture, Shader* shader, glm::mat4 objectMatrix)
{
	boxTexture->Bind();

	bottomSide.drawModel();
	bottom.drawModel();
	side.drawModel();
	side2.drawModel();

	boxTexture->Unbind();
}



