//example skeleton code 2021 winter comp371
//modified from http://learnopengl.com/

#include <glad/glad.h>	// include GL Extension Wrangler
#include <glfw/glfw3.h>	// include GLFW helper library

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <time.h>;
#include <vector>

#include "ObjLoaderIndex.h"
#include "Shader.h"
#include "GLDebugMessageCallback.h"
#include "../lines3d.h"
#include "../grid.h"
#include "../GroundPlain.h"
#include "../CModel.h"
#include "../LModel.h"
#include "../Laginho.h"
#include "../DannModel.h"
#include "../Stage.h"
#include "../Screen.h"
#include "../Texture.h"
#include "../Cylinder.h"
#include "../EModel.h"
#include "../SkyBox.h"
#include "../SpotLightModel.h"

using namespace std;

#pragma region Initialization

// Window dimensions
const GLuint WIDTH = 1024, HEIGHT = 768;

void renderScene(Shader& shader, GroundPlain& ground, LModel& lModel, EModel& eModel, EModel& eModel2, LModel lModel2, EModel eModel3, CModel& cModel, Stage& stage, Screen& screen, SkyBox skyBox, Texture* arrayOfTexture, Texture* boxTexture, Texture* metalTexture, Texture* stage_texture, Texture* tileTexture, Texture* skyboxTexture);

glm::mat4 model_matrix;
glm::mat4 view_matrix;
glm::mat4 proj_matrix;

std::vector<int> indices;
std::vector<glm::vec3> vertices;
std::vector<glm::vec3> normals;
std::vector<glm::vec2> UVs;



GLuint vm_loc ;
GLuint pm_loc ;
GLuint mm_loc;
GLuint flag_id ;
GLuint lights_id ;
GLuint spotlight_id;
GLuint spotlight2_id;
GLuint spotlight3_id;
GLuint normalcol_id ;
GLuint greyscale_id ;
GLuint red_id ;
GLuint green_id ;
GLuint blue_id ;
GLuint colour_id ;

double camRotation = 0;
const float radius = 30.0f;

float shearX = 0.f;
float shearY = 0.f;

//model settings
glm::mat4 model_active = glm::rotate(glm::mat4(1.0f), glm::radians(0.f), glm::vec3(0, 1, 0)); //active model
glm::vec3 model_active_move = glm::vec3(0, 15, 25); //to apply translational transformations

glm::mat4 model_general = glm::mat4(1.0f); //active model
glm::vec3 model_general_move = glm::vec3(0, 2, -10); //to apply translational transformations

//Alessandro
glm::mat4 model_L = glm::mat4(1.0f);//Model of letter A
glm::vec3 model_L_move = glm::vec3(0, 15, 25); //to apply translational transformations
//Le Cherng
glm::mat4 model_E = glm::mat4(1.0f);//Model of letter U
glm::vec3 model_E_move = glm::vec3(0, 12, 25); //to apply translational transformations
//Dan
glm::mat4 model_E2 = glm::mat4(1.0f);//Model of letter K
glm::vec3 model_E2_move = glm::vec3(0, 9, 25); //to apply translational transformations
//LaginHo
glm::mat4 model_L2 = glm::mat4(1.0f);//Model of letter O
glm::vec3 model_L2_move = glm::vec3(0, 6, 25); //to apply translational transformations

glm::mat4 model_E3 = glm::mat4(1.0f);////Model of first letter S
glm::vec3 model_E3_move = glm::vec3(0, 3, 25); //to apply translational transformations

glm::mat4 model_C = glm::mat4(1.0f);///Model of second letter S
glm::vec3 model_C_move = glm::vec3(0, 0, 25); //to apply translational transformations

//LaginHo
glm::mat4 model_grid = glm::mat4(1.0f);
glm::vec3 model_grid_move = glm::vec3(0, 0, 0); //to apply translational transformations

glm::mat4 model_Sky = glm::mat4(1.0f);//Model of letter O
glm::vec3 model_Sky_move = glm::vec3(0, 0, 0); //to apply translational transformations


//World Matrix
glm::mat4 model_world = glm::mat4(1.0f);
glm::vec3 model_world_move = glm::vec3(0, 0, 0); //to apply translational transformations

glm::mat4 model_Stage = glm::rotate(glm::mat4(1.0f), glm::radians(0.f), glm::vec3(0, 1, 0)); //active model
glm::vec3 model_Stage_move = glm::vec3(-10, 0, -25); //to apply translational transformations

glm::mat4 model_Screen = glm::rotate(glm::mat4(1.0f), glm::radians(0.f), glm::vec3(0, 1, 0)); //active model
glm::vec3 model_Screen_move = glm::vec3(-10, 0, -25); //to apply translational transformations

glm::mat4 model_Light = glm::rotate(glm::mat4(1.0f), glm::radians(180.f), glm::vec3(0, 1, 0));///Model of projector

glm::vec3 model_Light_move = glm::vec3(0, 40, 30); //to apply translational transformations


glm::mat4 model_L_matrix ;

glm::mat4 model_Sky_matrix;
//Le Cherng
glm::mat4 model_E_matrix ;
//Dan
glm::mat4 model_E2_matrix ;
//LaginHo
glm::mat4 model_L2_matrix ;
glm::mat4 model_Stage_matrix ;
glm::mat4 model_Screen_matrix;
glm::mat4 grid_matrix ;
glm::mat4 ground_matrix ;
glm::mat4 line_matrix;

glm::mat4 model_E3_matrix;

glm::mat4 model_C_matrix;

glm::mat4 model_Light_matrix;

Texture arrayOfTexture[14];

int currentIndex = 0;
// Game loop
int n = 10;
int milli_seconds = n * 1000;
time_t start, end;

GLuint vm_loc_lines_3d;
GLuint pm_loc_lines_3d;
GLuint mm_loc_lines_3d;

//color settings
bool flag = true;//false;
bool lights = true;// true;
bool spotlight = false;
bool spotlight2 = false;
bool spotlight3 = false;
bool normalcol = false;
bool greyscale = false;
bool red = false;
bool green = false;
bool blue = false;
bool colour = false;
bool activeModelTexture = true;
bool shadow = true;

//0 for points, 1 for lines, 2 for triangle
int renderingMode = 2;
//0 for alessandro, 1 for laginho, 2 for Dann, 3 for Le Cherng
int activeModel = 0;
int previousActiveModel = 0;
int initModel = activeModel;
int currentCam=0;

