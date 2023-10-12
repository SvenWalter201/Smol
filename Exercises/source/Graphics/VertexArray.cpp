#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Renderer.h"

VertexArray::VertexArray()
{
	//Vertex Array Object
	glGenVertexArrays(1, &m_RendererId);
	glBindVertexArray(m_RendererId);
}


VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererId);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (size_t i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}

}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererId);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
