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
#include "../lines3d.h";

using namespace std;

// Window dimensions
const GLuint WIDTH = 1024, HEIGHT = 768;

//camera settings
glm::vec3 cam_pos = glm::vec3(0, 2, 90);
glm::vec3 cam_dir = glm::vec3(0, 0, -1); //direction means what the camera is looking at
glm::vec3 temp_cam_dir = glm::vec3(0, 0, 1); //use this for the cross product or else when cam_dir and cam_up overlap, the cross product will be 0 (bad!)
glm::vec3 cam_up = glm::vec3(0, 1, 0); //up defines where the top of the camera is directing towards

//model settings
glm::mat4 model = glm::mat4(1.0f); //to apply scalor and rotational transformations
glm::vec3 modl_move = glm::vec3(0, 0, 0); //to apply translational transformations

//color settings
bool flag = false;
bool lights = false;
bool normalcol = false;
bool greyscale = false;
bool red = false;
bool green = false;
bool blue = false;
bool colour = false;
//glm::vec3 object_color = glm::vec3(0.5, 0.5, 0.5);
void DrawCube(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat edgeSize);
// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mod)
{
	std::cout << key << std::endl;	//outputs the key value

	//if you press the Esc key, the window will close
	if (key == GLFW_KEY_ESCAPE)
		glfwSetWindowShouldClose(window, GL_TRUE);

	//WASD buttons to move the camera
	if (key == GLFW_KEY_W) //W moves forward
		cam_pos += cam_dir;

	if (key == GLFW_KEY_S) //S moves backwards
		cam_pos -= cam_dir;

	if (key == GLFW_KEY_D) //D moves right
		cam_pos -= glm::cross(cam_up, cam_dir);

	if (key == GLFW_KEY_A) //A moves left
		cam_pos += glm::cross(cam_up, cam_dir);

	//Left and Right key rotate camera
	if (key == GLFW_KEY_RIGHT) //left arrow rotates the camera left about the up vector
		cam_dir = glm::mat3(glm::rotate(glm::radians(0.8f), -cam_up)) * cam_dir;

	if (key == GLFW_KEY_LEFT) //right arrow rotates the camera right about the up vector
		cam_dir = glm::mat3(glm::rotate(glm::radians(0.8f), cam_up)) * cam_dir;

	glm::vec3 rotate_around_x = glm::cross(cam_up, cam_dir); //cross product
	if (key == GLFW_KEY_UP) { //up arrow rotates the camera upwards about the right vector
		glm::mat4 rotation_matrix(1);
		rotation_matrix = glm::rotate(rotation_matrix, -(8 / 180.0f), rotate_around_x);
		cam_dir = glm::mat3(rotation_matrix) * cam_dir;
		cam_up = glm::mat3(rotation_matrix) * cam_up;
	}

	if (key == GLFW_KEY_DOWN) { //down arrow rotates the camera downwards about the right vector
								//cam_dir = glm::mat3(glm::rotate(glm::radians(0.8f), rotate_around_x)) * cam_dir;
		glm::mat4 rotation_matrix(1);
		rotation_matrix = glm::rotate(rotation_matrix, (8 / 180.0f), rotate_around_x);
		cam_dir = glm::mat3(rotation_matrix) * cam_dir;
		cam_up = glm::mat3(rotation_matrix) * cam_up;
	}

	//IJKL buttons to move the model
	if (key == GLFW_KEY_I) //I moves the object along the +Y axis
		modl_move.y += 1;

	if (key == GLFW_KEY_K) //K moves the object along the -Y
		modl_move.y -= 1;

	if (key == GLFW_KEY_J) //J moves the object along the +X axis
		modl_move.x -= 1;

	if (key == GLFW_KEY_L) //L moves the object along the -X axis
		modl_move.x += 1;

	if (key == GLFW_KEY_PAGE_UP) //PgUp moves the object along the +Z axis
		modl_move.z += 1;

	if (key == GLFW_KEY_PAGE_DOWN) //PgDown moves the object along the -Z axis
		modl_move.z -= 1;

	//BNE buttons to rotate the model
	if (key == GLFW_KEY_B) //B rotates the object about the X axis
		model = glm::rotate(model, glm::radians(5.f), glm::vec3(1, 0, 0));

	if (key == GLFW_KEY_N) //N rotates the object about the Y axis,
		model = glm::rotate(model, glm::radians(5.f), glm::vec3(0, 1, 0));

	if (key == GLFW_KEY_E) //rotates the object about the Z axis
		model = glm::rotate(model, glm::radians(5.f), glm::vec3(0, 0, 1));

	//OP buttons to scale up and down
	if (key == GLFW_KEY_O) //O scales up the object by a factor of 10%
		model = glm::scale(model, glm::vec3(1.1f));

	if (key == GLFW_KEY_P) //P scales up the object by a factor of -10%
		model = glm::scale(model, glm::vec3(0.9f));

	//toggle the red channel on/off
	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		/*if (object_color.x != 0.5) {
			object_color.x = 0.5;
		}
		else
			object_color.x = 0;*/
		if (red != true)
			red = true;
		else
			red = false;
	}

	//toggle the green channel on/off
	if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		/*if (object_color.y != 0.5) {
			object_color.y = 0.5;
		}
		else
			object_color.y = 0;*/
		if (green != true)
			green = true;
		else
			green = false;
	}

	//toggle the blue channel on/off
	if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
		/*if (object_color.z != 0.5) {
			object_color.z = 0.5;
		}
		else
			object_color.z = 0;*/
		if (blue != true)
			blue = true;
		else
			blue = false;
	}

	//turn on all channels
	if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
		/*if (object_color != glm::vec3(0.5, 0.5, 0.5))
			object_color = glm::vec3(0.5, 0.5, 0.5);
		else
			object_color = glm::vec3(0, 0, 0);*/
		if (colour != true) {
			colour = true;

			red = false;
			green = false;
			blue = false;
			colour = false;
		}
		else
			colour = false;
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

	if (key == GLFW_KEY_M && action == GLFW_PRESS) {
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
	}
}

