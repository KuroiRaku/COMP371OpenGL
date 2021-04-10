#include "EModel.h"

using namespace std;


EModel::EModel() {

}

void EModel::drawLetter(Texture* boxTexture, Shader* shader, glm::mat4 objectMatrix)
{
	boxTexture->Bind();

	cube.drawModel();
	cube2.drawModel();
	cube3.drawModel();
	cube4.drawModel();
	cube5.drawModel();
	cube6.drawModel();
	
	side.drawModel();
	side2.drawModel();

	boxTexture->Unbind();
}
