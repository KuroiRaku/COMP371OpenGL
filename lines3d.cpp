#include "lines3d.h"

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   ourColor = aColor;\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0f);\n"
"}\n\0";

Lines3d::Lines3d() {
	GLfloat vertices_lines[] =
	{
		// position		// color
		0.0f,0.0f,0.0f, 1.0f, 0.0f, 0.0f,
		0.0f,5.0f,0.0f, 1.0f, 0.0f, 0.0f,
		0.0f,0.0f,0.0f, 0.0f, 1.0f, 0.0f,
		5.0f,0.0f,0.0f, 0.0f, 1.0f, 0.0f,
		0.0f,0.0f,0.0f, 0.0f, 0.0f, 1.0f,
		0.0f,0.0f,5.0f, 0.0f, 0.0f, 1.0f,
	};

	int indicies_lines[] =
	{
		0,1,
		2,3,
		3,4
	};

	glGenVertexArrays(1, &this->vao);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(this->vao);

	GLuint vertices_VBO_lines;
	glGenBuffers(1, &vertices_VBO_lines);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO_lines);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(float), vertices_lines, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);  //3*sizeof(GLfloat) is the offset of 3 float numbers
	glEnableVertexAttribArray(0);

	//color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint EBO_lines;
	glGenBuffers(1, &EBO_lines);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_lines);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2 * sizeof(int), indicies_lines, GL_STATIC_DRAW);
	glBindVertexArray(0);

	//compileShader();
}

GLuint Lines3d::getVAO()
{
	return this->vao;
}

int Lines3d::getIndicesSize()
{
	return 6;
}

void Lines3d::drawLines()
{
	//glUseProgram(this->shaderProgram);
	glBindVertexArray(this->vao);
	glDrawArrays(GL_LINES, 0, 6);
}

void Lines3d::compileShader()
{
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	this->shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
