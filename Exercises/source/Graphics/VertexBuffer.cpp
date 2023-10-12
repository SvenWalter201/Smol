#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	glGenBuffers(1, &m_rendererId); //create a buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_rendererId); //bind the buffer to draw
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); 	//set buffer size and contents
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_rendererId);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_rendererId); //bind the buffer to draw
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0); //bind the buffer to draw
}
