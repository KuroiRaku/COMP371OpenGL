#include "Renderer.h"
#include "GLDebugMessageCallback.h"

// drawMode 0 = Triangle, 1= lines, 2 = point
void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const int& drawMode) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();

	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
