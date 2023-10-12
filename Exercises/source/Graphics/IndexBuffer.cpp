#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : m_count(count)
{
	glGenBuffers(1, &m_rendererId); //create a buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId); //bind the buffer to draw
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW); 	//set buffer size and contents
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_rendererId);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId); //bind the buffer to draw
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //bind the buffer to draw
}
