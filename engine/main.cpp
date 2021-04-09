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
#include "../AlessandroModel.h"
#include "../LeCherngModel.h"
#include "../Laginho.h"
#include "../DannModel.h"
#include "../Stage.h"
#include "../Screen.h"
#include "../Texture.h"
#include "../Cylinder.h"
#include "../SModel.h"
#include "../SkyBox.h"
#include "../SpotLightModel.h"

using namespace std;

#pragma region Initialization

// Window dimensions
const GLuint WIDTH = 1024, HEIGHT = 768;

void renderScene(GroundPlain ground, AlessandroModel alessandroModel, LeCherngModel leCherngModel, DannModel danModel, LaginhoModel laginModel, Stage stage, Screen screen, SModel sModel1, SModel sModel2, SkyBox skyBox, Texture* arrayOfTexture, Texture* boxTexture, Texture* metalTexture, Texture* stage_texture, Texture* tileTexture, Shader* shader);

glm::mat4 model_matrix;
glm::mat4 view_matrix;
glm::mat4 proj_matrix;

std::vector<int> indices;
std::vector<glm::vec3> vertices;
std::vector<glm::vec3> normals;
std::vector<glm::vec2> UVs;

//camera settings
glm::vec3 cam_pos = glm::vec3(0, 2, 30);
glm::vec3 cam_dir = glm::vec3(0, 0, -1); //direction means what the camera is looking at
glm::vec3 temp_cam_dir = glm::vec3(0, 0, 1); //use this for the cross product or else when cam_dir and cam_up overlap, the cross product will be 0 (bad!)
glm::vec3 cam_up = glm::vec3(0, 1, 0); //up defines where the top of the camera is directing towards

//model settings
glm::mat4 model_active = glm::rotate(glm::mat4(1.0f), glm::radians(60.f), glm::vec3(0, 1, 0)); //active model
glm::vec3 model_active_move = glm::vec3(-10, 2, -6); //to apply translational transformations

glm::mat4 model_general = glm::mat4(1.0f); //active model
glm::vec3 model_general_move = glm::vec3(0, 2, -10); //to apply translational transformations

float shearX = 0.f;
float shearY = 0.f;

glm::vec3 cam_pos_back = glm::vec3(0, 3, -28);
glm::vec3 cam_dir_back = glm::vec3(0, 0, -1);
glm::vec3 cam_up_back = glm::vec3(0, 1, 0);

glm::vec3 cam_pos_front = glm::vec3(0, 3, -23);
glm::vec3 cam_dir_front = glm::vec3(0, 0, 1);
glm::vec3 cam_up_front = glm::vec3(0, 1, 0);

GLuint vm_loc ;
GLuint pm_loc ;
GLuint mm_loc;
GLuint flag_id ;
GLuint lights_id ;
GLuint spotlight_id;
GLuint normalcol_id ;
GLuint greyscale_id ;
GLuint red_id ;
GLuint green_id ;
GLuint blue_id ;
GLuint colour_id ;

//Alessandro
glm::mat4 model_A = glm::mat4(1.0f);//Model of letter A
glm::vec3 model_A_move = glm::vec3(0.5, 23 - 0.5, -25); //to apply translational transformations
//Le Cherng
glm::mat4 model_L = glm::mat4(1.0f);//Model of letter U
glm::vec3 model_L_move = glm::vec3(0.5, 13 - 0.5, -25); //to apply translational transformations
//Dan
glm::mat4 model_D = glm::mat4(1.0f);//Model of letter K
glm::vec3 model_D_move = glm::vec3(-0.5, 28 - 0.5, -25); //to apply translational transformations
//LaginHo
glm::mat4 model_La = glm::mat4(1.0f);//Model of letter O
glm::vec3 model_La_move = glm::vec3(0.5, 18 - 0.5, -25); //to apply translational transformations
//LaginHo
glm::mat4 model_grid = glm::mat4(1.0f);
glm::vec3 model_grid_move = glm::vec3(0, 0, 0); //to apply translational transformations

glm::mat4 model_Sky = glm::mat4(1.0f);//Model of letter O
glm::vec3 model_Sky_move = glm::vec3(0, 0, 0); //to apply translational transformations


//World Matrix
glm::mat4 model_world = glm::mat4(1.0f);
glm::vec3 model_world_move = glm::vec3(0, 0, 0); //to apply translational transformations

