#include "QuizModelsAlessandro.h"

QuizModelsAlessandro::QuizModelsAlessandro() {
	this->lineSize = 0.4f * 2;
};

void QuizModelsAlessandro::drawLetterI() {

};

void QuizModelsAlessandro::setLetterI(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin) {
	// 3 cubes ontop, 3 cubes on the bottom, 1 elongated sphere
	Cube topLeft = Cube(-1 * lineSize + xOrigin, 1.5 * lineSize + yOrigin, zOrigin);
	Cube topMiddle = Cube(xOrigin, 1.5 * lineSize + yOrigin, zOrigin);
	Cube topRight = Cube(1 * lineSize + xOrigin, 1.5 * lineSize + yOrigin, zOrigin);
	Sphere body = Sphere(xOrigin, yOrigin, zOrigin, 1);
	Cube bottomLeft = Cube(-1 * lineSize + xOrigin, -1.5 * lineSize + yOrigin, zOrigin);
	Cube bottomMiddle = Cube(xOrigin, -1.5 * lineSize + yOrigin, zOrigin);
	Cube bottomRight = Cube(1 * lineSize + xOrigin, -1.5 * lineSize + yOrigin, zOrigin);

	topLeft.drawModel();
	topMiddle.drawModel();
	topRight.drawModel();
	body.draw();
	bottomLeft.drawModel();
	bottomMiddle.drawModel();
	bottomRight.drawModel();
}

void QuizModelsAlessandro::setLetterL(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin) {
	Cube bottomLeft = Cube(-1.0f * lineSize + xOrigin, -1.5f * lineSize + yOrigin, zOrigin);
	Cube bottomMiddle = Cube(xOrigin, -1.5f * lineSize + yOrigin, zOrigin);
	Cube bottomRight = Cube(1.0f * lineSize + xOrigin, -1.5f * lineSize + yOrigin, zOrigin);
	Sphere body = Sphere(xOrigin - 7.0f * lineSize, yOrigin /2, zOrigin, 2.0f);

	bottomLeft.drawModel();
	bottomMiddle.drawModel();
	bottomRight.drawModel();
	body.draw();
}

void QuizModelsAlessandro::setLetterE(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin) {
	Cube topLeft = Cube(-1 * lineSize + xOrigin, 1.5 * lineSize + yOrigin, zOrigin);
	Cube topMiddle = Cube(xOrigin, 1.5 * lineSize + yOrigin, zOrigin);
	Cube topRight = Cube(1 * lineSize + xOrigin, 1.5 * lineSize + yOrigin, zOrigin);
	Cube bottomLeft = Cube(-1.0f * lineSize + xOrigin, -1.5f * lineSize + yOrigin, zOrigin);
	Cube bottomMiddle = Cube(xOrigin, -1.5f * lineSize + yOrigin, zOrigin);
	Cube bottomRight = Cube(1.0f * lineSize + xOrigin, -1.5f * lineSize + yOrigin, zOrigin);
	Cube middleLeft = Cube(-1.0f * lineSize + xOrigin, yOrigin, zOrigin);
	Cube middleMiddle = Cube(xOrigin, yOrigin, zOrigin);
	Sphere body = Sphere(xOrigin - 5, yOrigin, zOrigin, 1);
	topLeft.drawModel();
	topMiddle.drawModel();
	topRight.drawModel();
	body.draw();
	bottomLeft.drawModel();
	bottomMiddle.drawModel();
	bottomRight.drawModel();
	middleLeft.drawModel();
	middleMiddle.drawModel();
}

void QuizModelsAlessandro::setLetterS(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin) {
	Cube topLeft = Cube(-1 * lineSize + xOrigin, 1.5 * lineSize + yOrigin, zOrigin);
	Cube topMiddle = Cube(xOrigin, 1.5 * lineSize + yOrigin, zOrigin);
	Cube topRight = Cube(1 * lineSize + xOrigin, 1.5 * lineSize + yOrigin, zOrigin);
	Cube bottomLeft = Cube(-1.0f * lineSize + xOrigin, -1.5f * lineSize + yOrigin, zOrigin);
	Cube bottomMiddle = Cube(xOrigin, -1.5f * lineSize + yOrigin, zOrigin);
	Cube bottomRight = Cube(1.0f * lineSize + xOrigin, -1.5f * lineSize + yOrigin, zOrigin);
	Cube middleLeft = Cube(-1.0f * lineSize + xOrigin, yOrigin, zOrigin);
	Cube middleMiddle = Cube(xOrigin, yOrigin, zOrigin);
	Cube middleRight = Cube(1.0f * lineSize + xOrigin, yOrigin, zOrigin);


	Sphere topLeftCol = Sphere(xOrigin - 5.0f * lineSize, yOrigin * 1.5 , zOrigin, 0.7);
	topLeftCol.draw();
	Sphere bottomRightCol = Sphere(xOrigin + 5.0f * lineSize, (yOrigin - 1.3)*1.5 , zOrigin, 0.7);
	bottomRightCol.draw();

	topLeft.drawModel();
	topMiddle.drawModel();
	topRight.drawModel();
	bottomLeft.drawModel();
	bottomMiddle.drawModel();
	bottomRight.drawModel();
	middleLeft.drawModel();
	middleMiddle.drawModel();
	middleRight.drawModel();

}

void QuizModelsAlessandro::setLetterR(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin) {
	Cube topLeft = Cube(-1 * lineSize + xOrigin, 1.5 * lineSize + yOrigin, zOrigin);
	Cube topMiddle = Cube(xOrigin, 1.5 * lineSize + yOrigin, zOrigin);
	Cube middleLeft = Cube(-1.0f * lineSize + xOrigin, yOrigin, zOrigin);
	Cube middleMiddle = Cube(xOrigin, yOrigin, zOrigin);
	Cube middleRight = Cube(1.0f * lineSize + xOrigin, yOrigin, zOrigin);

	Sphere leftCol = Sphere(xOrigin - 6.0f, yOrigin - 1.0f, zOrigin, 1.5);
	leftCol.draw();
	Sphere middleCol = Sphere(xOrigin, yOrigin + 5.0f * lineSize, zOrigin, 0.5f);
	middleCol.draw();
	Sphere bottomRightCol = Sphere(xOrigin + 5.0f * lineSize, yOrigin - 0.0f * lineSize, zOrigin, 0.8f);
	bottomRightCol.draw();

	middleLeft.drawModel();
	middleMiddle.drawModel();
	middleRight.drawModel();
	topLeft.drawModel();
	topMiddle.drawModel();
}

void QuizModelsAlessandro::setLetterK(GLfloat xOrigin, GLfloat yOrigin, GLfloat zOrigin) {
	Cube middleLeft = Cube(-1.0f * lineSize + xOrigin, yOrigin, zOrigin);
	Cube middleMiddle = Cube(xOrigin, yOrigin, zOrigin);
	Cube topRight = Cube(1 * lineSize + xOrigin, 1.5 * lineSize + yOrigin, zOrigin);
	Cube bottomRight = Cube(1.0f * lineSize + xOrigin, -1.5f * lineSize + yOrigin, zOrigin);

	Sphere leftCol = Sphere(xOrigin - 7.0f * lineSize, yOrigin, zOrigin, 1.5);
	leftCol.draw();

	Sphere rightCol = Sphere(xOrigin + 3.0f * lineSize, yOrigin, zOrigin, 1.5);
	rightCol.draw();

	middleLeft.drawModel();
	middleMiddle.drawModel();
	bottomRight.drawModel();
	topRight.drawModel();
}