//camera settings
// fps
glm::vec3 cam_pos = glm::vec3(0, 2, 30);
glm::vec3 cam_dir = glm::vec3(0, 0, -1); //direction means what the camera is looking at
glm::vec3 temp_cam_dir = glm::vec3(0, 0, 1); //use this for the cross product or else when cam_dir and cam_up overlap, the cross product will be 0 (bad!)
glm::vec3 cam_up = glm::vec3(0, 1, 0); //up defines where the top of the camera is directing towards

// model back
glm::vec3 cam_pos_back = glm::vec3(0.5, 3, 45);
glm::vec3 cam_dir_back = glm::vec3(0, 0, -1);
glm::vec3 cam_up_back = glm::vec3(0, 1, 0);

// model front 
glm::vec3 cam_pos_front = glm::vec3(0.5, 3, 23);
glm::vec3 cam_dir_front = glm::vec3(0, 0, -1);
glm::vec3 cam_up_front = glm::vec3(0, 1, 0);

// Extra camera??? 
glm::vec3 cam_pos_light = glm::vec3(0, 40, -10);
glm::vec3 cam_dir_light = glm::vec3(0, 0, 0);
glm::vec3 cam_up_light = glm::vec3(0, 1, 0);

float camX;
float camZ;
// lighting settings

// Point Light //ambient light
glm::vec3 lightColor = glm::vec3(1.0, 0.5, 1.0);
glm::vec3 lightPosition = glm::vec3(1.2f, 5.0f, 2.0f);
glm::vec3 lightFocus = glm::vec3(0.0, 0.0, 0.0);
glm::vec3 lightDirection = glm::normalize(lightFocus - lightPosition);

// Spotlight
// key 7 
glm::vec3 spotlightColor = glm::vec3(1.0, 1.0, 1.0);
glm::vec3 spotlightPosition = glm::vec3(0, 20, -5);
glm::vec3 spotlightFocus = glm::vec3(0, 0, 23);
glm::vec3 spotlightDirection = glm::normalize(spotlightFocus - spotlightPosition);

// Rotating
glm::vec3 spotlightColor2 = glm::vec3(0.0, 1.0, 0.0);
glm::vec3 spotlightPosition2 = model_Light_move;
glm::vec3 spotlightFocus2 = glm::vec3(0.0, 0.0, 0.0);
glm::vec3 spotlightDirection2 = glm::normalize(spotlightFocus2 - spotlightPosition2);

// Ceiling key S
glm::vec3 spotlightColor3 = glm::vec3(1.0, 0.2, 0.6);
glm::vec3 spotlightPosition3 = glm::vec3(0, 40, 10);
glm::vec3 spotlightFocus3 = glm::vec3(0, 0, -15);
glm::vec3 spotlightDirection3 = glm::normalize(spotlightFocus3 - spotlightPosition3);

// Ceiling
glm::vec3 spotlightColor4 = glm::vec3(1.0, 0.2, 0.6);
glm::vec3 spotlightPosition4 = glm::vec3(0, 40, 0);
glm::vec3 spotlightFocus4 = glm::vec3(0, 0, -15);
glm::vec3 spotlightDirection4 = glm::normalize(spotlightFocus3 - spotlightPosition3);

glm::vec3 generalLightDirection = lightDirection;
glm::vec3 generalLightPosition = lightPosition;
glm::vec3 generalLightFocus = lightFocus;

float spotlightCutoff = glm::cos(glm::radians(2.5f));
float spotlightOuterCutoff = glm::cos(glm::radians(12.0f));
float spotlightConstant = 1.0f;
float spotlightLinear = 0.09;
float spotlightQuadratic = 0.032;

float lightNearPlane = 2.0f;
float lightFarPlane = 20.0f;

//glm::vec3 object_color = glm::vec3(0.5, 0.5, 0.5);

#pragma endregion Initialization

void resetToPreviousModel(int previousActiveModel) {
	switch (previousActiveModel)
	{
	case 0:
		model_active = model_L;
		model_active_move = model_L_move;
		break;
	case 1:
		model_active = model_L2;
		model_active_move = model_L2_move;
		break;
	case 2:
		model_active = model_E2;
		model_active_move = model_E2_move;
		break;
	case 3:
		model_active = model_E;
		model_active_move = model_E_move;
		break;
	case 4:
		model_active = model_E3;
		model_active_move = model_E3_move;
		break;

	case 5:
		model_active = model_C;
		model_active_move = model_C_move;
		break;
	}
	activeModel = previousActiveModel;
}

// Rotate around a point
// Note: This function is not in used, because assignment doesn't require it. But we will still keep it if we want to play around :D
void rotateAround(glm::vec3& moveVec, glm::mat4& matrix, glm::vec3 rotation) {
	activeModel = 4;

	glm::mat4 identityMatrix(1.f);
	identityMatrix = glm::translate(identityMatrix, glm::vec3(-moveVec.x, -moveVec.y, -moveVec.z));
	identityMatrix = glm::rotate(identityMatrix, 0.05f, rotation);
	identityMatrix = glm::translate(identityMatrix, glm::vec3(moveVec.x, moveVec.y, moveVec.z));
	identityMatrix *= matrix;
	matrix = identityMatrix;
}

#pragma region KeyCallback

