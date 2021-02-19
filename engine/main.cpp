//example skeleton code 2021 winter comp371
//modified from http://learnopengl.com/

#include <GL/glew.h>	// include GL Extension Wrangler
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>	// include GLFW helper library

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ObjLoaderIndex.h"
#include "Shader.h"
#include "GLDebugMessageCallback.h"
#include "../lines3d.h"
#include "../grid.h"
#include "../AlessandroModel.h"
#include "../LeCherngModel.h"
#include "../Laginho.h"
#include "../DannModel.h"
#include "../Model.hpp"
#include "../Transform.hpp"

using namespace std;

// Window dimensions
const GLuint WIDTH = 1024, HEIGHT = 768;

struct Entity {
	Entity(Transform t, glm::vec3 c, RawModel* m){
		transform = t;
		color = c;
		model = m;
	}
	Transform transform;
	glm::vec3 color;
	RawModel* model;
};

struct Letter {
	Letter(){

	}
	std::vector<Entity> entities;
	bool isSelected = false;
};

std::vector<Letter> letters;

//camera settings
glm::vec3 cam_pos = glm::vec3(0, 10, 20);
glm::vec3 cam_dir = glm::vec3(0, -1, -2); //direction means what the camera is looking at
glm::vec3 temp_cam_dir = glm::vec3(0, 0, 1); //use this for the cross product or else when cam_dir and cam_up overlap, the cross product will be 0 (bad!)
glm::vec3 cam_up = glm::vec3(0, 1, 0); //up defines where the top of the camera is directing towards

//model settings
glm::mat4 model = glm::mat4(1.0f); //active model
glm::vec3 model_move = glm::vec3(0, 2, -10); //to apply translational transformations

//Alessandro
glm::mat4 model_A = glm::mat4(1.0f);
glm::vec3 model_A_move = glm::vec3(0, 2, -10); //to apply translational transformations
//Le Cherng
glm::mat4 model_L = glm::mat4(1.0f);
glm::vec3 model_L_move = glm::vec3(0, 2, 10); //to apply translational transformations
//Dan
glm::mat4 model_D = glm::mat4(1.0f);
glm::vec3 model_D_move = glm::vec3(10, 2, 0); //to apply translational transformations
//LaginHo
glm::mat4 model_La = glm::mat4(1.0f);
glm::vec3 model_La_move = glm::vec3(-10, 2, 0); //to apply translational transformations
//LaginHo
glm::mat4 model_grid = glm::mat4(1.0f);
glm::vec3 model_grid_move = glm::vec3(0, 0, 0); //to apply translational transformations

//World Matrix
glm::mat4 model_world = glm::mat4(1.0f);
glm::vec3 model_world_move = glm::vec3(0, 0, 0); //to apply translational transformations

//color settings
bool flag = false;
bool lights = false;
bool normalcol = false;
bool greyscale = false;
bool red = false;
bool green = false;
bool blue = false;
bool colour = false;

//0 for points, 1 for lines, 2 for triangle
int renderingMode = 2;
//0 for alessandro, 1 for laginho, 2 for Dann, 3 for Le Cherng
int activeModel = 0;
int previousActiveModel = 0;
int initModel = activeModel;
//glm::vec3 object_color = glm::vec3(0.5, 0.5, 0.5);
void DrawCube(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat edgeSize);