double last_y_pos = 0;

//LEFT mouse button + drag up and down, moves the camera further and closer to the object
void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
	bool lbutton_pressed = true;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		lbutton_pressed = true;
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		lbutton_pressed = false;

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
}


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
	shader.Bind();

	//Font Shader
	/*Shader textShader("resources/shaders/text.vs", "resources/shaders/text.fs");
	textShader.Bind();*/

	
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
	

	Lines3d lines3dObject = Lines3d();


	//glm is a math funtion
	glm::mat4 modl_matrix = glm::translate(glm::mat4(1.f), glm::vec3(3, 0, 0));
	glm::mat4 view_matrix = glm::lookAt(cam_pos, cam_dir, cam_up);
	glm::mat4 proj_matrix = glm::perspective(glm::radians(45.f), 1.f, 0.1f, 200.f); //perspective view. Third parameter should be > 0, or else errors
	glEnable(GL_DEPTH_TEST); //remove surfaces beyond the cameras render distance

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
	glUniformMatrix4fv(mm_loc, 1, GL_FALSE, glm::value_ptr(modl_matrix));

	glUniform3fv(shader.GetUniformLocation("light_color"), 1, glm::value_ptr(glm::vec3(0.8, 0.8, 0.8)));
	glUniform3fv(shader.GetUniformLocation("light_position"), 1, glm::value_ptr(glm::vec3(0.0, 20.0, 5.0)));
	glUniform3fv(shader.GetUniformLocation("object_color"), 1, glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
	glUniform3fv(shader.GetUniformLocation("view_position"), 1, glm::value_ptr(glm::vec3(cam_pos)));

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		view_matrix = glm::lookAt(cam_pos, cam_pos + cam_dir, cam_up);
		glUniformMatrix4fv(vm_loc, 1, 0, glm::value_ptr(view_matrix));

		//glm::mat4 rotator = glm::rotate(glm::mat4(1.0f), i / 200.f, glm::vec3(1, 0, 0));
		glm::mat4 translator = glm::translate(glm::mat4(1.0f), modl_move);
		//glm::mat4 scalor = glm::scale(glm::mat4(1.0f), glm::vec3(1, 1, 1));
		modl_matrix = translator * model;
		glUniformMatrix4fv(mm_loc, 1, 0, glm::value_ptr(modl_matrix));

		DrawCube(WIDTH / 2, HEIGHT / 2, -500, 200);
		//glUniform3fv(object_color_id, 1, glm::value_ptr(object_color));
		glUniform1i(flag_id, flag);
		glUniform1i(lights_id, lights);
		glUniform1i(normalcol_id, normalcol);
		glUniform1i(greyscale_id, greyscale);
		glUniform1i(red_id, red);
		glUniform1i(green_id, green);
		glUniform1i(blue_id, blue);
		glUniform1i(colour_id, colour);

		// --- Render ---
		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draws cube
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

		// Draws line
		glBindVertexArray(lines3dObject.getVAO());
		glDrawArrays(GL_LINES, 0, lines3dObject.getIndicesSize());

		// Unbinds VAO
		glBindVertexArray(0);

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

