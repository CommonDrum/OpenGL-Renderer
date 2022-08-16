#include "../Headers/Renderer.h"

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw( VertexArray& VA, IndexBuffer& IB, Shader& shader)
{
	VA.Bind();
	IB.Bind();
	//shader.Activate();

	// Draw primitives, number of indices, datatype of indices, index of indices
	glDrawElements(GL_TRIANGLES, IB.GetCount() , GL_UNSIGNED_INT, 0);
}