void resetToPreviousModel(int previousActiveModel) {
	switch (previousActiveModel)
	{
	case 0:
		model = model_A;
		model_move = model_A_move;
		break;
	case 1:
		model = model_La;
		model_move = model_La_move;
		break;
	case 2:
		model = model_D;
		model_move = model_D_move;
		break;
	case 3:
		model = model_L;
		model_move = model_L_move;
		break;
	case 4:
		cout << "Error Occured" << endl;
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

	if(key == GLFW_KEY_H){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if(key == GLFW_KEY_G){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if(key == GLFW_KEY_0){
		for(auto& i : letters){
			i.isSelected = false;
		}
		letters[0].isSelected = true;
	}
	if(key == GLFW_KEY_1){
		for(auto& i : letters){
			i.isSelected = false;
		}
		letters[1].isSelected = true;
	}
	if(key == GLFW_KEY_2){
		for(auto& i : letters){
			i.isSelected = false;
		}
		letters[2].isSelected = true;
	}
	if(key == GLFW_KEY_3){
		for(auto& i : letters){
			i.isSelected = false;
		}
		letters[3].isSelected = true;
	}
	if(key == GLFW_KEY_4){
		for(auto& i : letters){
			i.isSelected = false;
		}
		letters[4].isSelected = true;
	}
	if(key == GLFW_KEY_5){
		for(auto& i : letters){
			i.isSelected = false;
		}
		letters[5].isSelected = true;
	}

	if(key == GLFW_KEY_W){
		for(auto& i : letters){
			if(i.isSelected){
				for(auto& i : i.entities){
					i.transform.position.z -= 1.0f;
				}
			}
		}
	}
	if(key == GLFW_KEY_A){
		for(auto& i : letters){
			if(i.isSelected){
				for(auto& i : i.entities){
					i.transform.position.x -= 1.0f;
				}
			}
		}
	}
	if(key == GLFW_KEY_S){
		for(auto& i : letters){
			if(i.isSelected){
				for(auto& i : i.entities){
					i.transform.position.z += 1.0f;
				}
			}
		}
	}
	if(key == GLFW_KEY_D){
		for(auto& i : letters){
			if(i.isSelected){
				for(auto& i : i.entities){
					i.transform.position.x += 1.0f;
				}
			}
		}
	}
	if(key == GLFW_KEY_P){
		for(auto& i : letters){
			if(i.isSelected){
				for(auto& i : i.entities){
					i.transform.position.y += 1.0f;
				}
			}
		}
	}
	if(key == GLFW_KEY_M){
		for(auto& i : letters){
			if(i.isSelected){
				for(auto& i : i.entities){
					i.transform.position.y -= 1.0f;
				}
			}
		}
	}


	if(key == GLFW_KEY_UP){
		cam_pos.z -= 1.0f;
	}
	if(key == GLFW_KEY_DOWN){
		cam_pos.z += 1.0f;
	}
	if(key == GLFW_KEY_LEFT){
		cam_pos.x -= 1.0f;
	}
	if(key == GLFW_KEY_RIGHT){
		cam_pos.x += 1.0f;
	}
	if(key == GLFW_KEY_SPACE){
		cam_pos.y += 1.0f;
	}
	if(key == GLFW_KEY_LEFT_SHIFT){
		cam_pos.y -= 1.0f;
	}

	//if you press the Esc key, the window will close
	if (key == GLFW_KEY_ESCAPE) {
		glfwSetWindowShouldClose(window, GL_TRUE);
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

     glfwSwapInterval(1);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
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
	RawModel cubeModel;
	cubeModel.loadFromFile("resources/objects/cube.obj");
	RawModel sphereModel;
	sphereModel.loadFromFile("resources/objects/sphere.obj");
	RawModel cylinderModel;
	cylinderModel.loadFromFile("resources/objects/cylinder.obj");
	RawModel monkey;
	monkey.loadFromFile("resources/objects/monkey.obj");
	Transform mTransform(glm::vec3(0, 10, -50), glm::vec3(0, 0, 0), glm::vec3(20, 20, 20));
	Transform xTransform(glm::vec3(1.25, 0, 0), glm::vec3(0, 0, 90), glm::vec3(0.25, 2.5, 0.25));
	Transform yTransform(glm::vec3(0, 1.25, 0), glm::vec3(0, 90, 0), glm::vec3(0.25, 2.5, 0.25));
	Transform zTransform(glm::vec3(0, 0, 1.25), glm::vec3(90, 0, 0), glm::vec3(0.25, 2.5, 0.25));


	//Creating entities
	letters.push_back(Letter());
	letters.push_back(Letter());
	letters.push_back(Letter());
	letters.push_back(Letter());
	letters.push_back(Letter());
	letters.push_back(Letter());
	letters.push_back(Letter());

	float offset = 0.0f;
	float height = 0.0f;

	letters[0].entities.emplace_back(Transform(glm::vec3(0 + offset, 2.5 + height, -5), glm::vec3(0, 0, 0), glm::vec3(1, 5, 1)), glm::vec3(1, 0, 0), &cubeModel);
	letters[0].entities.emplace_back(Transform(glm::vec3(1 + offset, 2.5 + height, -5), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)), glm::vec3(1, 0, 0), &sphereModel);
	letters[0].entities.emplace_back(Transform(glm::vec3(2 + offset, 2.5 + height, -5), glm::vec3(0, 0, 0), glm::vec3(1, 5, 1)), glm::vec3(1, 0, 0), &cubeModel);

	height += 6.0f;

	letters[1].entities.emplace_back(Transform(glm::vec3(0 + offset, 2.5 + height, -5), glm::vec3(0, 0, 0), glm::vec3(1, 5, 1)), glm::vec3(0.8, 0.8, 0), &cubeModel);
	letters[1].entities.emplace_back(Transform(glm::vec3(2 + offset, 2.5 + height, -5), glm::vec3(0, 0, 0), glm::vec3(1, 5, 1)), glm::vec3(0.8, 0.8, 0), &cubeModel);
	letters[1].entities.emplace_back(Transform(glm::vec3(1 + offset, 2.5 + height, -5), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)), glm::vec3(0.8, 0.8, 0), &sphereModel);
	letters[1].entities.emplace_back(Transform(glm::vec3(1 + offset, 4.5 + height, -5), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)), glm::vec3(0.8, 0.8, 0), &sphereModel);

	height += 6.0f;

	letters[2].entities.emplace_back(Transform(glm::vec3(1 - 0.5f + offset, 4.0 + height, -5), glm::vec3(90, 90, -45), glm::vec3(1, 2, 1)), glm::vec3(0.0, 0.8, 0), &sphereModel);
	letters[2].entities.emplace_back(Transform(glm::vec3(0 - 0.5f + offset, 2.5 + height, -5), glm::vec3(0, 0, 0), glm::vec3(1, 5, 1)), glm::vec3(0, 0.8, 0), &cubeModel);
	letters[2].entities.emplace_back(Transform(glm::vec3(2 - 0.5f + offset, 4.0 + height, -5), glm::vec3(90, 90, 45), glm::vec3(1, 2, 1)), glm::vec3(0.0, 0.8, 0), &sphereModel);
	letters[2].entities.emplace_back(Transform(glm::vec3(3 - 0.5f + offset, 2.5 + height, -5), glm::vec3(0, 0, 0), glm::vec3(1, 5, 1)), glm::vec3(0, 0.8, 0), &cubeModel);

	height += 6.0f;

	letters[3].entities.emplace_back(Transform(glm::vec3(0 + 1 + offset, 2.5 + height, -5), glm::vec3(0, 0, 0), glm::vec3(1, 5, 1)), glm::vec3(0, 0.8, 0.8), &cubeModel);
	letters[3].entities.emplace_back(Transform(glm::vec3(0 + 1 + offset, 4.5 + height, -5), glm::vec3(90, 90, 0), glm::vec3(1, 4, 1)), glm::vec3(0.0, 0.8, 0.8), &sphereModel);
	letters[3].entities.emplace_back(Transform(glm::vec3(0 + 1 + offset, 0.5 + height, -5), glm::vec3(90, 90, 0), glm::vec3(1, 4, 1)), glm::vec3(0.0, 0.8, 0.8), &sphereModel);

	height += 6.0f;

	letters[4].entities.emplace_back(Transform(glm::vec3(0 + offset, 2.5 + height, -5), glm::vec3(0, 0, 0), glm::vec3(1, 5, 1)), glm::vec3(0.8, 0.0, 0.8), &cubeModel);
	letters[4].entities.emplace_back(Transform(glm::vec3(1 + offset, 4.5 + height, -5), glm::vec3(0, 0, 60), glm::vec3(1, 2, 1)), glm::vec3(0.8, 0.0, 0.8), &sphereModel);
	letters[4].entities.emplace_back(Transform(glm::vec3(2 + offset, 2.5 + height, -5), glm::vec3(0, 0, 0), glm::vec3(1, 3, 1)), glm::vec3(0.8, 0.0, 0.8), &sphereModel);
	letters[4].entities.emplace_back(Transform(glm::vec3(1 + offset, 0.5 + height, -5), glm::vec3(0, 0, -60), glm::vec3(1, 2, 1)), glm::vec3(0.8, 0.0, 0.8), &sphereModel);

	height += 6.0f;

	letters[5].entities.emplace_back(Transform(glm::vec3(0 + 1 + offset, 2.5 + height, -5), glm::vec3(0, 0, 0), glm::vec3(1, 5, 1)), glm::vec3(0, 0.0, 0.8), &cubeModel);
	letters[5].entities.emplace_back(Transform(glm::vec3(0 + 1 + offset, 4.5 + height, -5), glm::vec3(90, 90, 0), glm::vec3(1, 4, 1)), glm::vec3(0.0, 0.0, 0.8), &sphereModel);
	letters[5].entities.emplace_back(Transform(glm::vec3(0 + 1 + offset, 0.5 + height, -5), glm::vec3(90, 90, 0), glm::vec3(1, 4, 1)), glm::vec3(0.0, 0.0, 0.8), &sphereModel);


	//lines
	Shader lines3dShader("resources/shaders/lines3d_vertex.shader", "resources/shaders/lines3d_fragment.shader");

	std::vector<unsigned int> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> UVs;
	loadOBJ("resources/objects/cube.obj", indices, vertices, normals, UVs);


	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO); //if you take this off nothing will show up because you haven't linked the VAO to the VBO
							//you have to bind before putting the point

	GLuint vertices_VBO;
	glGenBuffers(1, &vertices_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);  //3*sizeof(GLfloat) is the offset of 3 float numbers
	glEnableVertexAttribArray(0);

	GLuint normals_VBO;
	glGenBuffers(1, &normals_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, normals_VBO);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);  //3*sizeof(GLfloat) is the offset of 3 float numbers
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices.front(), GL_STATIC_DRAW);

	// Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO
	glBindVertexArray(0);

	//model loading sort of
	Lines3d lines3dObject = Lines3d();
	Grid grid = Grid();
	AlessandroModel alessandroModel = AlessandroModel();
	LeCherngModel leCherngModel = LeCherngModel();
	DannModel danModel = DannModel();
	LaginhoModel laginModel = LaginhoModel();

	//shader set up
	shader.Bind();
	glm::mat4 model_matrix = glm::translate(glm::mat4(1.f), glm::vec3(3, 2, 0));
	glm::mat4 view_matrix = glm::lookAt(cam_pos, cam_dir, cam_up);
	glm::mat4 proj_matrix = glm::perspective(glm::radians(70.f), 1.f, 0.1f, 200.f); //perspective view. Third parameter should be > 0, or else errors

	//other model matrix

	//Alessandro
	glm::mat4 model_A_matrix = glm::translate(glm::mat4(1.f), model_A_move);
	//Le Cherng
	glm::mat4 model_L_matrix = glm::translate(glm::mat4(1.f), model_L_move);
	//Dan
	glm::mat4 model_D_matrix = glm::translate(glm::mat4(1.f), model_D_move);
	//LaginHo
	glm::mat4 model_La_matrix = glm::translate(glm::mat4(1.f), model_La_move);

	glm::mat4 grid_matrix = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0));

	glm::mat4 line_matrix = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0));

	GLuint vm_loc = shader.GetUniformLocation("vm");
	GLuint pm_loc = shader.GetUniformLocation("pm");
	GLuint mm_loc = shader.GetUniformLocation("mm");
	GLuint flag_id = shader.GetUniformLocation("flag");
	GLuint lights_id = shader.GetUniformLocation("lights");
	GLuint normalcol_id = shader.GetUniformLocation("normalcol");
	GLuint greyscale_id = shader.GetUniformLocation("greyscale");
	GLuint red_id = shader.GetUniformLocation("red");
	GLuint green_id = shader.GetUniformLocation("green");
	GLuint blue_id = shader.GetUniformLocation("blue");
	GLuint colour_id = shader.GetUniformLocation("colour");

	//glUniformMatrix4fv(vm_loc, 1, GL_FALSE, &view_matrix[0][0]); OR
	glUniformMatrix4fv(vm_loc, 1, GL_FALSE, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(pm_loc, 1, GL_FALSE, glm::value_ptr(proj_matrix));
	glUniformMatrix4fv(mm_loc, 1, GL_FALSE, glm::value_ptr(model_matrix));

	glUniform3fv(shader.GetUniformLocation("light_color"), 1, glm::value_ptr(glm::vec3(0.8, 0.8, 0.8)));
	glUniform3fv(shader.GetUniformLocation("light_position"), 1, glm::value_ptr(glm::vec3(0.0, 20.0, 5.0)));
	glUniform3fv(shader.GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
	glUniform3fv(shader.GetUniformLocation("view_position"), 1, glm::value_ptr(glm::vec3(cam_pos)));
	// 3D Lines Shader camera projection setup
	lines3dShader.Bind();
	GLuint vm_loc_lines_3d = lines3dShader.GetUniformLocation("vm");
	GLuint pm_loc_lines_3d = lines3dShader.GetUniformLocation("pm");
	GLuint mm_loc_lines_3d = lines3dShader.GetUniformLocation("mm");
	glUniformMatrix4fv(vm_loc_lines_3d, 1, GL_FALSE, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(pm_loc_lines_3d, 1, GL_FALSE, glm::value_ptr(proj_matrix));
	glUniformMatrix4fv(mm_loc_lines_3d, 1, GL_FALSE, glm::value_ptr(line_matrix));
	// Game loop
	float x = 0.0f;
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		x += 0.01f;

		mTransform.position.y = sin(x)*50;
		mTransform.position.z = cos(x)*50;
		mTransform.position.x = sin(x)*50;
		mTransform.rotation.x += 1.0f;
		mTransform.rotation.z += 0.2f;
		mTransform.rotation.y += 2.2f;


		shader.Bind();

		view_matrix = glm::lookAt(cam_pos, cam_pos + cam_dir, cam_up);
		glUniformMatrix4fv(vm_loc, 1, 0, glm::value_ptr(view_matrix));

		// --- Render ---
		// Clear the colorbuffer
		glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUniformMatrix4fv(mm_loc, 1, 0, &zTransform.getMatrix()[0][0]);
		glUniform3fv(shader.GetUniformLocation("object_color"), 1, &glm::vec3(0.0, 0.0, 1.0)[0]);
		cylinderModel.render();
		glUniformMatrix4fv(mm_loc, 1, 0, &yTransform.getMatrix()[0][0]);
		glUniform3fv(shader.GetUniformLocation("object_color"), 1, &glm::vec3(0.0, 1.0, 0.0)[0]);
		cylinderModel.render();
		glUniformMatrix4fv(mm_loc, 1, 0, &xTransform.getMatrix()[0][0]);
		glUniform3fv(shader.GetUniformLocation("object_color"), 1, &glm::vec3(1.0, 0.0, 0.0)[0]);
		cylinderModel.render();

		glUniformMatrix4fv(mm_loc, 1, 0, &mTransform.getMatrix()[0][0]);
		glUniform3fv(shader.GetUniformLocation("object_color"), 1, &glm::vec3(1.0, 1.0, 1.0)[0]);
		monkey.render();



		for(auto& i : letters){
			for(auto& i : i.entities){
				glUniformMatrix4fv(mm_loc, 1, 0, &i.transform.getMatrix()[0][0]);
				glUniform3fv(shader.GetUniformLocation("object_color"), 1, &i.color[0]);
				i.model->render();
			}
		}

		// Draws grid
		glLineWidth(0.5f);
		glUniform3fv(shader.GetUniformLocation("object_color"), 1, &glm::vec3(0.5, 0.5, 0.5)[0]);
		glUniformMatrix4fv(vm_loc_lines_3d, 1, 0, glm::value_ptr(view_matrix));
		glUniformMatrix4fv(mm_loc_lines_3d, 1, 0, glm::value_ptr(grid_matrix));
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

void DrawCube(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat edgeLength)
{
	GLfloat halfSide = edgeLength * 0.5f;

	GLfloat vertices[] =
	{
		// front face
		centerX - halfSide, centerY + halfSide, centerZ + halfSide, // top left
		centerX + halfSide, centerY + halfSide, centerZ + halfSide, // top right
		centerX + halfSide, centerY - halfSide, centerZ + halfSide, // bottom right
		centerX - halfSide, centerY - halfSide, centerZ + halfSide, // bottom left

		// back face
		centerX - halfSide, centerY + halfSide, centerZ - halfSide, // top left
		centerX + halfSide, centerY + halfSide, centerZ - halfSide, // top right
		centerX + halfSide, centerY - halfSide, centerZ - halfSide, // bottom right
		centerX - halfSide, centerY - halfSide, centerZ - halfSide, // bottom left

		// left face
		centerX - halfSide, centerY + halfSide, centerZ + halfSide, // top left
		centerX - halfSide, centerY + halfSide, centerZ - halfSide, // top right
		centerX - halfSide, centerY - halfSide, centerZ - halfSide, // bottom right
		centerX - halfSide, centerY - halfSide, centerZ + halfSide, // bottom left

		// right face
		centerX + halfSide, centerY + halfSide, centerZ + halfSide, // top left
		centerX + halfSide, centerY + halfSide, centerZ - halfSide, // top right
		centerX + halfSide, centerY - halfSide, centerZ - halfSide, // bottom right
		centerX + halfSide, centerY - halfSide, centerZ + halfSide, // bottom left

		// top face
		centerX - halfSide, centerY + halfSide, centerZ + halfSide, // top left
		centerX - halfSide, centerY + halfSide, centerZ - halfSide, // top right
		centerX + halfSide, centerY + halfSide, centerZ - halfSide, // bottom right
		centerX + halfSide, centerY + halfSide, centerZ + halfSide, // bottom left

		// top face
		centerX - halfSide, centerY - halfSide, centerZ + halfSide, // top left
		centerX - halfSide, centerY - halfSide, centerZ - halfSide, // top right
		centerX + halfSide, centerY - halfSide, centerZ - halfSide, // bottom right
		centerX + halfSide, centerY - halfSide, centerZ + halfSide  // bottom left
	};

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glColor3f( colour[0], colour[1], colour[2] );
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glDrawArrays(GL_QUADS, 0, 24);

	glDisableClientState(GL_VERTEX_ARRAY);

}
