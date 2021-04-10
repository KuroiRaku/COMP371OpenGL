#include "CModel.h"


CModel::CModel() {
	
}

void CModel::drawModel(Texture * boxTexture, Shader* shader, glm::mat4 objectMatrix)
{

	boxTexture->Bind();
	cube.drawModel();
	cube2.drawModel();
	cube3.drawModel();
	cube4.drawModel();

	side.drawModel();
	side2.drawModel();

	boxTexture->Unbind();

}

