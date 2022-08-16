#pragma once
#include <glad/glad.h>
#include "VertexArrayClass.h"
#include "IndexBufferClass.h"
#include "ShaderClass.h"
#include "glm/glm.hpp"


#define MAX_VERTEX 1000
#define MAX_INDEX  10000


struct Vertex
{
	glm::vec3 coordinates;
	glm::vec3 color;
};


class Renderer
{
private:
	VertexArray* VA;
	IndexBuffer* IB;
	VertexBuffer* VB;
	Shader* p_Shader;
	

public:
	Renderer(Shader* shader);
	~Renderer();
	
	// Utilities
	void Clear();
	void Draw();

	// Data provided from outside of the class
	void SetVBLayout(const VertexBufferLayout& layout);
	void SetShader(Shader* shader);
	//void SetVertexArray();
	void SetIndexBuffer(int size, void* data);
	void SetVertexBuffer(int size, void* data);
};