bool leftShiftPressed = false;
bool worldOrientationKeyPressed = false;

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mod)
{
	std::cout << key << std::endl;	//outputs the key value

	//if you press the Esc key, the window will close
	if (key == GLFW_KEY_ESCAPE) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) {
		leftShiftPressed = true;
	}
	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE) {
		leftShiftPressed = false;
	}

	if ((key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT || key == GLFW_KEY_UP || key == GLFW_KEY_DOWN) && action == GLFW_PRESS) {
		activeModel = 4;
		worldOrientationKeyPressed = true;
	}

	if ((key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT || key == GLFW_KEY_UP || key == GLFW_KEY_DOWN) && action == GLFW_RELEASE) {
		worldOrientationKeyPressed = false;
		resetToPreviousModel(previousActiveModel);
	}

	//TGFH buttons to move the camera
	if (!leftShiftPressed) {
		if (key == GLFW_KEY_T) { //W moves forward
			cam_pos += cam_dir;
		}

		if (key == GLFW_KEY_G) { //S moves backwards
			cam_pos -= cam_dir;
		}

		if (key == GLFW_KEY_H) { //D moves right
			cam_pos -= glm::cross(cam_up, cam_dir);
		}

		if (key == GLFW_KEY_F) { //A moves left
			cam_pos += glm::cross(cam_up, cam_dir);
		}
		if (worldOrientationKeyPressed)
		{
			//Left and Right key rotate camera
			if (key == GLFW_KEY_RIGHT) { //left arrow rotates the camera left about the right vector
				camRotation += 0.05;
				camX = sin(camRotation) * radius;
				camZ = cos(camRotation) * radius;
			}
			if (key == GLFW_KEY_DOWN) { //left arrow rotates the camera left about the down vector
				model_world = glm::rotate(model_world, glm::radians(5.f), glm::vec3(-1, 0, 0));
			}
			if (key == GLFW_KEY_UP) { //left arrow rotates the camera left about the up vector
				model_world = glm::rotate(model_world, glm::radians(5.f), glm::vec3(1, 0, 0));
			}
			if (key == GLFW_KEY_LEFT) { //left arrow rotates the camera left about the left vector
				camRotation -= 0.05;
				camX = sin(camRotation) * radius;
				camZ = cos(camRotation) * radius;
			}
		}
	}



	//reset to initial position
	if (key == GLFW_KEY_HOME)
	{
		model_world = glm::mat4(1.f);
	}

	//full reset
	if (key == GLFW_KEY_0)
	{
		model_active = glm::mat4(1.0f);
		model_active_move = glm::vec3(0, 2, -10); //to apply translational transformations

		//Alessandro
		model_L = glm::mat4(1.0f);
		model_L_move = glm::vec3(0, 2, -10); //to apply translational transformations
		//Le Cherng
		model_E = glm::mat4(1.0f);
		model_E_move = glm::vec3(0, 2, 10); //to apply translational transformations
		   //Dan
		model_E2 = glm::mat4(1.0f);
		model_E2_move = glm::vec3(10, 2, 0); //to apply translational transformations
	   //LaginHo
		model_L2 = glm::mat4(1.0f);
		model_L2_move = glm::vec3(-10, 2, 0); //to apply translational transformations
		  //LaginHo
		model_grid = glm::mat4(1.0f);
		model_grid_move = glm::vec3(0, 0, 0); //to apply translational transformations

		model_world = glm::mat4(1.f);

		shearX = 0;
		shearY = 0;
	}

	if (key == GLFW_KEY_SPACE)
	{
		int randomXPosition = -15 + (std::rand() % (15 + 15 + 1));
		int randomZPosition = -15 + (std::rand() % (15 + 15 + 1));
		model_active = glm::mat4(1.0f);
		model_active_move = glm::vec3(randomXPosition, 2, randomZPosition); //to apply translational transformations

		//Alessandro
		randomXPosition = -15 + (std::rand() % (15 + 15 + 1));
		randomZPosition = -15 + (std::rand() % (15 + 15 + 1));
		model_L = glm::mat4(1.0f);
		model_L_move = glm::vec3(randomXPosition, 2, randomZPosition); //to apply translational transformations

		//Le Cherng
		randomXPosition = -15 + (std::rand() % (15 + 15 + 1));
		randomZPosition = -15 + (std::rand() % (15 + 15 + 1));
		model_E = glm::mat4(1.0f);
		model_E_move = glm::vec3(randomXPosition, 2, randomZPosition); //to apply translational transformations

		//Dan
		randomXPosition = -15 + (std::rand() % (15 + 15 + 1));
		randomZPosition = -15 + (std::rand() % (15 + 15 + 1));
		model_E2 = glm::mat4(1.0f);
		model_E2_move = glm::vec3(randomXPosition, 2, randomZPosition); //to apply translational transformations

	   //LaginHo
		randomXPosition = -15 + (std::rand() % (15 + 15 + 1));
		randomZPosition = -15 + (std::rand() % (15 + 15 + 1));
		model_L2 = glm::mat4(1.0f);
		model_L2_move = glm::vec3(randomXPosition, 2, randomZPosition); //to apply translational transformations

	}

	if (!worldOrientationKeyPressed) {

		//BNE buttons to rotate the model
		if (leftShiftPressed) {
			if (key == GLFW_KEY_W) { //W rotates the object about the +X axis
				model_active = glm::rotate(model_active, glm::radians(5.f), glm::vec3(1, 0, 0));
			}
			if (key == GLFW_KEY_S) { //S rotates the object about the -X axis
				model_active = glm::rotate(model_active, glm::radians(5.f), glm::vec3(-1, 0, 0));
			}
			if (key == GLFW_KEY_A) { //N rotates the object about the Y axis,
				model_active = glm::rotate(model_active, glm::radians(5.f), glm::vec3(0, 1, 0));
			}
			if (key == GLFW_KEY_D) { //N rotates the object about the -Y axis,
				model_active = glm::rotate(model_active, glm::radians(5.f), glm::vec3(0, -1, 0));
			}
			if (key == GLFW_KEY_E) { //rotates the object about the Z axis
				model_active = glm::rotate(model_active, glm::radians(5.f), glm::vec3(0, 0, 1));
			}
			if (key == GLFW_KEY_Q) { //rotates the object about the -Z axis
				model_active = glm::rotate(model_active, glm::radians(5.f), glm::vec3(0, 0, -1));
			}

			// For moving the models?
			if (key == GLFW_KEY_T) { //I moves the object along the +Y axis
				shearY += 0.1;
			}

			if (key == GLFW_KEY_G) { //K moves the object along the -Y
				shearY -= 0.1;
			}

			if (key == GLFW_KEY_F) { //J moves the object along the +X axis
				shearX -= 0.1;
			}

			if (key == GLFW_KEY_H) { //L moves the object along the -X axis
				shearX += 0.1;
			}

			// For rotating the models
			if (key == GLFW_KEY_UP) { //W rotates the object about the +X axis
				model_active = glm::rotate(model_active, glm::radians(5.f), glm::vec3(1, 0, 0));
				model_L = glm::rotate(model_L, glm::radians(5.f), glm::vec3(1, 0, 0));
				model_E2 = glm::rotate(model_E2, glm::radians(5.f), glm::vec3(1, 0, 0));
				model_L2 = glm::rotate(model_L2, glm::radians(5.f), glm::vec3(1, 0, 0));
				model_E = glm::rotate(model_E, glm::radians(5.f), glm::vec3(1, 0, 0));
			}
			if (key == GLFW_KEY_DOWN) { //S rotates the object about the -X axis
				model_active = glm::rotate(model_active, glm::radians(5.f), glm::vec3(-1, 0, 0));
				model_L = glm::rotate(model_L, glm::radians(5.f), glm::vec3(-1, 0, 0));
				model_E2 = glm::rotate(model_E2, glm::radians(5.f), glm::vec3(-1, 0, 0));
				model_L2 = glm::rotate(model_L2, glm::radians(5.f), glm::vec3(-1, 0, 0));
				model_E = glm::rotate(model_E, glm::radians(5.f), glm::vec3(-1, 0, 0));
			}
			if (key == GLFW_KEY_LEFT) { //N rotates the object about the Y axis,
				model_active = glm::rotate(model_active, glm::radians(5.f), glm::vec3(0, 1, 0));
				model_L = glm::rotate(model_L, glm::radians(5.f), glm::vec3(0, 1, 0));
				model_E2 = glm::rotate(model_E2, glm::radians(5.f), glm::vec3(0, 1, 0));
				model_L2 = glm::rotate(model_L2, glm::radians(5.f), glm::vec3(0, 1, 0));
				model_E = glm::rotate(model_E, glm::radians(5.f), glm::vec3(0, 1, 0));
			}
			if (key == GLFW_KEY_RIGHT) { //N rotates the object about the -Y axis,
				model_active = glm::rotate(model_active, glm::radians(5.f), glm::vec3(0, -1, 0));
				model_L = glm::rotate(model_L, glm::radians(5.f), glm::vec3(0, -1, 0));
				model_E2 = glm::rotate(model_E2, glm::radians(5.f), glm::vec3(0, -1, 0));
				model_L2 = glm::rotate(model_L2, glm::radians(5.f), glm::vec3(0, -1, 0));
				model_E = glm::rotate(model_E, glm::radians(5.f), glm::vec3(0, -1, 0));
			}
		}

		//OP buttons to scale up and down
		if (key == GLFW_KEY_U) { //O scales up the object by a factor of 10%
			model_active = glm::scale(model_active, glm::vec3(1.1f));
		}
		if (key == GLFW_KEY_J) { //P scales up the object by a factor of -10%
			model_active = glm::scale(model_active, glm::vec3(0.9f));
		}

		//toggle the red channel on/off
		if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
			if (red != true) {
				red = true;
			}
			else
			{
				red = false;
			}
			activeModel = 0;
			previousActiveModel = 1;
			model_active = model_L;
			model_active_move = model_L_move;
		}

		//toggle the green channel on/off
		if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
			if (green != true)
			{
				green = true;
			}
			else
			{
				green = false;
			}
			activeModel = 1;
			previousActiveModel = 1;
			model_active = model_L2;
			model_active_move = model_L2_move;
		}

		//toggle the blue channel on/off
		if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
			if (blue != true) {
				blue = true;
			}
			else {
				blue = false;
			}
			activeModel = 2;
			previousActiveModel = 2;
			model_active = model_E2;
			model_active_move = model_E2_move;
		}

		//turn on all channels
		if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
			if (colour != true) {
				colour = true;

				red = false;
				green = false;
				blue = false;
				colour = false;
			}
			else
				colour = false;

			activeModel = 3;
			previousActiveModel = 3;
			model_active = model_E;
			model_active_move = model_E_move;
		}

		//toggle between Gouraud and Phong shading
		if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
			if (flag == false) {
				flag = true;
			}
			else {
				flag = false;
			}
		}

		if (key == GLFW_KEY_6 && action == GLFW_PRESS) {
				lights = true;
				flag = true;
				spotlight = false;
				spotlight2 = false;
				spotlight3 = false;
				generalLightDirection = lightDirection;
				generalLightPosition = lightPosition;
				generalLightFocus = lightFocus;
		}

		if (key == GLFW_KEY_7 && action == GLFW_PRESS) {
			spotlight = true;
			spotlight2 = false;
			spotlight3 = false;
			lights = false; 
			generalLightDirection = spotlightDirection;
			generalLightPosition = spotlightPosition;
			generalLightFocus = spotlightFocus;
		}

		if (key == GLFW_KEY_K && action == GLFW_PRESS) {
			spotlight2 = false;
			lights = false;
			spotlight = false;
			spotlight3 = true;
			generalLightDirection = spotlightDirection3;
			generalLightPosition = spotlightPosition3;
			generalLightFocus = spotlightFocus3;
		}
		if (key == GLFW_KEY_S && action == GLFW_PRESS) {
			lights = false; 
			spotlight3 = false;
			spotlight = false;
			if (spotlight2 == true) {
				spotlight2 = false;
				generalLightDirection = lightDirection;
				generalLightPosition = lightPosition;
				generalLightFocus = lightFocus;
			}
			else
			{
				spotlight2 = true;
				generalLightDirection = spotlightDirection2;
				generalLightPosition = spotlightPosition2;
				generalLightFocus = spotlightFocus2;
			}
		}
			
			

		if (key == GLFW_KEY_8 && action == GLFW_PRESS) {
			if (normalcol == false)
				normalcol = true;
			else
				normalcol = false;
		}

		if (key == GLFW_KEY_X && action == GLFW_PRESS) {
			activeModelTexture = !activeModelTexture;
		}

		/*if (key == GLFW_KEY_G && action == GLFW_PRESS) {
			if (greyscale == false)
				greyscale = true;
			else
				greyscale = false;
		}*/
	}

	//rendering mode
	if (key == GLFW_KEY_P && action == GLFW_PRESS) {
		renderingMode = 0;
	}

	if (key == GLFW_KEY_L && action == GLFW_PRESS) {
		renderingMode = 1;
	}

	if (key == GLFW_KEY_T && action == GLFW_PRESS) {
		renderingMode = 2;
	}

	// Camera
	// Infront
	if (key == GLFW_KEY_M && action == GLFW_PRESS) {
		if (currentCam == 1) {
			currentCam = 0;
		}
		else {
			currentCam = 1;
		}
	}
	// Back
	if (key == GLFW_KEY_B && action == GLFW_PRESS) {
		if (currentCam == 2) {
			currentCam = 0;
		}
		else {
			currentCam = 2;
		}
	}
	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		currentCam = 0;
	}

	// Rotating cam
	if (key == GLFW_KEY_N && action == GLFW_PRESS) {
		//Rotation cam
		if (currentCam == 4) {
			currentCam = 0;
		}
		else {
			currentCam = 4;
		}
	}

	if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
		//Rotation cam
		if (shadow) {
			std::cout << "test" << std::endl;
			shadow = false;
		}
		else {
			shadow = true;
		}
	}

	
}

