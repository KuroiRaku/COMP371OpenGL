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

#include "ObjLoaderIndex.h"
#include "Shader.h"
#include "Font.h"
#include "GLDebugMessageCallback.h"
#include "../lines3d.h"
#include "../grid.h"
#include "../LModel.h"
#include "../EModel.h"
#include "../CModel.h"

using namespace std;

// Window dimensions
const GLuint WIDTH = 1024, HEIGHT = 768;

//camera settings
glm::vec3 cam_pos = glm::vec3(0, 2, 90);
glm::vec3 cam_dir = glm::vec3(0, 0, -1); //direction means what the camera is looking at
glm::vec3 temp_cam_dir = glm::vec3(0, 0, 1); //use this for the cross product or else when cam_dir and cam_up overlap, the cross product will be 0 (bad!)
glm::vec3 cam_up = glm::vec3(0, 1, 0); //up defines where the top of the camera is directing towards


// Le Cherng Lee
// I'm using last name and first three characters of my first name
//model settings
glm::mat4 model = glm::mat4(1.0f); //active model
glm::vec3 model_move = glm::vec3(0, 15, 0); //to apply translational transformations

//model cube that we loaded in for no reason :p
glm::mat4 model_cube = glm::mat4(1.0f); //active model
glm::vec3 model_cube_move = glm::vec3(0, 2, -10); //to apply translational transformations

//Character L
glm::mat4 model_L = glm::mat4(1.0f);
glm::vec3 model_L_move = glm::vec3(0, 15, 0); //to apply translational transformations

//Character E
glm::mat4 model_E = glm::mat4(1.0f);
glm::vec3 model_E_move = glm::vec3(0, 12, 0); //to apply translational transformations

//Second Character E
glm::mat4 model_E2 = glm::mat4(1.0f);
glm::vec3 model_E2_move = glm::vec3(0, 9, 0); //to apply translational 

//Second Character L
glm::mat4 model_L2 = glm::mat4(1.0f);
glm::vec3 model_L2_move = glm::vec3(0, 6, 0); //to apply translational transformations

//Third Character E
glm::mat4 model_E3 = glm::mat4(1.0f);
glm::vec3 model_E3_move = glm::vec3(0, 3, 0); //to apply translational transformations

//Third Character C
glm::mat4 model_C = glm::mat4(1.0f);
glm::vec3 model_C_move = glm::vec3(0, 0, 0); //to apply translational transformations

//Grid
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
//glm::vec3 object_color = glm::vec3(0.5, 0.5, 0.5);


