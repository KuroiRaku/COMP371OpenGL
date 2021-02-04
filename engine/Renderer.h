#pragma once

#include <glad/glad.h>
#include <iostream>
#include <string>

#include "VertexArray.h"
#include "Shader.h"
#include "IndexBuffer.h"

class Renderer
{
public:
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const int& drawMode) const;
	void Clear() const;
};