double last_y_pos = 0;
double last_x_pos = 0;
bool lbutton_pressed = true;
bool r_button_pressed = true;
bool m_button_pressed = true;

//LEFT mouse button + drag up and down, moves the camera further and closer to the object
void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		lbutton_pressed = true;
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		lbutton_pressed = false;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		r_button_pressed = true;
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
		r_button_pressed = false;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
		m_button_pressed = true;
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE) {
		m_button_pressed = false;
	}

	//moving forward / backward while left button is pressed
	if (lbutton_pressed) {
		if (last_y_pos - ypos > 0) { //mouse going up, camera moves backward
			cam_pos -= cam_dir;
			last_y_pos = ypos;
		}

		if (last_y_pos - ypos < 0) { //mouse going down, camera moves forward
			cam_pos += cam_dir;
			last_y_pos = ypos;
		}
	}

	if (r_button_pressed) {
		if (last_x_pos - xpos > 0) { //mouse going up, camera moves backward
			cam_dir = glm::mat3(glm::rotate(glm::radians(0.5f), cam_up)) * cam_dir;
			last_x_pos = xpos;
		}

		if (last_x_pos - xpos < 0) { //mouse going down, camera moves forward
			cam_dir = glm::mat3(glm::rotate(glm::radians(0.5f), -cam_up)) * cam_dir;
			last_x_pos = xpos;
		}
	}

	if (m_button_pressed) {
		glm::mat4 rotation_matrix(1);
		glm::vec3 rotate_around_x = glm::cross(cam_up, cam_dir); //cross product
		if (last_y_pos - ypos > 0) { //mouse going up, camera moves backward
			rotation_matrix = glm::rotate(rotation_matrix, -(0.01f), rotate_around_x);
			cam_dir = glm::mat3(rotation_matrix) * cam_dir;
			cam_up = glm::mat3(rotation_matrix) * cam_up;
			last_y_pos = ypos;
		}

		if (last_y_pos - ypos < 0) { //mouse going down, camera moves forward
			glm::mat4 rotation_matrix(1);
			rotation_matrix = glm::rotate(rotation_matrix, (0.01f), rotate_around_x);
			cam_dir = glm::mat3(rotation_matrix) * cam_dir;
			cam_up = glm::mat3(rotation_matrix) * cam_up;
			last_y_pos = ypos;
		}
	}
}

