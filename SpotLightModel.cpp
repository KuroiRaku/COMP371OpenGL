#include "SpotLightModel.h"


SpotLightModel::SpotLightModel(GLfloat centerX, GLfloat centerY, GLfloat centerZ) {
	cube = Cube(centerX - 0.5f, centerY - 0.5f, centerZ, 1.0f, 1.0f, 1.0f);
	cylinder = Cylinder(5.0f, 1.0f, 1.0f);
}
//(float Length, float size, float radius)
void SpotLightModel::drawModel(Shader& shader, glm::mat4 objectMatrix) {
	cube.drawModel();
	cylinder.draw(NULL);
}


