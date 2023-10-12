#include "QuadRenderer.h"
#include <iostream>
#include "../Graphics/Shader.h"

//Default Quad Vertex Data
glm::vec2 quadVertexData[] = {
glm::vec2(-0.5f, -0.5f), glm::vec2(0.0f, 0.0f),
glm::vec2(0.5f, -0.5f), glm::vec2(1.0f, 0.0f),
glm::vec2(0.5f,  0.5f), glm::vec2(1.0f, 1.0f),
glm::vec2(-0.5f,  0.5f), glm::vec2(0.0f, 1.0f)
};

QuadRenderer::QuadRenderer(GameObject* owner) : 
	Component(owner),
	m_TexCoords({ glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f) }), 
	m_TextureId(0), 
	m_Shader(nullptr)
{
}

QuadRenderer::~QuadRenderer()
{
	if (m_Shader != nullptr)
	{
		unsigned int users = m_Shader->RemoveUser();
		if (users == 0)
			delete(m_Shader);
	}

}

void QuadRenderer::Update()
{
}

void QuadRenderer::SetTexCoordsByAtlasIndex(unsigned int atlasIdx, unsigned int atlasWidth, unsigned int atlasHeight)
{
	unsigned int xIdx = atlasIdx % atlasWidth;
	unsigned int yIdx = atlasIdx / atlasHeight;

	std::cout << xIdx << std::endl;
	std::cout << yIdx << std::endl;

	float xFraction = 1.0f / (float)atlasWidth;
	float yFraction = 1.0f / (float)atlasHeight;

	std::cout << xFraction << std::endl;
	std::cout << yFraction << std::endl;

	m_TexCoords =
	{
		glm::vec2(xIdx * xFraction, yIdx * yFraction), //lL
		glm::vec2((xIdx + 1) * xFraction, yIdx * yFraction), //rL
		glm::vec2((xIdx + 1) * xFraction, (yIdx + 1) * yFraction), //rU
		glm::vec2(xIdx * xFraction, (yIdx + 1) * yFraction) //lU
	};
}

void QuadRenderer::AssignShader(Shader* shader)
{
	if (m_Shader != nullptr)
	{
		unsigned int users = m_Shader->RemoveUser();
		if (users == 0)
			delete(m_Shader);
	}

	m_Shader = shader;
	m_Shader->AddUser();
}