#pragma endregion KeyCallback

// The MAIN function, from here we start the application and run the game loop
int main()
{
	std::cout << "Starting GLFW context" << std::endl;
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// OpenGL state
	// ------------
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glPointSize(10.0);


	//Hidden surface removal
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);


	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	//glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);


	// Build and compile our shader program
	Shader shader("resources/shaders/vertex.shader", "resources/shaders/fragment.shader");
	Shader shaderShadow("resources/shaders/shadow_vertex.shader", "resources/shaders/shadow_fragment.shader");

	//lines
	Shader lines3dShader("resources/shaders/lines3d_vertex.shader", "resources/shaders/lines3d_fragment.shader");


	loadOBJ("resources/objects/cube.obj", indices, vertices, normals, UVs);

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO); //if you take this off nothing will show up because you haven't linked the VAO to the VBO
							//you have to bind before putting the point

	GLuint vertices_VBO;
	glGenBuffers(1, &vertices_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);
	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);  //3*sizeof(GLfloat) is the offset of 3 float numbers
	//glEnableVertexAttribArray(0);

	GLuint normals_VBO;
	glGenBuffers(1, &normals_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, normals_VBO);
	//glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals.front(), GL_STATIC_DRAW);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);  //3*sizeof(GLfloat) is the offset of 3 float numbers
	//glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices.front(), GL_STATIC_DRAW);

	// Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
	glBindVertexArray(0);


	//shader set up
	shader.Bind();
	model_matrix = glm::translate(glm::mat4(1.f), glm::vec3(3, 2, 0));
	view_matrix = glm::lookAt(cam_pos, cam_dir, cam_up);
	proj_matrix = glm::perspective(glm::radians(45.f), 1.f, 0.1f, 200.f); //perspective view. Third parameter should be > 0, or else errors

	//other model matrix
	model_Light = glm::rotate(glm::mat4(1.0f), glm::radians(30.f), glm::vec3(-1, 0, 0));

	//Alessandro
	model_L_matrix = glm::translate(glm::mat4(1.f), model_L_move);
	//Le Cherng
	model_E_matrix = glm::translate(glm::mat4(1.f), model_E_move);
	//Dan
	model_E2_matrix = glm::translate(glm::mat4(1.f), model_E2_move);
	//LaginHo
	model_L2_matrix = glm::translate(glm::mat4(1.f), model_L2_move);

	model_E3_matrix = glm::translate(glm::mat4(1.f), model_E3_move);

	model_C_matrix = glm::translate(glm::mat4(1.f), model_C_move);

	model_Stage_matrix = glm::translate(glm::mat4(1.f), model_Stage_move);

	model_Screen_matrix = glm::translate(glm::mat4(1.f), model_Screen_move);

	model_Sky_matrix = glm::translate(glm::mat4(1.f), model_Sky_move);

	model_Light_matrix = glm::translate(model_Light, model_Light_move);

	grid_matrix = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0));
    ground_matrix = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0));
	line_matrix = glm::translate(glm::mat4(1.f), glm::vec3(0, 1, 0));

	 vm_loc = shader.GetUniformLocation("vm");
	 pm_loc = shader.GetUniformLocation("pm");
     mm_loc = shader.GetUniformLocation("mm");
     flag_id = shader.GetUniformLocation("flag");
     lights_id = shader.GetUniformLocation("lights");
	 spotlight_id = shader.GetUniformLocation("spotlight_on");
	 spotlight2_id = shader.GetUniformLocation("spotlight_on2");
	 spotlight3_id = shader.GetUniformLocation("spotlight_on3");
	 normalcol_id = shader.GetUniformLocation("normalcol");
	 greyscale_id = shader.GetUniformLocation("greyscale");
	 red_id = shader.GetUniformLocation("red");
	 green_id = shader.GetUniformLocation("green");
     blue_id = shader.GetUniformLocation("blue");
	 colour_id = shader.GetUniformLocation("colour");

	//glUniformMatrix4fv(vm_loc, 1, GL_FALSE, &view_matrix[0][0]); OR
	glUniformMatrix4fv(vm_loc, 1, GL_FALSE, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(pm_loc, 1, GL_FALSE, glm::value_ptr(proj_matrix));
	glUniformMatrix4fv(mm_loc, 1, GL_FALSE, glm::value_ptr(model_matrix));

	// point light
	glUniform3fv(shader.GetUniformLocation("light_color"), 1, glm::value_ptr(lightColor));
	glUniform3fv(shader.GetUniformLocation("light_position"), 1, glm::value_ptr(lightPosition));

	// Spotlight.
	glUniform3fv(shader.GetUniformLocation("spotlight_color"), 1, glm::value_ptr(spotlightColor));
	glUniform3fv(shader.GetUniformLocation("spotlight_position"), 1, glm::value_ptr(spotlightPosition));
	glUniform3fv(shader.GetUniformLocation("spotlight_direction"), 1, glm::value_ptr(spotlightDirection));
	glUniform1f(shader.GetUniformLocation("spotlight_cutoff"), spotlightCutoff);
	glUniform1f(shader.GetUniformLocation("spotlight_outer_cutoff"), spotlightOuterCutoff);
	glUniform1f(shader.GetUniformLocation("spotlight_constant"), spotlightConstant);
	glUniform1f(shader.GetUniformLocation("spotlight_linear"), spotlightLinear);
	glUniform1f(shader.GetUniformLocation("spotlight_quadratic"), spotlightQuadratic);

	glUniform3fv(shader.GetUniformLocation("spotlight_color2"), 1, glm::value_ptr(spotlightColor2));
	glUniform3fv(shader.GetUniformLocation("spotlight_position2"), 1, glm::value_ptr(spotlightPosition2));
	glUniform3fv(shader.GetUniformLocation("spotlight_direction2"), 1, glm::value_ptr(spotlightDirection2));
	glUniform1f(shader.GetUniformLocation("spotlight_cutoff2"), spotlightCutoff);
	glUniform1f(shader.GetUniformLocation("spotlight_outer_cutoff2"), spotlightOuterCutoff);
	glUniform1f(shader.GetUniformLocation("spotlight_constant2"), spotlightConstant);
	glUniform1f(shader.GetUniformLocation("spotlight_linear2"), spotlightLinear);
	glUniform1f(shader.GetUniformLocation("spotlight_quadratic2"), spotlightQuadratic);

	glUniform3fv(shader.GetUniformLocation("spotlight_color3"), 1, glm::value_ptr(spotlightColor3));
	glUniform3fv(shader.GetUniformLocation("spotlight_position3"), 1, glm::value_ptr(spotlightPosition3));
	glUniform3fv(shader.GetUniformLocation("spotlight_direction3"), 1, glm::value_ptr(spotlightDirection3));


	glUniform3fv(shader.GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
	glUniform3fv(shader.GetUniformLocation("view_position"), 1, glm::value_ptr(glm::vec3(cam_pos)));
	// 3D Lines Shader camera projection setup
	lines3dShader.Bind();
	 vm_loc_lines_3d = lines3dShader.GetUniformLocation("vm");
	 pm_loc_lines_3d = lines3dShader.GetUniformLocation("pm");
	 mm_loc_lines_3d = lines3dShader.GetUniformLocation("mm");
	glUniformMatrix4fv(vm_loc_lines_3d, 1, GL_FALSE, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(pm_loc_lines_3d, 1, GL_FALSE, glm::value_ptr(proj_matrix));
	glUniformMatrix4fv(mm_loc_lines_3d, 1, GL_FALSE, glm::value_ptr(line_matrix));

	Texture boxTexture("resources/textures/boxtexture.jpg", false);
	Texture metalTexture("resources/textures/metaltexture.jpg", false);
	Texture evilDann("resources/textures/evilDann.png", false);
	Texture dio("resources/textures/dio.jpg", false);
	Texture texture_AL_1("resources/textures/allesandro1.jpg", false);
	Texture texture_AL_2("resources/textures/allesandro2.jpg", false);
	Texture texture_LA_1("resources/textures/laginho1.jpg", false);
	Texture texture_LA_2("resources/textures/laginho2.jpg", false);
	Texture bonus1("resources/textures/bonusTexture1.jpg", false);
	Texture bonus2("resources/textures/bonusTexture2.jpg", false);
	Texture tileTexture("resources/textures/tiletexture.jpg", false);
	Texture modelAllesandroTexture("resources/textures/ModelAllesandro.png", true);
	Texture modelDanielTexture("resources/textures/ModelDaniel.png", true);
	Texture modelLaginhoTexture("resources/textures/ModelLaginho.png", true);
	Texture modelLeCherngTexture("resources/textures/ModelLeCherng.png", true);
	Texture stage_texture("resources/textures/stage_texture.jpg", true);
	Texture skyboxTexture("resources/textures/boxtexture.jpg", false);

	arrayOfTexture[0] = modelAllesandroTexture;
	arrayOfTexture[1] = modelDanielTexture;
	arrayOfTexture[2] = modelLaginhoTexture;
	arrayOfTexture[3] = modelLeCherngTexture;
	arrayOfTexture[4] = boxTexture;
	arrayOfTexture[5] = metalTexture;
	arrayOfTexture[6] = evilDann;
	arrayOfTexture[7] = dio;
	arrayOfTexture[8] = texture_AL_1;
	arrayOfTexture[9] = texture_AL_2;
	arrayOfTexture[10] = texture_LA_1;
	arrayOfTexture[11] = texture_LA_2;
	arrayOfTexture[12] = bonus1;
	arrayOfTexture[13] = bonus2;


	// Configure depth map FBO
	// Variable storing index to texture used for shadow mapping
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	GLuint depth_map_texture;
	// Get the texture
	glGenTextures(1, &depth_map_texture);
	// Bind the texture so the next glTex calls affect it
	glBindTexture(GL_TEXTURE_2D, depth_map_texture);
	// Create the texture and specify it's attributes, including widthn height, components (only depth is stored, no color information)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	// Set texture sampler parameters.
	// The two calls below tell the texture sampler inside the shader how to upsample and downsample the texture. Here we choose the nearest filtering option, which means we just use the value of the closest pixel to the chosen image coordinate.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// The two calls below tell the texture sampler inside the shader how it should deal with texture coordinates outside of the [0, 1] range. Here we decide to just tile the image.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Variable storing index to framebuffer used for shadow mapping
	GLuint depth_map_fbo;  // fbo: framebuffer object
	// Get the framebuffer
	glGenFramebuffers(1, &depth_map_fbo);
	// Bind the framebuffer so the next glFramebuffer calls affect it
	glBindFramebuffer(GL_FRAMEBUFFER, depth_map_fbo);
	// Attach the depth map texture to the depth map framebuffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_map_texture, 0);
	glDrawBuffer(GL_NONE); //disable rendering colors, only write depth values
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	start = time(0);
	camX = sin(camRotation) * radius;
	camZ = cos(camRotation) * radius;

	Lines3d lines3dObject = Lines3d();
	Grid grid = Grid();
	GroundPlain ground = GroundPlain();
	
	LModel lModel = LModel();
	EModel eModel = EModel();
	EModel eModel2 = EModel();

	LModel lModel2 = LModel();
	EModel eModel3 = EModel();
	CModel cModel = CModel();

	Stage stage = Stage();
	Screen screen = Screen();
	SkyBox skyBox = SkyBox();
	SpotLightModel spotLight = SpotLightModel(0, 0, 0);
	Cylinder cylinder = Cylinder(2.5f, 1.f, 0.125);
	Cube cube = Cube(1, 1, 1, 2, 2, 2);

	glm::mat4 lightProjectionMatrix = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, lightNearPlane, lightFarPlane);
	glm::mat4 lightViewMatrix = glm::lookAt(generalLightPosition, generalLightFocus, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 lightSpaceMatrix = lightProjectionMatrix * lightViewMatrix;

	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();


		// --- Render ---
		// Clear the colorbuffer
		glClearColor(1.f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		switch (currentCam) {
		case 0:
			// FPS
			view_matrix = glm::lookAt(cam_pos, cam_pos + cam_dir, cam_up);
			break;
		case 1:
			// In front of model
			view_matrix = glm::lookAt(cam_pos_front, cam_pos_front + cam_dir_front, cam_up_front);
			break;
		case 2:
			// Back of Model
			view_matrix = glm::lookAt(cam_pos_back, cam_pos_back + cam_dir_back, cam_up_back);
			break;
		case 3:
			// Some extra I guess
			view_matrix = glm::lookAt(cam_pos_light, cam_pos_light + cam_dir_light, cam_up_light);
			break;
		case 4:
			// Rotating
			spotlightColor2 = glm::vec3(1.0, 0.4, 0.4);
			spotlightPosition2 = glm::vec3(camX, 30, camZ);
			spotlightFocus2 = glm::vec3(1.0, 0.0, 0.0);
			spotlightDirection2 = glm::normalize(spotlightFocus2 - spotlightPosition2);
			glUniform3fv(shader.GetUniformLocation("spotlight_position2"), 1, glm::value_ptr(spotlightPosition2));
			glUniform3fv(shader.GetUniformLocation("spotlight_direction2"), 1, glm::value_ptr(spotlightDirection2));
			view_matrix = glm::lookAt(glm::vec3(camX, 30, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
			break;
		}

		// lighting
		//glm::mat4 lightProjectionMatrix = glm::perspective(glm::radians(45.0f), (GLfloat)SHADOW_WIDTH / (GLfloat)SHADOW_HEIGHT, lightNearPlane, lightFarPlane);
		

		if (shadow) {
			shaderShadow.Bind();
			std::cout << "Doing shadowssss" << std::endl;
			lightViewMatrix = glm::lookAt(generalLightPosition, generalLightFocus, glm::vec3(0.0f, 1.0f, 0.0f));
			lightSpaceMatrix = lightProjectionMatrix * lightViewMatrix;

			glUniformMatrix4fv(shaderShadow.GetUniformLocation("light_view_proj_matrix"), 1, 0, glm::value_ptr(lightSpaceMatrix));

			glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
			glBindFramebuffer(GL_FRAMEBUFFER, depth_map_fbo);
			glClear(GL_DEPTH_BUFFER_BIT);

			renderScene(shaderShadow, ground, lModel, eModel, eModel2, lModel2, eModel3, cModel, stage, screen, skyBox, arrayOfTexture, &boxTexture, &metalTexture, &stage_texture, &tileTexture, &skyboxTexture);
			// Unbind the framebuffer
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		glm::mat4 translator_A = glm::translate(glm::mat4(1.0f), model_L_move);
		glm::mat4 translator_La = glm::translate(glm::mat4(1.0f), model_L2_move);
		glm::mat4 translator_D = glm::translate(glm::mat4(1.0f), model_E2_move);
		glm::mat4 translator_L = glm::translate(glm::mat4(1.0f), model_E_move);
		glm::mat4 translator_grid = glm::translate(glm::mat4(1.0f), model_grid_move);
		glm::mat4 translator = glm::translate(glm::mat4(1.0f), model_active_move);
		glm::mat4 translator_Stage = glm::translate(glm::mat4(1.0f), model_Stage_move);
		glm::mat4 translator_Screen = glm::translate(glm::mat4(1.0f), model_Screen_move);



		switch (activeModel) {
		case 0:
			model_matrix = model_world * translator * model_active;
			model_L_matrix = model_world * translator * model_active;
			model_L = model_active;
			model_L_move = model_active_move;

			grid_matrix = model_world  * translator_grid * model_grid;
			model_L2_matrix = model_world * translator_La * model_L2;
			model_E2_matrix = model_world * translator_D * model_E2;
			model_E_matrix = model_world * translator_L * model_E;
			model_Stage_matrix = model_world  * translator_Stage * model_Stage;
			model_Screen_matrix = model_world  * translator_Screen * model_Screen;
			break;
		case 1:
			model_L2_matrix = model_world * translator * model_active;
			model_L2 = model_active;
			model_L2_move = model_active_move;

			model_matrix = model_world * translator_A * model_L;
			grid_matrix = model_world  * translator_grid * model_grid;
			model_L_matrix = model_world * translator_A * model_L;
			model_E2_matrix = model_world * translator_D * model_E2;
			model_E_matrix = model_world * translator_L * model_E;
			model_Stage_matrix = model_world * translator_Stage * model_Stage;
			model_Screen_matrix = model_world * translator_Screen * model_Screen;
			break;
		case 2:
			model_E2_matrix = model_world * translator * model_active;
			model_E2 = model_active;
			model_E2_move = model_active_move;

			model_matrix = model_world * translator_A * model_L;
			grid_matrix = model_world * translator_grid * model_grid;
			model_L_matrix = model_world * translator_A * model_L;
			model_L2_matrix = model_world * translator_La * model_L2;
			model_E_matrix = model_world * translator_L * model_E;
			model_Stage_matrix = model_world * translator_Stage * model_Stage;
			model_Screen_matrix = model_world  * translator_Screen * model_Screen;
			break;
		case 3:
			model_E_matrix = model_world  * translator * model_active;
			model_E = model_active;
			model_E_move = model_active_move;

			model_matrix = model_world * translator_A * model_L;
			grid_matrix = model_world  * translator_grid * model_grid;
			model_L_matrix = model_world * translator_A * model_L;
			model_L2_matrix = model_world  * translator_La * model_L2;
			model_E2_matrix = model_world * translator_D * model_E2;
			model_Stage_matrix = model_world * translator_Stage * model_Stage;
			model_Screen_matrix = model_world * translator_Screen * model_Screen;
			break;
		case 4:
			model_matrix = model_world * translator_A * model_L;
			grid_matrix = model_world  * translator_grid * model_grid;
			model_L_matrix = model_world * translator_A * model_L;
			model_L2_matrix = model_world * translator_La * model_L2;
			model_E2_matrix = model_world * translator_D * model_E2;
			model_E_matrix = model_world * translator_L * model_E;
			model_Stage_matrix = model_world  * translator_Stage * model_Stage;
			model_Screen_matrix = model_world  * translator_Screen * model_Screen;
			break;
		}
		glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(model_matrix));


		glViewport(0, 0, WIDTH, HEIGHT);
		glClearColor(1.f, 0.1f, 0.1f, 1.0f);
		
		shader.Bind();

		if (!shadow) {
			glUniform1i(shader.GetUniformLocation("shadow_on"), shadow);
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUniformMatrix4fv(pm_loc, 1, 0, glm::value_ptr(proj_matrix));
		glUniform3fv(shader.GetUniformLocation("view_position"), 1, glm::value_ptr(cam_pos));
		glUniformMatrix4fv(shader.GetUniformLocation("light_view_proj_matrix"), 1, 0, glm::value_ptr(lightSpaceMatrix));
		// glUniform3fv(shader.GetUniformLocation("light_position"), 1, glm::value_ptr(generalLightPosition));
		glUniform3fv(shader.GetUniformLocation("light_direction"), 1, glm::value_ptr(generalLightDirection));

		
		glUniform1i(flag_id, flag);
		glUniform1i(lights_id, lights);
		glUniform1i(spotlight_id, spotlight);
		glUniform1i(spotlight2_id, spotlight2);
		glUniform1i(spotlight3_id, spotlight3);
		glUniform1i(normalcol_id, normalcol);
		glUniform1i(greyscale_id, greyscale);
		glUniform1i(red_id, red);
		glUniform1i(green_id, green);
		glUniform1i(blue_id, blue);
		glUniform1i(colour_id, colour);
		// --- Render ---
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draws Models
		//model_A_shader.Bind();

		glBindVertexArray(VAO);
		shader.SetUniform1i("u_Texture", 0);
		//shader.SetUniform4f("light_position", 0.0, 30.0, 5.0, 1);
		//shader.SetVec3("light_position", glm::vec3(0.0, 30.0, 5.0));
		renderScene(shader, ground, lModel, eModel, eModel2, lModel2, eModel3, cModel, stage, screen, skyBox, arrayOfTexture, &boxTexture, &metalTexture, &stage_texture, &tileTexture, &skyboxTexture);
		glUniformMatrix4fv(vm_loc, 1, 0, glm::value_ptr(view_matrix));
		glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(model_Light_matrix));
		spotLight.drawModel(shader, model_Light_matrix);

		// Draws line
		glLineWidth(1.0f);
		glUniformMatrix4fv(vm_loc, 1, 0, glm::value_ptr(view_matrix));
		glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(line_matrix));
		arrayOfTexture[4].Bind();
		lines3dObject.drawLines(&shader, line_matrix);
		arrayOfTexture[4].Unbind();

		// Draws grid
		lines3dShader.Bind();
		glLineWidth(0.5f);
		glUniformMatrix4fv(vm_loc_lines_3d, 1, 0, glm::value_ptr(view_matrix));
		glUniformMatrix4fv(mm_loc_lines_3d, 1, 0, glm::value_ptr(grid_matrix));
		boxTexture.activeTexture = activeModelTexture;
		metalTexture.activeTexture = activeModelTexture;
		evilDann.activeTexture = activeModelTexture;
		dio.activeTexture = activeModelTexture;
		texture_AL_1.activeTexture = activeModelTexture;
		texture_AL_2.activeTexture = activeModelTexture;
		stage_texture.activeTexture = activeModelTexture;
		tileTexture.activeTexture = activeModelTexture;

		for (int i = 0; i < sizeof(arrayOfTexture) / sizeof(arrayOfTexture[0]); i++) {
			arrayOfTexture[i].activeTexture = activeModelTexture;
		}

		// Unbinds VAO
		glBindVertexArray(0);

		//activeModel = initModel;
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}

void renderScene(Shader& shader, GroundPlain& ground, LModel& lModel, EModel& eModel, EModel& eModel2, LModel lModel2, EModel eModel3, CModel& cModel, Stage& stage, Screen& screen, SkyBox skyBox, Texture* arrayOfTexture, Texture* boxTexture, Texture* metalTexture, Texture* stage_texture, Texture* tileTexture, Texture* skyboxTexture){
	
	glUniformMatrix4fv(shader.GetUniformLocation("mm"), 1, 0, glm::value_ptr(model_L_matrix));
	//glUniform3fv(shader.GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
	lModel.drawLetter(boxTexture, &shader, model_L_matrix);

	glUniformMatrix4fv(shader.GetUniformLocation("mm"), 1, 0, glm::value_ptr(model_E_matrix));
	//glUniform3fv(shader.GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
	eModel.drawLetter(boxTexture, &shader, model_E_matrix);

	glUniformMatrix4fv(shader.GetUniformLocation("mm"), 1, 0, glm::value_ptr(model_E2_matrix));
	//glUniform3fv(shader.GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
	eModel2.drawLetter(metalTexture, &shader, model_E2_matrix);

	glUniformMatrix4fv(shader.GetUniformLocation("mm"), 1, 0, glm::value_ptr(model_L2_matrix));
	lModel2.drawLetter(metalTexture, &shader, model_L2_matrix);

	glUniformMatrix4fv(shader.GetUniformLocation("mm"), 1, 0, glm::value_ptr(model_E3_matrix));
	eModel3.drawLetter(metalTexture, &shader, model_E3_matrix);

	glUniformMatrix4fv(shader.GetUniformLocation("mm"), 1, 0, glm::value_ptr(model_C_matrix));
	cModel.drawModel(boxTexture, &shader, model_C_matrix);

	glUniformMatrix4fv(shader.GetUniformLocation("mm"), 1, 0, glm::value_ptr(model_Sky_matrix));
	//glUniform3fv(shader.GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
    skyBox.drawModel(skyboxTexture, metalTexture, &shader, model_Sky_matrix);

	if (time(0) - start == n) {
		if (currentIndex == (sizeof(arrayOfTexture) / sizeof(arrayOfTexture[0]) - 1)) {
			currentIndex = 0;
		}
		else {
			currentIndex++;
		}
		start = start + n;
	}
	glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(model_Screen_matrix));
	//glUniform3fv(shader.GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(0, 0, 0)));
	screen.drawModel(renderingMode, &arrayOfTexture[currentIndex]);

	//model_Stage_shader Bind()
	glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(model_Stage_matrix));
	//glUniform3fv(shader.GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
	stage.drawModel(renderingMode, stage_texture, &shader, model_Stage_matrix);

	// Ground
	glUniformMatrix4fv(vm_loc, 1, 0, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(ground_matrix));
	ground.drawGround(stage_texture);
}
