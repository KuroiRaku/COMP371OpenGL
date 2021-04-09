#include "GroundPlain.h"

// Small hack for the texture here
// Because textures only display correctly here facing the camera
// Going to create it facing the camera and then rotate it

GroundPlain::GroundPlain() {
	
}

void GroundPlain::drawGround(Texture * tileTexture) {
	tileTexture->Bind();

	plane.drawModel();

	tileTexture->Unbind();
}