void resetToPreviousModel(int previousActiveModel) {
	switch (previousActiveModel)
	{
	case 0:
		model = model_L;
		model_move = model_L_move;
		break;
	case 1:
		model = model_E;
		model_move = model_E_move;
		break;
	case 2:
		model = model_E2;
		model_move = model_E2_move;
		break;
	case 3:
		model = model_L2;
		model_move = model_L2_move;
		break;
	case 4:
		model = model_E3;
		model_move = model_E3_move;
		break;
	case 5:
		model = model_C;
		model_move = model_C_move;
		break;
	case 6:
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

	if ((key == GLFW_KEY_LEFT|| key == GLFW_KEY_RIGHT || key == GLFW_KEY_UP || key == GLFW_KEY_DOWN) && action == GLFW_PRESS) {
		activeModel = 99;
		worldOrientationKeyPressed = true;
	}

	if ((key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT || key == GLFW_KEY_UP || key == GLFW_KEY_DOWN) && action == GLFW_RELEASE) {
		worldOrientationKeyPressed = false;
		resetToPreviousModel(previousActiveModel);
	}

	//WASD buttons to move the camera
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

	//reset to initial position
	if (key == GLFW_KEY_HOME)
	{
		model_world = glm::mat4(1.f);
	}

	//full reset
	if (key == GLFW_KEY_0)
	{
		model = glm::mat4(1.0f);
		model_move = glm::vec3(0, 2, -10); //to apply translational transformations

		//Character L
		glm::mat4 model_L = glm::mat4(1.0f);
		glm::vec3 model_L_move = glm::vec3(0, 20, 0); //to apply translational transformations

		//Character E
		glm::mat4 model_E = glm::mat4(1.0f);
		glm::vec3 model_E_move = glm::vec3(0, 15, 0); //to apply translational transformations

		//Second Character E
		glm::mat4 model_E2 = glm::mat4(1.0f);
		glm::vec3 model_E2_move = glm::vec3(0, 13, 0); //to apply translational 

		//Second Character L
		glm::mat4 model_L2 = glm::mat4(1.0f);
		glm::vec3 model_L2_move = glm::vec3(0, 8, 0); //to apply translational transformations

		//Third Character E
		glm::mat4 model_E3 = glm::mat4(1.0f);
		glm::vec3 model_E3_move = glm::vec3(0, 2, 0); //to apply translational transformations

		//Third Character C
		glm::mat4 model_C = glm::mat4(1.0f);
		glm::vec3 model_C_move = glm::vec3(0, 0, 0); //to apply translational transformations

		//Grid
		glm::mat4 model_grid = glm::mat4(1.0f);
		glm::vec3 model_grid_move = glm::vec3(0, 0, 0); //to apply translational transformations

		//World Matrix
		glm::mat4 model_world = glm::mat4(1.0f);
		glm::vec3 model_world_move = glm::vec3(0, 0, 0); //to apply translational transformations

		model_world = glm::mat4(1.f);
	}
	
	if (!worldOrientationKeyPressed) {
		//WASD buttons to move the model
		if (!leftShiftPressed) {
			if (key == GLFW_KEY_W) { //I moves the object along the +Y axis
				model_move.y += 1;
			}

			if (key == GLFW_KEY_S) { //K moves the object along the -Y
				model_move.y -= 1;
			}

			if (key == GLFW_KEY_A) { //J moves the object along the +X axis
				model_move.x -= 1;
			}

			if (key == GLFW_KEY_D) { //L moves the object along the -X axis
				model_move.x += 1;
			}

			if (key == GLFW_KEY_PAGE_UP) { //PgUp moves the object along the +Z axis
				model_move.z += 1;
			}

			if (key == GLFW_KEY_PAGE_DOWN) { //PgDown moves the object along the -Z axis
				model_move.z -= 1;
			}
		}

		//BNE buttons to rotate the model
		if (leftShiftPressed == true) {
			if (key == GLFW_KEY_W) { //W rotates the object about the +X axis
				model = glm::rotate(model, glm::radians(5.f), glm::vec3(1, 0, 0));
			}
			if (key == GLFW_KEY_S) { //S rotates the object about the -X axis
				model = glm::rotate(model, glm::radians(5.f), glm::vec3(-1, 0, 0));
			}
			if (key == GLFW_KEY_A) { //N rotates the object about the Y axis,
				model = glm::rotate(model, glm::radians(5.f), glm::vec3(0, 1, 0));
			}
			if (key == GLFW_KEY_D) { //N rotates the object about the -Y axis,
				model = glm::rotate(model, glm::radians(5.f), glm::vec3(0, -1, 0));
			}
			if (key == GLFW_KEY_E) { //rotates the object about the Z axis
				model = glm::rotate(model, glm::radians(5.f), glm::vec3(0, 0, 1));
			}
			if (key == GLFW_KEY_Q) { //rotates the object about the -Z axis
				model = glm::rotate(model, glm::radians(5.f), glm::vec3(0, 0, -1));
			}
		}

		//OP buttons to scale up and down
		if (key == GLFW_KEY_U) { //O scales up the object by a factor of 10%
			model = glm::scale(model, glm::vec3(1.1f));
		}
		if (key == GLFW_KEY_J) { //P scales up the object by a factor of -10%
			model = glm::scale(model, glm::vec3(0.9f));
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
			previousActiveModel = 0;
			model = model_L;
			model_move = model_L_move;

			
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
			model = model_E;
			model_move = model_E_move;
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

			model = model_E2;
			model_move = model_E2_move;

			
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

			model = model_L2;
			model_move = model_L2_move;
		}

		//toggle between Gouraud and Phong shading
		if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
			if (flag == false)
				flag = true;
			else
				flag = false;

			activeModel = 4;
			previousActiveModel = 4;
			model = model_E3;
			model_move = model_E3_move;
		}

		if (key == GLFW_KEY_6 && action == GLFW_PRESS) {
			if (lights == false)
				lights = true;
			else
				lights = false;

			activeModel = 5;
			previousActiveModel = 5;
			model = model_C;
			model_move = model_C_move;
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
		cout << "Rendering Mode: " << renderingMode << endl;
	}

	if (key == GLFW_KEY_L && action == GLFW_PRESS) {
		renderingMode = 1;
		cout << "Rendering Mode: " << renderingMode << endl;
	}

	if (key == GLFW_KEY_T && action == GLFW_PRESS) {
		renderingMode = 2;
		cout << "Rendering Mode: " << renderingMode << endl;
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

 //The MAIN function, from here we start the application and run the game loop
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

	std::vector<int> indices;
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
	
	//ascending Order
	LModel lModel = LModel();
	EModel eModel = EModel();
	EModel e2Model = EModel();
	LModel l2Model = LModel();
	EModel e3Model = EModel();
	CModel cModel = CModel();
	
	//shader set up
	shader.Bind();
	glm::mat4 model_cube_matrix = glm::translate(glm::mat4(1.f), glm::vec3(3, 2, 0));
	glm::mat4 view_matrix = glm::lookAt(cam_pos, cam_dir, cam_up);
	glm::mat4 proj_matrix = glm::perspective(glm::radians(45.f), 1.f, 0.1f, 200.f); //perspective view. Third parameter should be > 0, or else errors

	//other model matrix
	
	//Last Name: Lee, First Name: Le Cherng 
	glm::mat4 model_L_matrix = glm::translate(glm::mat4(1.f), model_L_move);
	glm::mat4 model_E_matrix = glm::translate(glm::mat4(1.f), model_E_move);
	glm::mat4 model_E2_matrix = glm::translate(glm::mat4(1.f), model_E2_move);
	glm::mat4 model_L2_matrix = glm::translate(glm::mat4(1.f), model_L2_move);
	glm::mat4 model_E3_matrix = glm::translate(glm::mat4(1.f), model_E3_move);
	glm::mat4 model_C_matrix = glm::translate(glm::mat4(1.f), model_C_move);


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
	glUniformMatrix4fv(mm_loc, 1, GL_FALSE, glm::value_ptr(model_cube_matrix));

	glUniform3fv(shader.GetUniformLocation("light_color"), 1, glm::value_ptr(glm::vec3(0.8, 0.8, 0.8)));
	glUniform3fv(shader.GetUniformLocation("light_position"), 1, glm::value_ptr(glm::vec3(5.0, 20.0, 5.0)));
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
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		shader.Bind();

		view_matrix = glm::lookAt(cam_pos, cam_pos + cam_dir, cam_up);
		glUniformMatrix4fv(vm_loc, 1, 0, glm::value_ptr(view_matrix));

		
		glm::mat4 translator_L = glm::translate(glm::mat4(1.0f), model_L_move);
		glm::mat4 translator_E = glm::translate(glm::mat4(1.0f), model_E_move);
		glm::mat4 translator_E2 = glm::translate(glm::mat4(1.0f), model_E2_move);
		glm::mat4 translator_L2 = glm::translate(glm::mat4(1.0f), model_L2_move);
		glm::mat4 translator_E3 = glm::translate(glm::mat4(1.0f), model_E3_move);
		glm::mat4 translator_C = glm::translate(glm::mat4(1.0f), model_C_move);
		glm::mat4 translator_cube = glm::translate(glm::mat4(1.0f), model_cube_move);

		glm::mat4 translator_grid = glm::translate(glm::mat4(1.0f), model_grid_move);
		glm::mat4 translator = glm::translate(glm::mat4(1.0f), model_move);

		switch (activeModel) {
		case 0:
			
			
			grid_matrix = model_world * translator_grid * model_grid;
			model_cube_matrix = model_world * translator_cube * model_cube;

			model_L_matrix = model_world * translator * model;
			model_L = model;
			model_L_move = model_move;

			model_E_matrix = model_world * translator_E * model_E;
			model_E2_matrix = model_world * translator_E2 * model_E2;
			model_L2_matrix = model_world * translator_L2 * model_L2;
			model_E3_matrix = model_world * translator_E3 * model_E3;
			model_C_matrix = model_world * translator_C * model_C;

			break;
		case 1:
			model_E_matrix = model_world * translator * model;
			model_E = model;
			model_E_move = model_move;
			
			model_cube_matrix = model_world * translator_cube * model_L2;
			grid_matrix = model_world * translator_grid * model_grid;

			model_L_matrix = model_world * translator_L * model_L;
			model_E2_matrix = model_world * translator_E2 * model_E2;
			model_L2_matrix = model_world * translator_L2 * model_L2;
			model_E3_matrix = model_world * translator_E3 * model_E3;
			model_C_matrix = model_world * translator_C * model_C;


			break;
		case 2:
			model_E2_matrix = model_world * translator * model;
			model_E2 = model;
			model_E2_move = model_move;

			model_cube_matrix = model_world * translator_cube * model_L2;
			grid_matrix = model_world * translator_grid * model_grid;
			
			model_L_matrix = model_world * translator_L * model_L;
			model_E_matrix = model_world * translator_E * model_E;
			model_L2_matrix = model_world * translator_L2 * model_L2;
			model_E3_matrix = model_world * translator_E3 * model_E3;
			model_C_matrix = model_world * translator_C * model_C;

			break;
		case 3:
			model_L2_matrix = model_world * translator * model;
			model_L2 = model;
			model_L2_move = model_move;
			
			model_cube_matrix = model_world * translator_cube * model_L2;
			grid_matrix = model_world * translator_grid * model_grid;

			model_L_matrix = model_world * translator_L * model_L;
			model_E_matrix = model_world * translator_E * model_E;
			model_E2_matrix = model_world * translator_E2 * model_E2;
			model_E3_matrix = model_world * translator_E3 * model_E3;
			model_C_matrix = model_world * translator_C * model_C;

			break;
		case 4:
			model_E3_matrix = model_world * translator * model;
			model_E3 = model;
			model_E3_move = model_move;

			model_cube_matrix = model_world * translator_cube * model_cube;
			grid_matrix = model_world * translator_grid * model_grid;

			model_L_matrix = model_world * translator_L * model_L;
			model_E_matrix = model_world * translator_E * model_E;
			model_E2_matrix = model_world * translator_E2 * model_E2;
			model_L2_matrix = model_world * translator_L2 * model_L2;
			model_C_matrix = model_world * translator_C * model_C;

			break;
		case 5:
			model_C_matrix = model_world * translator* model;
			
			model_C = model;
			model_C_move = model_move;

			model_cube_matrix = model_world * translator_cube * model_cube;
			grid_matrix = model_world * translator_grid * model_grid;

			model_L_matrix = model_world * translator_L * model_L;
			model_E_matrix = model_world * translator_E * model_E;
			model_E2_matrix = model_world * translator_E2 * model_E2;
			model_L2_matrix = model_world * translator_L2 * model_L2;
			model_E3_matrix = model_world * translator_E3 * model_E3;

			break;
		default:
			model_cube_matrix = model_world * translator_cube * model_L2;
			grid_matrix = model_world * translator_grid * model_grid;

			model_L_matrix = model_world * translator_L * model_L;
			model_E_matrix = model_world * translator_E * model_E;
			model_E2_matrix = model_world * translator_E2 * model_E2;
			model_L2_matrix = model_world * translator_L2 * model_L2;
			model_E3_matrix = model_world * translator_E3 * model_E3;
			model_C_matrix = model_world * translator_C * model_C;

			break;
		}
		glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(model_cube_matrix));

		glUniform1i(flag_id, flag);
		glUniform1i(lights_id, lights);
		/*glUniform1i(normalcol_id, normalcol);
		glUniform1i(greyscale_id, greyscale);
		glUniform1i(red_id, red);
		glUniform1i(green_id, green);
		glUniform1i(blue_id, blue);
		*/
		//glUniform1i(colour_id, colour);

		// --- Render ---
		// Clear the colorbuffer
		glClearColor(0.0f, 0.5019f, 0.5019f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draws cube
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

		// Draws Models
		glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(model_L_matrix));
		glUniform3fv(shader.GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(0.5, 0.5, 0.3)));
		lModel.drawModel(renderingMode, &shader, model_L);
		
		glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(model_E_matrix));
		glUniform3fv(shader.GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(1, 0, 0)));
		eModel.drawModel(renderingMode,&shader,model_E);
		
		glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(model_E2_matrix));
		glUniform3fv(shader.GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(0.5, 0, 0)));
		e2Model.drawModel(renderingMode, &shader, model_E2);

		glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(model_L2_matrix));
		glUniform3fv(shader.GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(0.5, 0, 1)));
		l2Model.drawModel(renderingMode, &shader, model_L2);

		//3rd e
		glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(model_E3_matrix));
		glUniform3fv(shader.GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(0.5, 1, 1)));
		e3Model.drawModel(renderingMode, &shader, model_E3);

		//C
		glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(model_C_matrix));
		glUniform3fv(shader.GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(0.5, 1, 0.3)));
		cModel.drawModel(renderingMode, &shader, model_C);

		// Draws line
		glLineWidth(1.0f);
		glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(line_matrix));
		glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(line_matrix));
		lines3dObject.drawLines(mm_loc, &shader, line_matrix);

		// Draws grid
		lines3dShader.Bind();
		glLineWidth(0.5f);
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