glm::mat4 model_Stage = glm::mat4(1.0f);
glm::vec3 model_Stage_move = glm::vec3(-10, 0, -25); //to apply translational transformations

glm::mat4 model_Screen = glm::mat4(1.0f);
glm::vec3 model_Screen_move = glm::vec3(-10, 0, 25); //to apply translational transformations

glm::mat4 model_spot_light = glm::mat4(1.0f);
glm::vec3 model_spot_light_move = glm::vec3(0, 24, -25); //to apply translational transformations

glm::mat4 model_S1 = glm::mat4(1.0f);////Model of first letter S
glm::vec3 model_S1_move = glm::vec3(0, 0.5, -25); //to apply translational transformations

glm::mat4 model_S2 = glm::mat4(1.0f);///Model of second letter S
glm::vec3 model_S2_move = glm::vec3(0, 7 - 0.5, -25); //to apply translational transformations


glm::mat4 model_A_matrix ;

glm::mat4 model_Sky_matrix;
//Le Cherng
glm::mat4 model_L_matrix ;
//Dan
glm::mat4 model_D_matrix ;
//LaginHo
glm::mat4 model_La_matrix ;
glm::mat4 model_Stage_matrix ;
glm::mat4 model_spot_light_matrix;
glm::mat4 model_Screen_matrix;
glm::mat4 grid_matrix ;
glm::mat4 ground_matrix ;
glm::mat4 line_matrix;

glm::mat4 model_S1_matrix;

glm::mat4 model_S2_matrix;

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
bool normalcol = false;
bool greyscale = false;
bool red = false;
bool green = false;
bool blue = false;
bool colour = false;
bool activeModelTexture = true;

//0 for points, 1 for lines, 2 for triangle
int renderingMode = 2;
//0 for alessandro, 1 for laginho, 2 for Dann, 3 for Le Cherng
int activeModel = 0;
int previousActiveModel = 0;
int initModel = activeModel;
int currentCam=0;

// lighting settings

// Point Light
glm::vec3 lightColor = glm::vec3(1.0, 0.5, 1.0);
glm::vec3 lightPosition = glm::vec3(1.2f, 5.0f, 2.0f);

// Spotlight
glm::vec3 spotlightColor = glm::vec3(1.0, 1.0, 1.0);
glm::vec3 spotlightPosition = glm::vec3(0, 20, -25);
glm::vec3 spotlightFocus = glm::vec3(0, 0, -23);
glm::vec3 spotlightDirection = glm::normalize(spotlightFocus - spotlightPosition);

float spotlightCutoff = glm::cos(glm::radians(12.5f));
float spotlightOuterCutoff = glm::cos(glm::radians(15.0f));
float spotlightConstant = 1.0f;
float spotlightLinear = 0.09;
float spotlightQuadratic = 0.032;

//glm::vec3 object_color = glm::vec3(0.5, 0.5, 0.5);

#pragma endregion Initialization 

