#include "SpotLight.h"
void SpotLight::drawModel(GLfloat centerX, GLfloat centerY, GLfloat centerZ) {
	Cube cube = Cube(centerX - 0.5f, centerY - 0.5f, centerZ, 1.0f, 1.0f, 1.0f);
	cube.drawModel();
	Cylinder cylinder = Cylinder(3.0f, 1.0f, 1.0f);
	cylinder.draw(NULL);
}


SpotLight::SpotLight() {

}



