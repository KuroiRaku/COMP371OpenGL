#pragma once

#include <glad/glad.h>
#include <iostream>
#include <string>

#include "VertexArray.h"
#include "Shader.h"
#include "IndexBuffer.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x,__FILE__,__LINE__))
//#define openGLDebug() glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS)
#define LOG(x) std::cout<<x<<std::endl

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const int& drawMode) const;
	void Clear() const;
};



