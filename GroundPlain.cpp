#include "GroundPlain.h"


// Small hack for the texture here
// Because textures only display correctly here facing the camera
// Going to create it facing the camera and then rotate it

GroundPlain::GroundPlain() {
	groundMatrix = ground.cubeMatrix;
}

void GroundPlain::drawGround(Texture * tileTexture) {
	tileTexture->Bind();

	ground.drawModel();

	tileTexture->Unbind();
}