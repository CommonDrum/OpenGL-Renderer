#pragma once
#include <glad/glad.h>
#include "VertexArrayClass.h"
#include "IndexBufferClass.h"
#include "ShaderClass.h"


class Renderer
{
public:
	void Clear();
	void Draw(VertexArray& VA, IndexBuffer& IB, Shader& shader);
};

