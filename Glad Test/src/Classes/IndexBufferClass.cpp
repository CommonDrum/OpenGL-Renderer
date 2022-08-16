#include "../Headers/IndexBufferClass.h"

// Constructor that generates a Elements Buffer Object and links it to indices
IndexBuffer::IndexBuffer(GLuint* indices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	m_Size = size;
}

// Binds the ElementBuffer
void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// Unbinds the ElementBuffer
void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Deletes the ElementBuffer
void IndexBuffer::Delete()
{
	glDeleteBuffers(1, &ID);
}

int IndexBuffer::GetCount()
{
	return m_Size/4;
}