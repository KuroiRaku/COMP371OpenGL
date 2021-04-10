#include "SpotLight.h"
void SpotLight::drawModel(GLfloat x, GLfloat y, GLfloat z) {
	Cylinder cylinder = Cylinder(3.0f, 1.0f, 1.0f);
	cylinder.draw(NULL);
	Cube cube = Cube(x - 0.5f, y - 0.5f, z, 1.0f, 1.0f, 1.0f);
	cube.drawModel();
	
}


SpotLight::SpotLight() {

}