void resetToPreviousModel(int previousActiveModel) {
	switch (previousActiveModel)
	{
	case 0:
		model_active = model_A;
		model_active_move = model_A_move;
		break;
	case 1:
		model_active = model_La;
		model_active_move = model_La_move;
		break;
	case 2:
		model_active = model_D;
		model_active_move = model_D_move;
		break;
	case 3:
		model_active = model_L;
		model_active_move = model_L_move;
		break;
	case 4:
		model_active = model_S1;
		model_active_move = model_S1_move;
		break;

	case 5:
		model_active = model_S2;
		model_active_move = model_S2_move;
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
				model_world = glm::rotate(model_world, glm::radians(5.f), glm::vec3(0, 1, 0));
			}
			if (key == GLFW_KEY_DOWN) { //left arrow rotates the camera left about the down vector
				model_world = glm::rotate(model_world, glm::radians(5.f), glm::vec3(-1, 0, 0));
			}
			if (key == GLFW_KEY_UP) { //left arrow rotates the camera left about the up vector
				model_world = glm::rotate(model_world, glm::radians(5.f), glm::vec3(1, 0, 0));
			}
			if (key == GLFW_KEY_LEFT) { //left arrow rotates the camera left about the left vector
				model_world = glm::rotate(model_world, glm::radians(5.f), glm::vec3(0, -1, 0));
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
		model_A = glm::mat4(1.0f);
		model_A_move = glm::vec3(0, 2, -10); //to apply translational transformations
		//Le Cherng
		model_L = glm::mat4(1.0f);
		model_L_move = glm::vec3(0, 2, 10); //to apply translational transformations
		   //Dan
		model_D = glm::mat4(1.0f);
		model_D_move = glm::vec3(10, 2, 0); //to apply translational transformations
	   //LaginHo
		model_La = glm::mat4(1.0f);
		model_La_move = glm::vec3(-10, 2, 0); //to apply translational transformations
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
		model_A = glm::mat4(1.0f);
		model_A_move = glm::vec3(randomXPosition, 2, randomZPosition); //to apply translational transformations

		//Le Cherng
		randomXPosition = -15 + (std::rand() % (15 + 15 + 1));
		randomZPosition = -15 + (std::rand() % (15 + 15 + 1));
		model_L = glm::mat4(1.0f);
		model_L_move = glm::vec3(randomXPosition, 2, randomZPosition); //to apply translational transformations

		//Dan
		randomXPosition = -15 + (std::rand() % (15 + 15 + 1));
		randomZPosition = -15 + (std::rand() % (15 + 15 + 1));
		model_D = glm::mat4(1.0f);
		model_D_move = glm::vec3(randomXPosition, 2, randomZPosition); //to apply translational transformations

	   //LaginHo
		randomXPosition = -15 + (std::rand() % (15 + 15 + 1));
		randomZPosition = -15 + (std::rand() % (15 + 15 + 1));
		model_La = glm::mat4(1.0f);
		model_La_move = glm::vec3(randomXPosition, 2, randomZPosition); //to apply translational transformations
		 
	}
	
	if (!worldOrientationKeyPressed) {
		//WASD buttons to move the model
		if (!leftShiftPressed) {
			if (key == GLFW_KEY_W) { //I moves the object along the +Y axis
				model_active_move.y += 1;
			}

			if (key == GLFW_KEY_S) { //K moves the object along the -Y
				model_active_move.y -= 1;
			}

			if (key == GLFW_KEY_A) { //J moves the object along the +X axis
				model_active_move.x -= 1;
			}

			if (key == GLFW_KEY_D) { //L moves the object along the -X axis
				model_active_move.x += 1;
			}

			if (key == GLFW_KEY_PAGE_UP) { //PgUp moves the object along the +Z axis
				model_active_move.z += 1;
			}

			if (key == GLFW_KEY_PAGE_DOWN) { //PgDown moves the object along the -Z axis
				model_active_move.z -= 1;
			}
		}

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
				model_A = glm::rotate(model_A, glm::radians(5.f), glm::vec3(1, 0, 0));
				model_D = glm::rotate(model_D, glm::radians(5.f), glm::vec3(1, 0, 0));
				model_La = glm::rotate(model_La, glm::radians(5.f), glm::vec3(1, 0, 0));
				model_L = glm::rotate(model_L, glm::radians(5.f), glm::vec3(1, 0, 0));
			}
			if (key == GLFW_KEY_DOWN) { //S rotates the object about the -X axis
				model_active = glm::rotate(model_active, glm::radians(5.f), glm::vec3(-1, 0, 0));
				model_A = glm::rotate(model_A, glm::radians(5.f), glm::vec3(-1, 0, 0));
				model_D = glm::rotate(model_D, glm::radians(5.f), glm::vec3(-1, 0, 0));
				model_La = glm::rotate(model_La, glm::radians(5.f), glm::vec3(-1, 0, 0));
				model_L = glm::rotate(model_L, glm::radians(5.f), glm::vec3(-1, 0, 0));
			}
			if (key == GLFW_KEY_LEFT) { //N rotates the object about the Y axis,
				model_active = glm::rotate(model_active, glm::radians(5.f), glm::vec3(0, 1, 0));
				model_A = glm::rotate(model_A, glm::radians(5.f), glm::vec3(0, 1, 0));
				model_D = glm::rotate(model_D, glm::radians(5.f), glm::vec3(0, 1, 0));
				model_La = glm::rotate(model_La, glm::radians(5.f), glm::vec3(0, 1, 0));
				model_L = glm::rotate(model_L, glm::radians(5.f), glm::vec3(0, 1, 0));
			}
			if (key == GLFW_KEY_RIGHT) { //N rotates the object about the -Y axis,
				model_active = glm::rotate(model_active, glm::radians(5.f), glm::vec3(0, -1, 0));
				model_A = glm::rotate(model_A, glm::radians(5.f), glm::vec3(0, -1, 0));
				model_D = glm::rotate(model_D, glm::radians(5.f), glm::vec3(0, -1, 0));
				model_La = glm::rotate(model_La, glm::radians(5.f), glm::vec3(0, -1, 0));
				model_L = glm::rotate(model_L, glm::radians(5.f), glm::vec3(0, -1, 0));
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
			model_active = model_A;
			model_active_move = model_A_move;
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
			model_active = model_La;
			model_active_move = model_La_move;
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
			model_active = model_D;
			model_active_move = model_D_move;
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
			model_active = model_L;
			model_active_move = model_L_move;
		}

		//toggle between Gouraud and Phong shading
		if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
			if (flag == false)
				flag = true;
			else
				flag = false;
		}

		if (key == GLFW_KEY_6 && action == GLFW_PRESS) {
			if (lights == false)
				lights = true;
			else
				lights = false;
		}

		if (key == GLFW_KEY_7 && action == GLFW_PRESS) {
			if (spotlight == false)
				spotlight = true;
			else
				spotlight = false;
		}

		if (key == GLFW_KEY_X && action == GLFW_PRESS) {
			activeModelTexture = !activeModelTexture;
		}

		/*if (key == GLFW_KEY_M && action == GLFW_PRESS) {
			if (normalcol == false)
				normalcol = true;
			else
				normalcol = false;
		}

		if (key == GLFW_KEY_G && action == GLFW_PRESS) {
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
	if (key == GLFW_KEY_M && action == GLFW_PRESS) {
		//fps
		currentCam = 1;
		spotlight = true;

	}
	if (key == GLFW_KEY_B && action == GLFW_PRESS) {
		//back fps
		currentCam = 2;
		spotlight = false;
		
	}
	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		currentCam = 0;
		spotlight = false;
	}



	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		//Camera at light source and toggle on and of the light
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

	//Alessandro
	model_A_matrix = glm::translate(glm::mat4(1.f), model_A_move);
	//Le Cherng
	model_L_matrix = glm::translate(glm::mat4(1.f), model_L_move);
	//Dan
	model_D_matrix = glm::translate(glm::mat4(1.f), model_D_move);
	//LaginHo
	model_La_matrix = glm::translate(glm::mat4(1.f), model_La_move);

	model_Stage_matrix = glm::translate(glm::mat4(1.f), model_Stage_move);

	model_spot_light_matrix = glm::translate(glm::mat4(1.f), model_spot_light_move);

	model_Screen_matrix = glm::translate(glm::mat4(1.f), model_Screen_move);

	model_S1_matrix = glm::translate(glm::mat4(1.f), model_S1_move);

	model_S2_matrix = glm::translate(glm::mat4(1.f), model_S2_move);
	model_Sky_matrix = glm::translate(glm::mat4(1.f), model_Sky_move);

	



	grid_matrix = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0));
    ground_matrix = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0));
	line_matrix = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0));

	 vm_loc = shader.GetUniformLocation("vm");
	 pm_loc = shader.GetUniformLocation("pm");
     mm_loc = shader.GetUniformLocation("mm");
     flag_id = shader.GetUniformLocation("flag");
     lights_id = shader.GetUniformLocation("lights");
	 spotlight_id = shader.GetUniformLocation("spotlight_on");
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

	Texture boxTexture("resources/textures/boxtexture.jpg");
	Texture metalTexture("resources/textures/metaltexture.jpg");
	Texture evilDann("resources/textures/evilDann.png");
	Texture dio("resources/textures/dio.jpg");
	Texture texture_AL_1("resources/textures/allesandro1.jpg");
	Texture texture_AL_2("resources/textures/allesandro2.jpg");
	Texture texture_LA_1("resources/textures/laginho1.jpg");
	Texture texture_LA_2("resources/textures/laginho2.jpg");
	Texture bonus1("resources/textures/bonusTexture1.jpg");
	Texture bonus2("resources/textures/bonusTexture2.jpg");
	Texture tileTexture("resources/textures/tiletexture.jpg");
	Texture modelAllesandroTexture("resources/textures/ModelAllesandro.png");
	Texture modelDanielTexture("resources/textures/ModelDaniel.png");
	Texture modelLaginhoTexture("resources/textures/ModelLaginho.png");
	Texture modelLeCherngTexture("resources/textures/ModelLeCherng.png");
	Texture stage_texture("resources/textures/stage_texture.jpg");
	
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

	
	start = time(0);

	Lines3d lines3dObject = Lines3d();
	Grid grid = Grid();
	GroundPlain ground = GroundPlain();
	AlessandroModel alessandroModel = AlessandroModel();
	LeCherngModel leCherngModel = LeCherngModel();
	DannModel danModel = DannModel();
	LaginhoModel laginModel = LaginhoModel();
	Stage stage = Stage();
	Screen screen = Screen();
	SModel sModel1 = SModel();
	SModel sModel2 = SModel();
	SkyBox skyBox = SkyBox();
	SpotLightModel spotLight = SpotLightModel();
	Cylinder cylinder = Cylinder(2.5f, 1.f, 0.125);


	Cube cube = Cube(1, 1, 1, 2, 2, 2);


	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		shader.Bind();
		switch (currentCam) {
		case 0:
			view_matrix = glm::lookAt(cam_pos, cam_pos + cam_dir, cam_up);
			break;
		case 1:
			view_matrix = glm::lookAt(cam_pos_front, cam_pos_front + cam_dir_front, cam_up_front);
			break;
		case 2:
			view_matrix = glm::lookAt(cam_pos_back, cam_pos_back + cam_dir_back, cam_up_back);
			break;
		case 4:
			view_matrix = glm::lookAt(cam_pos, cam_pos + cam_dir, cam_up);
			break;
		
		}
	


		glm::mat4 translator_A = glm::translate(glm::mat4(1.0f), model_A_move);
		glm::mat4 translator_La = glm::translate(glm::mat4(1.0f), model_La_move);
		glm::mat4 translator_D = glm::translate(glm::mat4(1.0f), model_D_move);
		glm::mat4 translator_L = glm::translate(glm::mat4(1.0f), model_L_move);
		glm::mat4 translator_grid = glm::translate(glm::mat4(1.0f), model_grid_move);
		glm::mat4 translator = glm::translate(glm::mat4(1.0f), model_active_move);
		glm::mat4 translator_Stage = glm::translate(glm::mat4(1.0f), model_Stage_move); 
		glm::mat4 translator_Spot_Light = glm::translate(glm::mat4(1.0f), model_spot_light_move);
		glm::mat4 translator_Screen = glm::translate(glm::mat4(1.0f), model_Screen_move);

		glm::mat4 ground_rotatation = glm::rotate(model_grid, 4.71239f, glm::vec3(1, 0, 0));
		ground_matrix = model_world * model_grid * ground_rotatation;

		glm::mat4 light_rotatation = glm::rotate(model_grid, -4.71239f, glm::vec3(1, 0, 0));
		model_spot_light_matrix = model_world * translator_Spot_Light * model_spot_light * light_rotatation;

		switch (activeModel) {
		case 0:
			model_matrix = model_world * translator * model_active;
			model_A_matrix = model_world * translator * model_active;
			model_A = model_active;
			model_A_move = model_active_move;

			grid_matrix = model_world  * translator_grid * model_grid;
			model_La_matrix = model_world * translator_La * model_La;
			model_D_matrix = model_world * translator_D * model_D;
			model_L_matrix = model_world * translator_L * model_L;
			model_Stage_matrix = model_world  * translator_Stage * model_Stage;
			model_Screen_matrix = model_world  * translator_Screen * model_Screen;
			break;
		case 1:
			model_La_matrix = model_world * translator * model_active;
			model_La = model_active;
			model_La_move = model_active_move;

			model_matrix = model_world * translator_A * model_A;
			grid_matrix = model_world  * translator_grid * model_grid;
			model_A_matrix = model_world * translator_A * model_A;
			model_D_matrix = model_world * translator_D * model_D;
			model_L_matrix = model_world * translator_L * model_L;
			model_Stage_matrix = model_world * translator_Stage * model_Stage;
			model_Screen_matrix = model_world * translator_Screen * model_Screen;
			break;
		case 2:
			model_D_matrix = model_world * translator * model_active;
			model_D = model_active;
			model_D_move = model_active_move;

			model_matrix = model_world * translator_A * model_A;
			grid_matrix = model_world * translator_grid * model_grid;
			model_A_matrix = model_world * translator_A * model_A;
			model_La_matrix = model_world * translator_La * model_La;
			model_L_matrix = model_world * translator_L * model_L;
			model_Stage_matrix = model_world * translator_Stage * model_Stage;
			model_Screen_matrix = model_world  * translator_Screen * model_Screen;
			break;
		case 3:
			model_L_matrix = model_world  * translator * model_active;
			model_L = model_active;
			model_L_move = model_active_move;

			model_matrix = model_world * translator_A * model_A;
			grid_matrix = model_world  * translator_grid * model_grid;
			model_A_matrix = model_world * translator_A * model_A;
			model_La_matrix = model_world  * translator_La * model_La;
			model_D_matrix = model_world * translator_D * model_D;
			model_Stage_matrix = model_world * translator_Stage * model_Stage;
			model_Screen_matrix = model_world * translator_Screen * model_Screen;
			break;
		case 4:
			model_matrix = model_world * translator_A * model_A;
			grid_matrix = model_world  * translator_grid * model_grid;
			model_A_matrix = model_world * translator_A * model_A;
			model_La_matrix = model_world * translator_La * model_La;
			model_D_matrix = model_world * translator_D * model_D;
			model_L_matrix = model_world * translator_L * model_L;
			model_Stage_matrix = model_world  * translator_Stage * model_Stage;
			model_Screen_matrix = model_world  * translator_Screen * model_Screen;
			break;
		}
		glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(model_matrix));

		glUniform1i(flag_id, flag);
		glUniform1i(lights_id, lights);
		glUniform1i(spotlight_id, spotlight);
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
		renderScene(ground, alessandroModel, leCherngModel, danModel, laginModel, stage, screen, sModel1, sModel2, skyBox, arrayOfTexture, &boxTexture, &metalTexture, &stage_texture, &tileTexture, &shader);
		glUniformMatrix4fv(vm_loc, 1, 0, glm::value_ptr(view_matrix));
		glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(line_matrix));

		// spot light model
		glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(model_spot_light_matrix));
		spotLight.drawModel(0,0,0);

		// Draws line
		glLineWidth(1.0f);
		glUniformMatrix4fv(vm_loc_lines_3d, 1, 0, glm::value_ptr(view_matrix));
		glUniformMatrix4fv(mm_loc_lines_3d, 1, 0, glm::value_ptr(line_matrix));
		//cylinder.draw(&shader);

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
		grid.drawGrid();
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

void renderScene( GroundPlain ground, AlessandroModel alessandroModel, LeCherngModel leCherngModel, DannModel danModel, LaginhoModel laginModel, Stage stage, Screen screen, SModel sModel1, SModel sModel2, SkyBox skyBox, Texture* arrayOfTexture, Texture* boxTexture, Texture* metalTexture, Texture* stage_texture, Texture* tileTexture, Shader* shader){
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glUniformMatrix4fv(vm_loc, 1, 0, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(line_matrix));
	glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(model_A_matrix));
	//glUniform3fv(shader.GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
	//alessandroModel.drawModel(renderingMode, boxTexture, metalTexture, shearX, shearY);

	//model_L_shader.Bind();
	glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(model_L_matrix));
	//glUniform3fv(shader.GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
	//leCherngModel.drawModel(renderingMode, boxTexture, metalTexture, shearX, shearY);

	//model_La_shader.Bind();
	glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(model_La_matrix));
	//glUniform3fv(shader.GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
	//laginModel.drawModel(renderingMode, boxTexture, metalTexture, shearX, shearY);

	glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(model_S1_matrix));
	sModel1.drawModel(renderingMode, boxTexture);
	glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(model_S2_matrix));
	sModel2.drawModel(renderingMode, boxTexture);


	glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(model_Sky_matrix));
	//glUniform3fv(shader.GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
     skyBox.drawModel(renderingMode, boxTexture, metalTexture, shearX, shearY, shader, model_Sky_matrix);

	//model_D_shader.Bind();
	glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(model_D_matrix));
	//glUniform3fv(shader.GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
	danModel.drawModel(renderingMode, boxTexture, metalTexture, shearX, shearY, shader, model_D_matrix);
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
	stage.drawModel(renderingMode, stage_texture);

	// Ground
	glUniformMatrix4fv(vm_loc, 1, 0, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(ground_matrix));
	ground.drawGround(tileTexture);
}




